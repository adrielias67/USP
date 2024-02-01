#include<iostream>
#include<stdlib.h>
#include"arvore23.h"

using namespace std;



item busca23(no23 * no, Key key){
    if(no==nullptr){
        item nulo;
        return nulo;
    }

    else if(no->key1 > key) return busca23(no->esq, key);

    else if(no->key1 == key){
        return no->val1;
    }

    /*2-nó*/
    else if(!no->tresNo){
        return busca23(no->dir, key);
    }

    /*3-nó*/
    else{
        if(no->key2 > key) return busca23(no->mid, key);
        if(no->key2 == key){
            return no->val2;
        }
        else return busca23(no->dir, key);
    }    
}



arvore23::arvore23(){
    raiz = nullptr;
}



arvore23::~arvore23(){

}



no23 * arvore23::insere(no23 * no, Key key, item val, bool * cresceu){
    //lado inserido == 'e': esquerda // lado inserido == 'm': meio // lado inserido == 'd': direita
    char ladoInserido;

    /* insere na árvore */
    
    /*subárvore vazia*/
    if(no==nullptr){
        no23 * novo = new no23;
        novo->key1 = key;
        novo->val1 = val;
        no = novo;
        * cresceu = true;
        return no;
    }

    /*elemento está na árvore */
    else if(no->key1.compare(key)==0){
        no->val1.nOcorrencias++;
        * cresceu = false;
        return no;
    }
    else if(no->tresNo && no->key2.compare(key)==0){
        no->val2.nOcorrencias++;
        * cresceu = false;
        return no;
    }

    /*inserção em folha 2-nó*/
    else if(no->esq==nullptr && !no->tresNo){
        /*insere na key 2*/
        if(no->key1 < key){
            no->key2 = key;
            no->val2 = val;
            no->tresNo = true;
            * cresceu = false;
            return no;
        }
        /*insere na key 1*/
        else{
            no->key2 = no->key1;
            no->val2 = no->val1;
            no->key1 = key;
            no->val1 = val;
            no->tresNo = true;
            * cresceu = false;
            return no;
        }
    }

    /*insere recursivamente*/
    else if(no->key1 > key){
        ladoInserido = 'e';
        no->esq = insere(no->esq, key, val, cresceu);
    }
    else if(!no->tresNo){
        ladoInserido = 'd';
        no->dir = insere(no->dir, key, val, cresceu);
    }
    else{
        if(no->key2 > key){
            ladoInserido = 'm';
            no->mid = insere(no->mid, key, val, cresceu);
        }
        else{
            ladoInserido = 'd';
            no->dir = insere(no->dir, key, val, cresceu);
        }
    }


    /* corrige a 2-3 */
    if(* cresceu){
        /*cresceu, e insere num 2-nó*/
        if(!no->tresNo){
            /*vem da direita*/
            if(ladoInserido == 'd'){
                no->tresNo = true;
                no->key2 = no->dir->key1;
                no->val2 = no->dir->val1;
                no->mid = no->dir->esq;
                no->dir = no->dir->dir;
                * cresceu = false;
                return no;
            }
            /*vem da esquerda*/
            else{
                no->tresNo = true;
                no->key2 = no->key1;
                no->val2 = no->val1;
                no->key1 = no->esq->key1;
                no->val1 = no->esq->val1;
                no->mid = no->esq->dir;
                no->esq = no->esq->esq;
                * cresceu = false;
                return no;
            }
        }

        /*cresceu e insere num 3-nó*/
        else{
            /*direita*/
            if(ladoInserido == 'd'){
                no23 * novaRaizDir = new no23;
                novaRaizDir->key1 = no->dir->key1;
                novaRaizDir->val1 = no->dir->val1;
                novaRaizDir->dir = no->dir->dir;
                novaRaizDir->esq = no->dir->esq;

                no23 * novaRaizEsq = new no23;
                novaRaizEsq->key1 = no->key1;
                novaRaizEsq->val1 = no->val1;
                novaRaizEsq->dir = no->mid;
                novaRaizEsq->esq = no->esq;

                no23 * novaRaiz = new no23;
                novaRaiz->key1 = no->key2;
                novaRaiz->val1 = no->val2;
                novaRaiz->dir = novaRaizDir;
                novaRaiz->esq = novaRaizEsq;

                * cresceu = true;
                return novaRaiz;
            }

            /*meio*/
            else if(ladoInserido == 'm'){
                no23 * novaRaizDir = new no23;
                novaRaizDir->key1 = no->key2;
                novaRaizDir->val1 = no->val2;
                novaRaizDir->dir = no->dir;
                novaRaizDir->esq = no->mid->dir;

                no23 * novaRaizEsq = new no23;
                novaRaizEsq->key1 = no->key1;
                novaRaizEsq->val1 = no->val1;
                novaRaizEsq->dir = no->mid->esq;
                novaRaizEsq->esq = no->esq;

                no23 * novaRaiz = new no23;
                novaRaiz->key1 = no->mid->key1;
                novaRaiz->val1 = no->mid->val1;
                novaRaiz->dir = novaRaizDir;
                novaRaiz->esq = novaRaizEsq;

                * cresceu = true;
                return novaRaiz;
            }

            /*esquerda*/
            else{
                no23 * novaRaizDir = new no23;
                novaRaizDir->key1 = no->key2;
                novaRaizDir->val1 = no->val2;
                novaRaizDir->dir = no->dir;
                novaRaizDir->esq = no->mid;

                no23 * novaRaizEsq = new no23;
                novaRaizEsq->key1 = no->esq->key1;
                novaRaizEsq->val1 = no->esq->val1;
                novaRaizEsq->dir = no->esq->dir;
                novaRaizEsq->esq = no->esq->esq;

                no23 * novaRaiz = new no23;
                novaRaiz->key1 = no->key1;
                novaRaiz->val1 = no->val1;
                novaRaiz->dir = novaRaizDir;
                novaRaiz->esq = novaRaizEsq;

                * cresceu = true;
                return novaRaiz;
            }
        }
    }
    return no;
}



void arvore23::add(Key key, item val){
    bool cresceu;
    raiz = insere(raiz, key, val, &cresceu);
    //cout << raiz->key1;
}



item arvore23::value(Key key){
    return (busca23(raiz, key));
}