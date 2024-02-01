#include <iostream>

using namespace std;


// Verifica se o começo do fragmento "a" encaixa no final do fragmento "b".
// Retorna o o número de letras em comum desse encaixe (overlap).
// Caso não haja encaixe, retorna 0.
// k é o mesmo do enunciado.
int encaixaOverlap(string a, string b, int k);

// Monta uma lista de adjacência em um arquivo.
// Recebe um vetor com os fragmentos, o tamanho dele, e o nome do arquivo.
// Cada fragmento é representado pelo seu índice no vetor passado como argumento.
// O formato de cada linha dessa lista é: u v o, onde "u" e "v" são os índices dos
// fragmentos (v encaixa no final de u), e "o" é o overlap entre a conexão deles.
// k é o mesmo do enunciado.
// Assim que a lista não for mais ser usada, o arquivo é deletado.
void montaListaFragmentos(string fragmentos[], int tamanho, int k, string filename);