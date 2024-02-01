#include<iostream>
#include<stdlib.h>
#include"vetorOrdenado.h"

using namespace std;



int buscaBin(noVO vetor[], int ini, int fim, Key key, bool * achou){
    int mid;
    mid = (ini+fim) / 2;
    if(vetor[mid].key.compare(key)==0){
        * achou = true;
        return mid;
    }
    if(ini>=fim){
        * achou = false;
        return mid;
    }
    if(vetor[mid].key>key) return buscaBin(vetor, ini, mid-1, key, achou);
    else return buscaBin(vetor, mid+1, fim, key, achou);
}



vetorOrdenado::vetorOrdenado(){
    vetor = new noVO[2];
    size = 2;
    nPalavras=0;
}



vetorOrdenado::~vetorOrdenado(){
    //delete(vetor);
}



void vetorOrdenado::resize(){
    size *= 2;
    noVO * aux = new noVO[size];
    for(int i=0; i<size/2; i++){
        aux[i] = vetor[i];
    }
    //delete(vetor);
    vetor = aux;
}



void vetorOrdenado::empurra(int pos){
    for(int i=nPalavras; i>pos; i--){
        vetor[i] = vetor[i-1];
    }
}



void vetorOrdenado::add(Key key, item val){
    bool achou = false;

    if(nPalavras==0){
        vetor[0].key = key;
        vetor[0].val = val;
        nPalavras++;
    }

    else{
        int pos = buscaBin(vetor, 0, nPalavras-1, key, &achou);

        if(achou){
            vetor[pos].val.nOcorrencias++;
        }

        else{
            if(size == nPalavras) resize();
            if(vetor[pos].key > key){
                empurra(pos);
                vetor[pos].key = key;
                vetor[pos].val = val;
            }
            else{
                empurra(pos+1);
                vetor[pos+1].key = key;
                vetor[pos+1].val = val;
            }
            nPalavras++;
        }
    }
}



item vetorOrdenado::value(Key key){
    bool achou;

    if(nPalavras==0){
        item nulo;
        return nulo;
    }

    int pos = buscaBin(vetor, 0, nPalavras-1, key, &achou);
    if(achou) return vetor[pos].val;
    else{
        item nulo;
        return nulo;
    }
}