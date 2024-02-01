#include <iostream>
#include "grafo.h"
#include "palavra.h"

using namespace std;


int main(){
    int N, k;
    cin >> N >> k;
    string fragmentos[N], dna;

    for(int i=0; i<N; i++){
        cin >> fragmentos[i];
    }

    // cout << "Construindo adjacencias...\n";
    montaListaFragmentos(fragmentos, N, k, "lista");

    // cout << "Retirando arestas...\n";
    grafo shotgun(fragmentos, N);
    shotgun.montaGrafo("lista");

    // cout << "Achando maior caminho...\n";
    dna = shotgun.remonta();

    cout << dna << endl;
}