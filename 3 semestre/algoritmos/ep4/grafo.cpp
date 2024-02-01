#include <iostream>
#include "grafo.h"
#include <fstream>
#include <algorithm>

using namespace std;




bool aceita(noLeitura no, char c){
    // letra
    if(no.tipo==0){
        if(c==no.letra) return true;
        return false;
    }

    // conjunto
    else if(no.tipo==1){
        for(int i=0; i<no.conjunto.size(); i++){
            if(c==no.conjunto[i]) return true;
        }
        return false;
    }

    // ^conjunto
    else if(no.tipo==2){
        for(int i=0; i<no.conjunto.size(); i++){
            if(c==no.conjunto[i]) return false;
        }
        return true;
    }

    // intervalo
    else if(no.tipo==3){
        if(c>=no.ini && c<=no.fim) return true;
        return false;
    }

    // ^intervalo
    else if(no.tipo==4){
        if(c>=no.ini && c<=no.fim) return false;
        return true;
    }

    // coringa
    else if(no.tipo==5) return true;

    // fim da palavra
    else return false;
}



grafo::grafo(int vertices){
    adj = new vector<int> [vertices+1];    //+1 para o vértice de fim de palavra
    nosLeitura = new noLeitura[vertices+1];    //+1 para o vértice de fim de palavra
    for(int i=0; i<vertices; i++){
        nosLeitura[i].tipo = -1;    //inicializa como sendo não leitura
    }
    nosLeitura[vertices].tipo = 6;    //nó de fim de palavra
    V = vertices+1;
}


grafo::~grafo(){
}


void grafo::incluiArco(int u, int v){
    adj[u].push_back(v);
}