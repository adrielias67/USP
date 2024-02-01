#include <iostream>

using namespace std;



class aviao{
    public:
        char * id;          // identificação do avião
        char * aeroporto;   // sigla do aeroporto de origem/destino
        int tempoEspera;    // tempo de espera de pouso ou de decolagem passado
        class aviao * prox; // ponteiro para o próximo avião da fila
        int tempo;          // tempo de combustível restante, ou de espera restante
        bool emergencia;    // 1 para voo de emergencia, 0 para voos regulares
        int ehraiz;         // 1 se é a raíz da fila, 0 caso contrário, e -1 se a fila estiver vazia

        aviao();
        ~aviao();
};

// retorna 1 para fila vazia, e 0 caso contrário
int filaVazia(aviao * raiz);
        
// dado um avião, inicializa suas informações e o coloca na fila, de acordo com sua prioridade
aviao * inicializa(aviao * raiz, char * id, char * aeroporto, int tempo, bool emergencia);
        
// remove o avião do início da fila, e devolve a nova raíz
aviao * removeInicio(aviao * raiz);

// remove o avião seguinte ao avião dado
void removeProx(aviao * raiz);

// diminui o tempo de todos os aviões por 1 e aumenta o tempo de espera por 1
void update(aviao * raiz);

// imprime os ids, aeroporto e tempo de todos os avioes em uma lista
void imprimeLista(aviao * raiz);

// soma os tempos de todos os avioes de uma lista
int somaTempo(aviao * raiz);

// retorna o tamanho da lista
int tamanho(aviao * raiz);