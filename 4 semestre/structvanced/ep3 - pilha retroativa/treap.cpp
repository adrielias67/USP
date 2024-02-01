#include <iostream>
#include <stdlib.h>
#include "treap.h"
#include <random>
#include "time.h"
#include <stack>

using namespace std;



treap::treap(){
    raiz = nullptr;
}


void destrutorR(noTreap* no){
    if(no==nullptr) return;
    destrutorR(no->esq);
    destrutorR(no->dir);
    delete no;
}

treap::~treap(){
    destrutorR(raiz);
}


int maxsum(noTreap* no){
    // retorna o tamanho do sufixo de soma máxima da subárvore
    return max(no->dir->sum_max, no->dir->sum + no->esq->sum_max);
}


noTreap* rodaEsq(noTreap* no){
    // roda os nós
    noTreap* aux;
    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    // corrige o nó
    no->sum = no->esq->sum + no->dir->sum;
    no->max = max(no->esq->max, no->dir->max);
    no->sum_max = maxsum(no);
    // corrige o aux
    aux->sum = aux->esq->sum + aux->dir->sum;
    aux->max = max(aux->esq->max, aux->dir->max);
    aux->sum_max = maxsum(aux);
    return aux;
}

noTreap* rodaDir(noTreap* no){
    // roda os nós
    noTreap* aux;
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    // corrige o nó
    no->sum = no->esq->sum + no->dir->sum;
    no->max = max(no->esq->max, no->dir->max);
    no->sum_max = maxsum(no);
    // corrige o aux
    aux->sum = aux->esq->sum + aux->dir->sum;
    aux->max = max(aux->esq->max, aux->dir->max);
    aux->sum_max = maxsum(aux);
    return aux;
}


noTreap* treap::Insert(noTreap* no, int chave, item val, int sum){
    // Insere recursivamente numa folha, e corrige o heap subindo
    // o argumento "sum" é usado para saber se é pop ou push

    /* insere na árvore */
    // árvore vazia
    if(no==nullptr){
        noTreap* novo = new noTreap;
        novo->chave = chave;
        novo->val = val;
        novo->sum = sum;
        novo->max = chave;
        if(sum==1) novo->sum_max = 1;
        else novo->sum_max = 0;
        novo->heapValue = 0;
        return novo;
    }

    // folha (empurra a folha em que chegou para baixo e insere o novo nó como irmão. cria um pai com valor de heap)
    if(no->esq==nullptr && no->dir==nullptr){
        noTreap* novo = new noTreap;
        noTreap* pai = new noTreap;
        novo->chave = chave;
        novo->val = val;
        novo->sum = sum;
        novo->max = chave;
        if(sum==1) novo->sum_max = 1;
        else novo->sum_max = 0;
        novo->heapValue = 0;
        if(chave < no->chave){
            pai->esq = novo;
            pai->dir = no;
        }
        else{
            pai->esq = no;
            pai->dir = novo;
        }
        pai->sum = pai->esq->sum + pai->dir->sum;
        pai->max = max(pai->esq->max, pai->dir->max);
        pai->sum_max = maxsum(pai);
        return pai;
    }

    // insere recursivamente
    else if(chave <= no->esq->max){
        no->esq = Insert(no->esq, chave, val, sum);
        no->sum = no->esq->sum + no->dir->sum;
        no->max = max(no->esq->max, no->dir->max);
        no->sum_max = maxsum(no);
    }
    else{
        no->dir = Insert(no->dir, chave, val, sum);
        no->sum = no->esq->sum + no->dir->sum;
        no->max = max(no->esq->max, no->dir->max);
        no->sum_max = maxsum(no);
    }
    
    /* corrige o heap subindo */
    if(no->heapValue < no->dir->heapValue){
        noTreap* pai = rodaEsq(no);
        return pai;
    }
    else if(no->heapValue < no->esq->heapValue){
        noTreap* pai = rodaDir(no);
        return pai;
    }
    else return no;
}


noTreap* treap::Delete(noTreap* no, int chave){
    // deleta a chave (sobe o nó irmão para o pai da chave deletada)
    if(no->esq->chave==chave){
        no->chave = no->dir->chave;
        no->val = no->dir->val;
        no->heapValue = no->dir->heapValue;
        no->sum = no->dir->sum;
        no->max = no->dir->max;
        no->sum_max = no->dir->sum_max;
        no->esq = no->dir->esq;
        no->dir = no->dir->dir;
        return no;
    }
    else if(no->dir->chave==chave){
        no->chave = no->esq->chave;
        no->val = no->esq->val;
        no->heapValue = no->esq->heapValue;
        no->sum = no->esq->sum;
        no->max = no->esq->max;
        no->sum_max = no->esq->sum_max;
        no->dir = no->esq->dir;
        no->esq = no->esq->esq;
        return no;
    }

    // desce até a chave e sobe corrigindo os nós
    else if(chave <= no->esq->max){
        no->esq = Delete(no->esq, chave);
        no->sum = no->esq->sum + no->dir->sum;
        no->max = max(no->esq->max, no->dir->max);
        no->sum_max = maxsum(no);
        return no;
    }
    else{
        no->dir = Delete(no->dir, chave);
        no->sum = no->esq->sum + no->dir->sum;
        no->max = max(no->esq->max, no->dir->max);
        no->sum_max = maxsum(no);
        return no;
    }
}


void printR(noTreap* no, int i){
    if(no==nullptr) return;
    cout << no->val << " " << no->chave << endl;
    printR(no->esq, i+3);
    for(int j=0; j<i; j++) cout << " ";
    printR(no->dir, i+3);
}


void treap::Print(noTreap* no){
    printR(no, 0);
    cout << endl;
}