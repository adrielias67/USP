#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// Uma aresta é da forma: (peso, (u, v)),
// que vai de u para v, com um peso.
using aresta = pair<int, pair<int,int>>;



class grafo{
    private:
        int nVertices; 

        // Lista de adjacência
        // adj[u] = (v, peso) - indica uma aresta de u para v, com peso.
        vector<pair<int,int>> *adj;

        // Vetor que guarda a string dos fragmentos.
        string *fragmentos;
        
        // Vetor que guarda o representante de cada vétice.
        int *rep;

    public:
        // Constrói um grafo, inicializando-o com o número 
        // de vértices, e vetor de fragmentos.
        grafo(string fragmentos[], int vertices);
        // 
        ~grafo();

        // Monta o grafo, utilizando as arestas mais pesadas que não formam circuito.
        // Recebe o arquivo com a lista de adjacência gerada pela classe palavra.
        void montaGrafo(string filename);

        // Devolve a reconstrução do DNA, maior caminho no grafo.
        string remonta();
};