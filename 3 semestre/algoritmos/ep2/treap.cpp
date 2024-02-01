#include<iostream>
#include<stdlib.h>
#include"treap.h"
#include<random>
#include"time.h"

using namespace std;



item buscaBin(noTreap * raiz, Key key){
    if(raiz->key.compare(key)==0) return raiz->val;

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


noTreap * rodaEsq(noTreap * no){
    noTreap * aux;
    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;
}


noTreap * rodaDir(noTreap * no){
    noTreap * aux;
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    return aux;
}



treap::treap(){
    raiz = nullptr;
}



treap::~treap(){

}



noTreap * treap::insere(noTreap * no, Key key, item val){
    /* insere na árvore */
    noTreap * novo = new noTreap;
    novo->key = key;
    novo->val = val;
    
    if(no==nullptr){
        no = novo;
        return no;
    }

    if(no->key == key){
        no->val.nOcorrencias++;
        return no;
    }

    else if(no->key > key){
        no->esq = insere(no->esq, key, val);
    }
    else no->dir = insere(no->dir, key, val);
    

    /* corrige o heap */
    if(no->dir!=nullptr && no->heapValue < no->dir->heapValue) return rodaEsq(no);
    else if(no->esq!=nullptr && no->heapValue < no->esq->heapValue) return rodaDir(no);
    else return no;
}



void treap::add(Key key, item val){
    raiz = insere(raiz, key, val);
}



item treap::value(Key key){
    return (buscaBin(raiz, key));
}