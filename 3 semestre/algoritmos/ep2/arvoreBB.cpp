#include<iostream>
#include<stdlib.h>
#include"arvoreBB.h"

using namespace std;



item buscaBin(noABB * raiz, Key key){
    if(raiz->key == key) return raiz->val;

    if(raiz->esq == nullptr){
        if(raiz->dir == nullptr){
            item nulo;
            return nulo;
        }
        else return buscaBin(raiz->dir, key);
    }
    else if(raiz->dir == nullptr){
        return buscaBin(raiz->esq, key);
    }

    else{
        if(key > raiz->key) return buscaBin(raiz->dir, key);
        else return buscaBin(raiz->esq, key);
    }
}



arvoreBB::arvoreBB(){
    raiz = nullptr;
}



arvoreBB::~arvoreBB(){

}



void arvoreBB::add(Key key, item val){
    noABB * novo = new noABB;
    novo->key = key;
    novo->val = val;
    
    if(raiz==nullptr){
        raiz = novo;
        return;
    }

    bool achou = false;
    noABB * aux = raiz;

    while(!achou){
        if(aux->key == key){
            aux->val.nOcorrencias++;
            achou = true;
        }

        else if(aux->key > key){
            if(aux->esq == nullptr){
                aux->esq = novo;
                achou = true;
            }
            else aux = aux->esq;
        }

        else{
            if(aux->dir == nullptr){
                aux->dir = novo;
                achou = true;
            }
            else aux = aux->dir;
        }
    }
}



item arvoreBB::value(Key key){
    return (buscaBin(raiz, key));
}