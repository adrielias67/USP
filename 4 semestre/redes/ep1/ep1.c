/* Por Prof. Daniel Batista <batista@ime.usp.br>
 * Em 27/8/2023
 * 
 * Um código simples de um servidor de eco a ser usado como base para
 * o EP1. Ele recebe uma linha de um cliente e devolve a mesma linha.
 * Teste ele assim depois de compilar:
 * 
 * ./redes-servidor-exemplo-ep1 8000
 * 
 * Com este comando o servidor ficará escutando por conexões na porta
 * 8000 TCP (Se você quiser fazer o servidor escutar em uma porta
 * menor que 1024 você precisará ser root ou ter as permissões
 * necessáfias para rodar o código com 'sudo').
 *
 * Depois conecte no servidor via telnet. Rode em outro terminal:
 * 
 * telnet 127.0.0.1 8000
 * 
 * Escreva sequências de caracteres seguidas de ENTER. Você verá que o
 * telnet exibe a mesma linha em seguida. Esta repetição da linha é
 * enviada pelo servidor. O servidor também exibe no terminal onde ele
 * estiver rodando as linhas enviadas pelos clientes.
 * 
 * Obs.: Você pode conectar no servidor remotamente também. Basta
 * saber o endereço IP remoto da máquina onde o servidor está rodando
 * e não pode haver nenhum firewall no meio do caminho bloqueando
 * conexões na porta escolhida.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "hash.h"

#define LISTENQ 1
#define MAXDATASIZE 100
#define MAXLINE 4096

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void printhxs(u8 buffer[], int size){
//     // Usado para debugar
//     for(int i=0; i<size; i++){
//         printf("%02x ", buffer[i]);
//     }
//     printf("\n");
// }


void skip_frame(int connfd);                                          // pula o frame e imprime os dados
int make_request(char recvline[], int connfd, hash* queues);                        // lê o frame e chama o request correspondente
void connection_establish(char recvline[], int connfd);               // estabelece a conexão
void connection_close(int connfd);                                    // fecha a conexão (não o canal)
void deliver_round_robin(char deliver_frame[], char queue_name[], hash* queues, int deliver_size);    // dá deliver na frame já feita para o primeiro da fila
// Requests:
void queue_declare(int connfd, char queue_name[], hash* queues);
void queue_consume(int connfd, char queue_name[], hash* queues);
void basic_publish(int connfd, char queue_name[], char message[], hash* queues);

u8 payload_buffer[2000000];


void skip_frame(int connfd){
    u8 frame_type;
    read(connfd, &frame_type, 1);

    u16 frame_channel;
    read(connfd, &frame_channel, 2);
    frame_channel = ntohs(frame_channel);
    
    u32 payload_size;
    read(connfd, &payload_size, 4);
    payload_size = ntohl(payload_size);
    
    read(connfd, payload_buffer, payload_size);
    
    u8 frame_end;
    read(connfd, &frame_end, 1);
    
    printf("|Frame type: %d\n", frame_type);
    printf("|Payload size: %d\n", payload_size);
    printf("|Frame end: %hx\n\n", frame_end);
}


int make_request(char recvline[], int connfd, hash* queues){
    // Retorna se deve fechar a conexão (1) ou não (0)
    u8 frame_type;
    read(connfd, &frame_type, 1);

    u16 frame_channel;
    read(connfd, &frame_channel, 2);
    frame_channel = ntohs(frame_channel);
    
    u32 payload_size;
    read(connfd, &payload_size, 4);
    payload_size = ntohl(payload_size);
    
    u16 frame_class;
    read(connfd, &frame_class, 2);
    frame_class = ntohs(frame_class);

    u16 frame_method;
    read(connfd, &frame_method, 2);
    frame_method = ntohs(frame_method);
    
    // Queue declare
    if(frame_class==50 && frame_method==10){
        read(connfd, payload_buffer, 2);    // ticket
        u8 queue_name_size;                                                 //
        read(connfd, &queue_name_size, 1);                                  //
        u8 queue_name[queue_name_size];                                     //
        read(connfd, queue_name, queue_name_size);                          //
        read(connfd, payload_buffer, payload_size-4-2-1-queue_name_size);   // nome da fila
        u8 frame_end;
        read(connfd, &frame_end, 1);
        queue_declare(connfd, queue_name, queues);
        return 1;
    }
    
    // Queue consume
    if(frame_class==60 && frame_method==20){
        read(connfd, payload_buffer, 2);    // ticket
        u8 queue_name_size;                         //
        read(connfd, &queue_name_size, 1);          //
        //printf("queue name size: %d\n", queue_name_size);
        char queue_name[queue_name_size];           //
        read(connfd, queue_name, queue_name_size);  // nome da fila
        read(connfd, payload_buffer, payload_size-4-2-1-queue_name_size); 
        u8 frame_end;
        read(connfd, &frame_end, 1);
        queue_consume(connfd, queue_name, queues);
        return 0;
    }

    // Basic publish
    if(frame_class==60 && frame_method==40){
        read(connfd, payload_buffer, 2);    // ticket
        read(connfd, payload_buffer, 1);    // exchange 
        u8 queue_name_size;
        read(connfd, &queue_name_size, 1);            //
        char queue_name[queue_name_size];             // 
        read(connfd, queue_name, queue_name_size);    // nome da fila
        read(connfd, payload_buffer, 1);    // mandatory/immediate
        u8 frame_end;
        read(connfd, &frame_end, 1);
        read(connfd, payload_buffer, 1+2);    // type, channel
        u32 payload_size;
        read(connfd, &payload_size, 4);
        payload_size = ntohl(payload_size);
        read(connfd, payload_buffer, payload_size);
        read(connfd, &frame_end, 1);    // frame-end
        read(connfd, payload_buffer, 1+2);    // type, channel
        u32 message_length;                              //
        read(connfd, &message_length, 4);                //
        message_length = ntohl(message_length);          //
        u8 message[message_length];                      //
        read(connfd, message, message_length);           // mensagem
        read(connfd, &frame_end, 1);    // frame-end
        basic_publish(connfd, queue_name, message, queues);
        return 1;
    }
}


void connection_establish(char recvline[], int connfd){
    ////////// CONNECTION ESTABLISH - INI //////////
    
    ssize_t n;
    if((n=read(connfd, recvline, 8)) > 0) {
        if(strcmp(recvline, "\x41\x4d\x51\x50\x00\x00\x09\x01")==0){
            printf("AMQP protocol header received\n\n");
    
            printf("#===================================#\n");
            printf("|       ESTABELECENDO CONEXAO       |\n\n");
    
            // Connection.start
            u8 connection_start[] = {
                0x01,                       //  type: method (1)
                0x00, 0x00,                 //  channel: 0
                0x00, 0x00, 0x00, 0x1c,     //  length = 28
                0x00, 0x0a,                 //  class: connnection (10)
                0x00, 0x0a,                 //  method: start (10)
                0x00,                       //  version-major: 0
                0x09,                       //  version-minor: 9
                0x00, 0x00, 0x00, 0x00,     //  server-properties length
                0x00, 0x00, 0x00, 0x05,     //  mechanisms length
                'P', 'L', 'A', 'I', 'N',    //  mechanisms
                0x00, 0x00, 0x00, 0x05,     //  locales length
                'e', 'n', '_', 'U', 'S',    //  locales
                0xce                        //  frame-end
            };
            printf("Connection.Start sent\n\n");
            write(connfd, connection_start, sizeof(connection_start));
    
            // Connection.start -ok
            printf("Connection.Start-OK received\n");
            skip_frame(connfd);
    
            // Connection.tune
            u8 connection_tune[] = {
                0x01,                       // type: method (1)
                0x00, 0x00,                 // channel: 0
                0x00, 0x00, 0x00, 0x0c,     // length = 12
                0x00, 0x0a,                 // class: connnection (10)
                0x00, 0x1e,                 // method: tune (30)
                0x07, 0xff,                 // channel-max: 2047
                0x00, 0x02, 0x00, 0x00,     // frame-max: 131072
                0x00, 0x3c,                 // heartbeat: 60 (não vamos nos preocupar com isso nesse ep)
                0xce                        // frame-end
            };  
            printf("Connection.Tune sent\n\n");
            write(connfd, connection_tune, sizeof(connection_tune));
    
            // Connection.tune -ok
            printf("Connection.Tune-OK received\n");
            skip_frame(connfd);
    
            // Connection.open
            printf("Connection.Open received\n");
            skip_frame(connfd);
    
            // Connection.open -ok
            u8 connection_open_ok[] = {
                0x01,                       // type: method (1)
                0x00, 0x00,                 // channel: 0
                0x00, 0x00, 0x00, 0x05,     // length = 5
                0x00, 0x0a,                 // class: connnection (10)
                0x00, 0x29,                 // method: open-ok (41)
                0x00,                       // arguments length
                0xce                        // frame-end
            };
            printf("Connection.Open-OK sent\n\n");
            write(connfd, connection_open_ok, sizeof(connection_open_ok));
    
            // Channel.open
            printf("Channel.Open received\n");
            skip_frame(connfd);
    
            // Channel.open -ok
            u8 channel_open_ok[] = {
                0x01,                       // type: method (1)
                0x00, 0x01,                 // channel: 1
                0x00, 0x00, 0x00, 0x08,     // length = 8
                0x00, 0x14,                 // class: channel (20)
                0x00, 0x0b,                 // method: open-ok (11)
                0x00, 0x00, 0x00, 0x00,     // arguments length
                0xce                        // frame-end
            };
            printf("Channel.Open-OK sent\n\n");
            write(connfd, channel_open_ok, sizeof(channel_open_ok));
        }
    
        printf("|       CONEXAO ESTABELECIDA        |\n");
        printf("#===================================#\n\n");
    }

} ////////// CONNECTION ESTABLISH - END //////////


void connection_close(int connfd){
    ////////// CONNECTION CLOSE - INI //////////
    
    // Connection.close
    printf("Connection.Close received\n");
    skip_frame(connfd);

    // Connection.close -ok
    u8 connection_close_ok[] = {
        0x01,                       // type: method (1)
        0x00, 0x00,                 // channel: 0
        0x00, 0x00, 0x00, 0x04,     // length = 4
        0x00, 0x0a,                 // class: connnection (10)
        0x00, 0x33,                 // method: close-ok (51)
        0xce                        // frame-end
    };
    printf("Connection.Close-OK sent\n\n");
    write(connfd, connection_close_ok, sizeof(connection_close_ok));

} ////////// CONNECTION CLOSE - END //////////


void queue_declare(int connfd, char queue_name[], hash* queues){
    ////////// DECLARE QUEUE - INI //////////
    
    printf("#===================================#\n");
    printf("|          DECLARANDO FILA          |\n\n");

    // Cria a fila
    pthread_mutex_lock(&mutex);
    queue* q = new_queue();
    add(queues, queue_name, q);
    pthread_mutex_unlock(&mutex);

    // Queue.declare -ok
    u8 queue_declare_ok [12+strlen(queue_name)-1+9];
    u8 queue_declare_ok_aux[] = {
        0x01,                       // type: method (1)
        0x00, 0x01,                 // channel: 1
    };
    memcpy(queue_declare_ok, queue_declare_ok_aux, sizeof(queue_declare_ok_aux));
    u32 length = 13+strlen(queue_name)-1;//
    queue_declare_ok[3] = length>>24;    //
    queue_declare_ok[4] = length>>16;    //
    queue_declare_ok[5] = length>>8;     //
    queue_declare_ok[6] = length;        // length
    u8 queue_declare_ok_aux2[] = {      
        0x00, 0x32,                 // class: queue (50)
        0x00, 0x0b,                 // method: declare-ok (11)
    };
    memcpy(queue_declare_ok+7, queue_declare_ok_aux2, sizeof(queue_declare_ok_aux2));
    queue_declare_ok[11] = strlen(queue_name)-1;
    memcpy(queue_declare_ok+12, queue_name, strlen(queue_name)-1);
    u8 queue_declare_ok_aux3[] = {
        0x00, 0x00, 0x00, 0x00,     // message-count
        0x00, 0x00, 0x00, 0x00,     // consumer-count
        0xce                        // frame-end
    };
    memcpy(queue_declare_ok+12+strlen(queue_name)-1, queue_declare_ok_aux3, sizeof(queue_declare_ok_aux3));
    printf("Queue.Declare-OK sent\n\n");
    write(connfd, queue_declare_ok, sizeof(queue_declare_ok));

    // Channel.close
    printf("Channel.Close received\n");
    skip_frame(connfd);

    // Channel.close -ok
    u8 channel_close_ok[] = {
        0x01,                       // type: method (1)
        0x00, 0x01,                 // channel: 1
        0x00, 0x00, 0x00, 0x04,     // length = 4
        0x00, 0x14,                 // class: channel (20)
        0x00, 0x29,                 // method: close-ok (41)
        0xce                        // frame-end
    };
    printf("Channel.Close-OK sent\n\n");
    write(connfd, channel_close_ok, sizeof(channel_close_ok));

    connection_close(connfd);

    printf("|          FILA DECLARADA           |\n");
    printf("#===================================#\n\n");
    
} ////////// DECLARE QUEUE - END //////////


void queue_consume(int connfd, char queue_name[], hash* queues){
    ////////// CONSUME QUEUE - INI //////////
    
    printf("#===================================#\n");
    printf("|    CONSUMO DE FILA REQUISITADO    |\n\n");

    // Inscreve o cliente na fila
    pthread_mutex_lock(&mutex);
    queue* q = find(queues, queue_name);
    if(q==NULL){
        printf("Queue does not exist\n");
        exit(1);
    }
    enqueue(q, connfd);
    pthread_mutex_unlock(&mutex);

    // Basic.consume -ok
    u8 basic_consume_ok[] = {
        0x01,                       // type: method (1)
        0x00, 0x01,                 // channel: 1
        0x00, 0x00, 0x00, 0x05,     // length = 5
        0x00, 0x3c,                 // class: basic (60)
        0x00, 0x15,                 // method: consume-ok (21)
        0x00,                       // consumer-tag length
        0xce                        // frame-end
    };
    printf("Basic.Consume-OK sent\n\n");
    write(connfd, basic_consume_ok, sizeof(basic_consume_ok));

    printf("|     CONSUMO DE FILA CONCEDIDO     |\n");
    printf("#===================================#\n\n");

} ////////// CONSUME QUEUE - END //////////


void basic_publish(int connfd, char queue_name[], char message[], hash*queues){
    ////////// PUBLISH - INI //////////
    printf("#===================================#\n");
    printf("|      PUBLICACAO REQUISITADA       |\n\n");

    // Channel.close
    printf("Channel.Close received\n");
    skip_frame(connfd);

    // Channel.close -ok
    u8 channel_close_ok[] = {
        0x01,                       // type: method (1)
        0x00, 0x01,                 // channel: 1
        0x00, 0x00, 0x00, 0x04,     // length = 4
        0x00, 0x14,                 // class: channel (20)
        0x00, 0x29,                 // method: close-ok (41)
        0xce                        // frame-end
    };
    printf("Channel.Close-OK sent\n\n");
    write(connfd, channel_close_ok, sizeof(channel_close_ok));

    // Basic.deliver (retornado para o cliente)
    int deliver_size = 23+strlen(queue_name)-1+1 +23 +7+sizeof(message)+1;
    u8 *basic_deliver = malloc(deliver_size);
    u8 basic_deliver_aux[] = {
        0x01,                       // type: method (1)
        0x00, 0x01,                 // channel: 1
    };
    memcpy(basic_deliver, basic_deliver_aux, sizeof(basic_deliver_aux));
    u32 length = 16+strlen(queue_name)-1;
    basic_deliver[3] = length>>24;    //
    basic_deliver[4] = length>>16;    //
    basic_deliver[5] = length>>8;     //
    basic_deliver[6] = length;        // length
    u8 basic_deliver_aux2[] = {
        0x00, 0x3c,                 // class: basic (60)
        0x00, 0x3c,                 // method: deliver (60)
        0x00,                       // consumer-tag length
        0x00, 0x00, 0x00, 0x00,     //
        0x00, 0x00, 0x00, 0x01,     // delivery-tag
        0x00,                       // redelivered
        0x00,                       // exchange length
    };
    memcpy(basic_deliver+7, basic_deliver_aux2, sizeof(basic_deliver_aux2));
    basic_deliver[22] = strlen(queue_name)-1;    // queue name length
    memcpy(basic_deliver+23, queue_name, strlen(queue_name)-1);    // queue name
    basic_deliver[23+strlen(queue_name)-1] = 0xce;    // frame-end
    u8 basic_deliver_aux3[] = {
        0x02,                       // type
        0x00, 0x01,                 // channel
        0x00, 0x00, 0x00, 0x0f,     // length
        0x00, 0x3c,                 // class: basic (60)
        0x00, 0x00,                 // weight
    };
    memcpy(basic_deliver+23+strlen(queue_name)-1+1, basic_deliver_aux3, sizeof(basic_deliver_aux3));
    u64 body_size = sizeof(message);
    int queue_name_size = strlen(queue_name)-1;
    basic_deliver[23+queue_name_size+1+11] = body_size>>56;    //
    basic_deliver[23+queue_name_size+1+12] = body_size>>48;    //
    basic_deliver[23+queue_name_size+1+13] = body_size>>40;    //
    basic_deliver[23+queue_name_size+1+14] = body_size>>32;    //
    basic_deliver[23+queue_name_size+1+15] = body_size>>24;    //
    basic_deliver[23+queue_name_size+1+16] = body_size>>16;    //
    basic_deliver[23+queue_name_size+1+17] = body_size>>8;     //
    basic_deliver[23+queue_name_size+1+18] = body_size;        //
    basic_deliver[23+queue_name_size+1+19] = 0x10;             //
    basic_deliver[23+queue_name_size+1+20] = 0x00;             // property flags
    basic_deliver[23+queue_name_size+1+21] = 0x01;             // properties
    basic_deliver[23+queue_name_size+1+22] = 0xce;             // frame-end
    basic_deliver[23+queue_name_size+1+23] = 0x03;             // type
    basic_deliver[23+queue_name_size+1+24] = 0x00;             //
    basic_deliver[23+queue_name_size+1+25] = 0x01;             // channel
    u32 message_length = sizeof(message);
    basic_deliver[23+queue_name_size+1+26] = message_length>>24;    //
    basic_deliver[23+queue_name_size+1+27] = message_length>>16;    //
    basic_deliver[23+queue_name_size+1+28] = message_length>>8;     //
    basic_deliver[23+queue_name_size+1+29] = message_length;        //
    memcpy(basic_deliver+23+queue_name_size+1+30, message, sizeof(message));
    basic_deliver[23+queue_name_size+1+30+sizeof(message)] = 0xce;    // frame-end
    printf("Basic.Deliver sent\n\n");
    deliver_round_robin(basic_deliver, queue_name, queues, deliver_size);
    //printf(" \"%s\"\n", message);
    
    connection_close(connfd);

    printf("|         PUBLICACAO FEITA          |\n");
    printf("#===================================#\n\n");
} ////////// PUBLISH - END //////////


void deliver_round_robin(char deliver_frame[], char queue_name[], hash* queues, int deliver_size){
    // Entrega a mensagem para o primeiro da fila e troca ele para último
    queue *q = find(queues, queue_name);
    if(q==NULL){
        printf("A fila não existe!\n\n");
        return;
    }
    int connfd = first(q);
    if(connfd==NULL){
        printf("Fila vazia, mensagem não entregue!\n\n");
        return;
    }
    
    printf("Mensagem entregue na fila \"%s\", port %d\n\n", queue_name, connfd);
    write(connfd, deliver_frame, deliver_size);
}


typedef struct{
    int lfd;
    int cfd;
    char* rl;
    hash* h;
}arguments;

arguments* new_args(int lfd, int cfd, char* rl, hash* h){
    arguments* args = malloc(sizeof(arguments));
    args->lfd = lfd;
    args->cfd = cfd;
    args->rl = rl;
    args->h = h;
    return args;
}

void* main_client(void* p_args){
    /**** PROCESSO FILHO ****/
    arguments args = *(arguments*)p_args;
    int listenfd = args.lfd;
    int connfd = args.cfd;
    char* recvline = args.rl;
    hash* queues = args.h;
    free(p_args);


    printf("[Uma conexão aberta]\n\n");
    
    /* Agora pode ler do socket e escrever no socket. Isto tem
        * que ser feito em sincronia com o cliente. Não faz sentido
        * ler sem ter o que ler. Ou seja, neste caso está sendo
        * considerado que o cliente vai enviar algo para o servidor.
        * O servidor vai processar o que tiver sido enviado e vai
        * enviar uma resposta para o cliente (Que precisará estar
        * esperando por esta resposta) 
        */

    /* ========================================================= */
    /* ========================================================= */
    /*                         EP1 INÍCIO                        */
    /* ========================================================= */
    /* ========================================================= */
    /* TODO: É esta parte do código que terá que ser modificada
    */
    
    int stop_connection=0;
    connection_establish(recvline, connfd);
    stop_connection = make_request(recvline, connfd, queues);
    
    if(!stop_connection){
        while(1){
            if(read(connfd, recvline, 1)==0){
                pthread_mutex_lock(&mutex);
                char* queue_name = find_and_dequeue(queues, connfd);
                printf("Cliente desconectou da fila \"%s\", port %d\n\n", queue_name, connfd);
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
    }

    /* ========================================================= */
    /* ========================================================= */
    /*                         EP1 FIM                           */
    /* ========================================================= */
    /* ========================================================= */

    /* Após ter feito toda a troca de informação com o cliente,
        * pode finalizar o processo filho
        */
    printf("[Uma conexão fechada]\n\n");
    return NULL;
}


int main (int argc, char **argv) {
    hash* queues = new_hash();

    /* Os sockets. Um que será o socket que vai escutar pelas conexões
     * e o outro que vai ser o socket específico de cada conexão
     */
    int listenfd, connfd;
    /* Informações sobre o socket (endereço e porta) ficam nesta struct
     */
    struct sockaddr_in servaddr;
    /* Retorno da função fork para saber quem é o processo filho e
     * quem é o processo pai
     */
    // pid_t childpid;
    /* Armazena linhas recebidas do cliente
     */
    char recvline[MAXLINE + 1];
    /* Armazena o tamanho da string lida do cliente
     */
    // ssize_t n;
   
    if (argc != 2) {
        fprintf(stderr,"Uso: %s <Porta>\n",argv[0]);
        fprintf(stderr,"Vai rodar um servidor de echo na porta <Porta> TCP\n");
        exit(1);
    }

    /* Criação de um socket. É como se fosse um descritor de arquivo.
     * É possível fazer operações como read, write e close. Neste caso o
     * socket criado é um socket IPv4 (por causa do AF_INET), que vai
     * usar TCP (por causa do SOCK_STREAM), já que o AMQP funciona sobre
     * TCP, e será usado para uma aplicação convencional sobre a Internet
     * (por causa do número 0)
     */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket :(\n");
        exit(2);
    }

    /* Agora é necessário informar os endereços associados a este
     * socket. É necessário informar o endereço / interface e a porta,
     * pois mais adiante o socket ficará esperando conexões nesta porta
     * e neste(s) endereços. Para isso é necessário preencher a struct
     * servaddr. É necessário colocar lá o tipo de socket (No nosso
     * caso AF_INET porque é IPv4), em qual endereço / interface serão
     * esperadas conexões (Neste caso em qualquer uma -- INADDR_ANY) e
     * qual a porta. Neste caso será a porta que foi passada como
     * argumento no shell (atoi(argv[1])). No caso do servidor AMQP,
     * utilize a porta padrão do protocolo que você deve descobrir
     * lendo a especificaçao dele ou capturando os pacotes de conexões
     * ao RabbitMQ com o Wireshark
     */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(atoi(argv[1]));
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind :(\n");
        exit(3);
    }

    /* Como este código é o código de um servidor, o socket será um
     * socket que escutará por conexões. Para isto é necessário chamar
     * a função listen que define que este é um socket de servidor que
     * ficará esperando por conexões nos endereços definidos na função
     * bind.
     */
    if (listen(listenfd, LISTENQ) == -1) {
        perror("listen :(\n");
        exit(4);
    }

    printf("[Servidor no ar. Aguardando conexões na porta %s]\n",argv[1]);
    printf("[Para finalizar, pressione CTRL+c ou rode um kill ou killall]\n");
   
    /* O servidor no final das contas é um loop infinito de espera por
     * conexões e processamento de cada uma individualmente
     */
	for (;;) {
        /* O socket inicial que foi criado é o socket que vai aguardar
         * pela conexão na porta especificada. Mas pode ser que existam
         * diversos clientes conectando no servidor. Por isso deve-se
         * utilizar a função accept. Esta função vai retirar uma conexão
         * da fila de conexões que foram aceitas no socket listenfd e
         * vai criar um socket específico para esta conexão. O descritor
         * deste novo socket é o retorno da função accept.
         */

        if ((connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) == -1 ) {
            perror("accept :(\n");
            exit(5);
        }
      
        /* Agora o servidor precisa tratar este cliente de forma
         * separada. Para isto é criado um processo filho usando a
         * função pthread_create. O filho tem que processar a requisição
         * do cliente. O pai tem que voltar no loop para continuar 
         * aceitando novas conexões. Se o cliente encerrar suas atividades,
         * a thread acaba e não nos preocupamos mais com ela.
         */
        
        pthread_t cliente;
        arguments *args;
        args = new_args(listenfd, connfd, recvline, queues);
        pthread_create(&cliente, NULL, main_client, args);
    }
    
    /**** PROCESSO PAI ****/
    /* Se for o pai, a única coisa a ser feita é fechar o socket
     * connfd (ele é o socket do cliente específico que será tratado
     * pelo processo filho)
     */
    close(connfd);
    close(listenfd);
    
    exit(0);
}
