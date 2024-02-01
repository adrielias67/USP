#include <stdio.h>
#include <stdlib.h>

int main() {
    int num, tentativas, opcao;             //"opcao" é a opcao escolhida no menu
    int depuracao=0, jogosjogados=0, jogosvencidos=0, parar=0;
    int n1, n2, n3, n;             //algarismos 1 2 e 3 do numero, e chute de algarismo
    int n1apuracao, n2apuracao, n3apuracao;        // guarda n1 n2 e n3 para mostrar quando a apuracao esta ligada, ou nos acertos
    srand(time(NULL));
    printf("Bem-vindo ao jogo da forca!!\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    while(parar == 0){
        if(depuracao == 0) printf("[ depuracao = DESLIGADO");
        else printf("[ depuracao = LIGADO");
        printf(" / jogos jogados = %d ]\n", jogosjogados);
        printf(" 1. Continuar a jogar\n 2. Alternar modo depuracao e continuar a jogar\n 3. Parar\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        if(opcao != 3){     
            num = rand() % 1000;
            n1 = num / 100;         // separar a casa da centena (n1)
            n2 = num % 100 / 10;    // separar a casa da dezena (n2)
            n3 = num % 10;          // separar a casa de unidade (n3)
            n1apuracao = n1;
            n2apuracao = n2;        // guarda os valores dos algarismos para mostrar nos digitos acertados ate o momento e na apuracao
            n3apuracao = n3;
            if(opcao == 2) depuracao = 1 - depuracao;     
            for (int i=6; i>0; i--){
                if (depuracao == 1) printf("Numero a ser adivinhado: %d %d %d\n", n1apuracao, n2apuracao, n3apuracao);
                printf("Restam %d tentativas\n", i);
                printf("Sua proxima tentativa (digito de 0 a 9): ");
                scanf("%d", &n);
                if(n == n1) n1 = -1;
                if(n == n2) n2 = -1;        
                if(n == n3) n3 = -1;
                printf("Voce ja acertou os seguintes digitos: ");
                if(n1<0) printf("%d ", n1apuracao);     
                else printf("_ ");
                if(n2<0) printf("%d ", n2apuracao);
                else printf("_ ");
                if(n3<0) printf("%d\n\n", n3apuracao);
                else printf("_\n\n");
                if (n1<0 && n2<0 && n3<0){
                    printf("Voce VENCEU!\n\n");
                    jogosvencidos ++;
                    jogosjogados ++;
                    i = 0;
                }
                else if(i == 1){
                    printf("Voce PERDEU!\n\n");
                    jogosjogados ++;
                }
            }
        }
        else{
            parar = 1;
            printf("Voce jogou %d jogos e venceu %d vezes!", jogosjogados, jogosvencidos);
        }
    }

}
