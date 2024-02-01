#include<iostream>
#include<stdlib.h>
#include"treap.h"
#include<random>
#include"time.h"

using namespace std;



treap::treap(){
    raiz = nullptr;
}


treap::~treap(){

}


noTreap* rodaEsq(noTreap* no){
    noTreap* aux;
    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;
}

noTreap* rodaDir(noTreap* no){
    noTreap* aux;
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    return aux;
}


noTreap* treap::Insert(noTreap* no, item val){
    //insere recursivamente numa folha, e corrige o heap subindo
    /* insere na árvore */
    if(no==nullptr){
        noTreap* novo = new noTreap;
        novo->val = val;
        no = novo;
        return no;
    }

    else if(no->val > val){
        no->esq = Insert(no->esq, val);
    }
    else no->dir = Insert(no->dir, val);
    
    /* corrige o heap */
    if(no->dir!=nullptr && no->heapValue < no->dir->heapValue) return rodaEsq(no);
    else if(no->esq!=nullptr && no->heapValue < no->esq->heapValue) return rodaDir(no);
    else return no;
}


noTreap* treap::Delete(noTreap* no, item val){
    // leva o nó a ser deletado para uma folha e deleta ele
    /* caminha até o nó a deletar */
    if(no->val != val){
        if(no->esq==nullptr){
            if(no->dir==nullptr){
                return no;
            }
            else{
                no->dir = Delete(no->dir, val);
                return no;
            }
        }

        else{
            if(no->dir==nullptr){
                no->esq = Delete(no->esq, val);
                return no;
            }
            else{
                if(no->val > val){
                    no->esq = Delete(no->esq, val);
                    return no;
                }
                else{
                    no->dir = Delete(no->dir, val);
                    return no;
                }
            }
        }
    }

    /* leva até uma folha e remove */
    if(no->esq==nullptr && no->dir==nullptr){
        return nullptr;
    }

    noTreap* pai;
    if(no->dir==nullptr){
        pai = rodaDir(no);
        pai->dir = Delete(pai->dir, val);
        return pai;
    }

    else if(no->esq==nullptr){
        pai = rodaEsq(no);
        pai->esq = Delete(pai->esq, val);
        return pai;
    }

    else{
        if(no->dir->heapValue > no->esq->heapValue){
            pai = rodaEsq(no);
            pai->esq = Delete(pai->esq, val);
            return pai;
        }
        else{
            pai = rodaDir(no);
            pai->dir = Delete(pai->dir, val);
            return pai;
        }
    }
}


bool treap::Search(noTreap* no, item val){
    // procura recursivamente em cada nó
    if(no==nullptr) return false;

    if(no->val == val) return true;

    if(val < no->val){
        return Search(no->esq, val);
    }
    else return Search(no->dir, val);
}


int treap::Min(noTreap* no){
    // caminha sempre para a esquerda até não poder mais
    if(no->esq==nullptr) return no->val;
    else return Min(no->esq);
}


void printR(noTreap* no, int i){
    if(no==nullptr) return;
    cout << no->val << " " << no->heapValue << endl;
    printR(no->esq, i+3);
    for(int j=0; j<i; j++) cout << " ";
    printR(no->dir, i+3);
}


void treap::Print(noTreap* no){
    printR(no, 0);
    cout << endl;
}