#include <iostream>
#include <vector>
#include <utility>

using namespace std;



// Struct para um nó de leitura no grafo
typedef struct{
    // tipo0=letra // tipo1=[conjunto] // tipo2=[^conjunto] // tipo3=[intervalo] // tipo4=[^intervalo] // tipo5=coringa // tipo6=fim de palavra // tipo-1=não é nó de leitura
    int tipo;

    // tipo letra
    char letra;

    // tipo conjunto
    vector<char> conjunto;

    // tipo intervalo
    char ini;
    char fim;

}noLeitura;


// Retorna se um caractere é aceito por um nó de leitura dado
bool aceita(noLeitura no, char c);


class grafo{
    public:
        // Montador de grafo, de acordo com o número de letras na expreg
        grafo(int vertices);
        
        ~grafo();

        // Número de vértices
        int V;

        // Inclui um arco de u para v na lista de adjacência do grafo
        void incluiArco(int u, int v);

        // Lista de adjacência
        vector<int> *adj;

        // Vetor de nós do grafo.
        // Caso seja um de leitura, armazena seu tipo e especificações
        noLeitura *nosLeitura;
};