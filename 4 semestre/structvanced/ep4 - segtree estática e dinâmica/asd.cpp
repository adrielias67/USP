#include <iostream>
#include <math.h>
#include <algorithm>
#include "asd.h"

using namespace std;



asd::asd(){
    for(int i=0; i<MAX; i++){
        raizes[i] = nullptr;
    }
    size = 0;
}


asd::~asd(){

}


vector<int> asd::Segments(int x){
    // para cada AS, adiciona os segmentos que contém x, corrigindo os seus índices
    // por exemplo, para os segmentos 1,2,3,4,5,6, temos a ASD:
    // as1:    as2:    as3:
    // nada    5,6     1,2,3,4
    // quando na realidade, seus índices em cada AS são:
    // as1:    as2:    as3:
    // nada    1,2     1,2,3,4

    int n_segs=0;
    for(int i=0; i<size; i++){
        if(raizes[i]!=nullptr) n_segs += pow(2,i);
    }

    vector<int> segs;
    for(int i=0; i<size; i++){
        
        if(raizes[i]!=nullptr){
            vector<int> segs_i = raizes[i]->Segments(raizes[i]->raiz, x);
            int diff = n_segs - raizes[i]->segmentos.size();
            for(int j=0;j<segs_i.size(); j++){
                segs_i[j] = segs_i[j] + diff;
            }
            segs.insert(segs.end(), segs_i.begin(), segs_i.end());
            n_segs -= raizes[i]->segmentos.size();
        
        }
    }
    
    return segs;
}


void asd::Insert(pair<int,int> s){
    int i=0;
    lista_seg nova;
    nova.push_back(s);

    while(raizes[i] != nullptr){
        lista_seg aux;
        aux.insert(aux.end(), raizes[i]->segmentos.begin(), raizes[i]->segmentos.end());

        nova.insert(nova.end(), aux.begin(), aux.end());
        
        delete raizes[i];
        raizes[i] = nullptr;
        i++;
    }

    reverse(nova.begin(), nova.end());
    raizes[i] = new as(nova);

    if(i==size) size++;
}


void asd::Print(){
    for(int i=0; i<size; i++){
        cout << "as " << i+1 << ":" << endl;
        if(raizes[i]!=nullptr) raizes[i]->Print(raizes[i]->raiz);
        else cout << "vazia" << endl;
        cout << endl;
    }
    cout << endl;
}