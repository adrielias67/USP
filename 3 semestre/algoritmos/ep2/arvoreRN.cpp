#include<iostream>
#include<stdlib.h>
#include"arvoreRN.h"

using namespace std;



item buscaBin(noRN * raiz, Key key){
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


noRN * rodaEsq(noRN * no){
    noRN * aux;
    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;
}


noRN * rodaDir(noRN * no){
    noRN * aux;
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    return aux;
}



arvoreRN::arvoreRN(){
    raiz = nullptr;
}



arvoreRN::~arvoreRN(){

}



noRN * arvoreRN::insere(noRN * no, Key key, item val){
    /* insere na árvore */
    noRN * novo = new noRN;
    novo->key = key;
    novo->val = val;
    
    /*árvore vazia*/
    if(no==nullptr){
        no = novo;
        novo->preto = true;
        return no;
    }

    /*elemento está na árvore */
    if(no->key == key){
        no->val.nOcorrencias++;
        return no;
    }

    /*insere recursivamente*/
    else if(no->key > key){
        no->esq = insere(no->esq, key, val);
    }
    else no->dir = insere(no->dir, key, val);


    /* corrige a rubro-negra */
    /*caso folha*/
    if(no->dir==nullptr && no->esq==nullptr) return no;

    /*caso do tio*/
    if(no->dir!=nullptr && no->esq!=nullptr){
        /*tio vermelho na esquerda (troca)*/
        if(!no->esq->preto && !no->dir->preto){
            if((no->dir->dir!=nullptr && !no->dir->dir->preto) || (no->dir->esq!=nullptr && !no->dir->esq->preto)){
                raiz->preto = false;
                raiz->dir->preto = true;
                raiz->esq->preto = true;
                return no;
            }
        }
        /*tio vermelho na direita (troca)*/
        if(!no->esq->preto && !no->dir->preto){
            if((no->esq->dir!=nullptr && !no->esq->dir->preto) || (no->esq->esq!=nullptr && !no->esq->esq->preto)){
                raiz->preto = false;
                raiz->dir->preto = true;
                raiz->esq->preto = true;
                return no;
            }
        }
    }

    /*tio preto na esquerda (gira)*/
    if((no->esq==nullptr || (no->esq!=nullptr&&no->esq->preto)) && (no->dir!=nullptr&&!no->dir->preto)){
        //giro unico
        if(no->dir->dir!=nullptr && !no->dir->dir->preto){
            no = rodaEsq(no);
            no->esq->preto = false;
            no->preto = true;
            return no;
        }
        //giro duplo
        if(no->dir->esq!=nullptr && !no->dir->esq->preto){
            no->dir = rodaDir(no->dir);
            no = rodaEsq(no);
            no->esq->preto = false;
            no->preto = true;
            return no;
        }
    }

    /*tio preto na direita (gira)*/
    if((no->dir==nullptr || (no->dir!=nullptr&&no->dir->preto)) && (no->esq!=nullptr&&!no->esq->preto)){
        //giro unico
        if(no->esq->esq!=nullptr && !no->esq->esq->preto){
            no = rodaDir(no);
            no->dir->preto = false;
            no->preto = true;
            return no;
        }
        //giro duplo
        if(no->esq->dir!=nullptr && !no->esq->dir->preto){
            no->esq = rodaEsq(no->esq);
            no = rodaDir(no);
            no->dir->preto = false;
            no->preto = true;
            return no;
        }
    }

    /*caso da raiz*/
    if(no==raiz && !no->preto){
        if((no->dir!=nullptr && !no->dir->preto) || (no->esq!=nullptr && !no->esq->preto)) raiz->preto = true;
    }

    return no;
}



void arvoreRN::add(Key key, item val){
    raiz = insere(raiz, key, val);
}



item arvoreRN::value(Key key){
    return (buscaBin(raiz, key));
}