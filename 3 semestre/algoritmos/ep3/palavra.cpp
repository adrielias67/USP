#include <iostream>
#include "palavra.h"
#include <fstream>
#include <vector>
#include <utility>

using namespace std;


int encaixaOverlap(string a, string b, int k){
    int bLen = b.length();
    if(bLen<k || a.length()<k) return 0;

    int j=0, overlap=0;
    int menor = min(a.length(), b.length());
    bool encaixa = true;

    for(int i=k; i<menor; i++){
        while(j<i){    
            if(a[j] != b[bLen-i+j]){
                encaixa = false;
                break;
            }
            j++;
        }
        if(encaixa) overlap = i;
        encaixa = true;
        j=0;
    }

    return overlap;
}


void montaListaFragmentos(string fragmentos[], int tamanho, int k, string filename){
    int i, j, nArestas=0;
    vector<pair<pair<int,int> , int>> lista;

    for(i=0; i<tamanho; i++){
        for(j=0; j<tamanho; j++){
            if(i==j) continue;
            int overlap = encaixaOverlap(fragmentos[i], fragmentos[j], k);
            if(overlap==0) continue;
            lista.push_back(pair(pair(j,i) , overlap));
            nArestas++;
        }
    }

    fstream file(filename, ios::out);
    file << nArestas << "\n";
    for(i=0; i<nArestas; i++){
        file << lista[i].first.first << " " << lista[i].first.second << " " << lista[i].second << "\n";
    }
    file.close();
}