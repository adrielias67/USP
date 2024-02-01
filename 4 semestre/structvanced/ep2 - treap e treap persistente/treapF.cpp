#include <iostream>
#include <stdlib.h>
#include "treapF.h"
#include <random>
#include "time.h"

using namespace std;



treapF::treapF(){
    raizes.push_back(nullptr);
}


treapF::~treapF(){

}


noTreapF* rodaEsq(noTreapF* no){
    noTreapF* aux;
    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;
}


noTreapF* rodaDir(noTreapF* no){
    noTreapF* aux;
    aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    return aux;
}



noTreapF* InsertR(noTreapF* no, item val){
    //insere recursivamente numa folha criando uma treap nova, e corrige o heap subindo
    /* insere na árvore */
    if(no==nullptr){
        noTreapF* novo = new noTreapF;
        novo->val = val;
        no = novo;
        return no;
    }

    noTreapF* copia = new noTreapF;
    copia->val = no->val;

    if(no->val > val){
        copia->esq = InsertR(no->esq, val);
        copia->dir = no->dir;
    }
    else{
        copia->dir = InsertR(no->dir, val);
        copia->esq = no->esq;
    }
    
    /* corrige o heap */
    if(copia->dir!=nullptr && copia->heapValue < copia->dir->heapValue) return rodaEsq(copia);
    else if(copia->esq!=nullptr && copia->heapValue < copia->esq->heapValue) return rodaDir(copia);
    else return copia;
}


void treapF::Insert(int no, item val){
    noTreapF* R = new noTreapF;
    R = InsertR(raizes[no], val);
    raizes.push_back(R);
}



noTreapF* DeleteR(noTreapF* no, item val, bool novo){
    // leva o nó a ser deletado para uma folha e deleta ele, criando uma treap nova
    /* árvore vazia */
    if(no==nullptr) return nullptr;

    /* insere a árvore nova*/
    if(no->val != val){
        noTreapF* copia = new noTreapF;
        copia->val = no->val;

        if(no->val > val){
            copia->esq = DeleteR(no->esq, val, false);
            copia->dir = no->dir;
        }
        else{
            copia->dir = DeleteR(no->dir, val, false);
            copia->esq = no->esq;
        }

        return copia;
    }

    /* leva até uma folha e remove */
    else{

        // é a priemira vez que encontro o nó a ser deletado
        if(!novo){
            noTreapF* pai = new noTreapF;
            noTreapF* copia = new noTreapF;
            copia->val = no->val;
            copia->dir = no->dir;
            copia->esq = no->esq;

            if(no->esq==nullptr && no->dir==nullptr){
                return nullptr;
            }

            else if(no->dir==nullptr){
                return copia->esq;
            }

            else if(no->esq==nullptr){
                return copia->dir;
            }

            else{
                if(no->dir->heapValue > no->esq->heapValue){
                    pai->val = no->dir->val;
                    pai->dir = no->dir->dir;
                    pai->esq = no->dir->esq;
                    copia->dir = pai;
                    pai = rodaEsq(copia);
                    pai->esq = DeleteR(pai->esq, val, true);
                    return pai;
                }
                else{
                    pai->val = no->esq->val;
                    pai->dir = no->esq->dir;
                    pai->esq = no->esq->esq;
                    copia->esq = pai;
                    pai = rodaDir(copia);
                    pai->dir = DeleteR(pai->dir, val, true);
                    return pai;
                }
            }
        }

        // já rotacionei o nó a ser deletado
        else{
            noTreapF* pai = new noTreapF;

            if(no->esq==nullptr && no->dir==nullptr){
                return nullptr;
            }

            else if(no->dir==nullptr){
                return no->esq;
            }

            else if(no->esq==nullptr){
                return no->dir;
            }

            else{
                if(no->dir->heapValue > no->esq->heapValue){
                    pai->val = no->dir->val;
                    pai->dir = no->dir->dir;
                    pai->esq = no->dir->esq;
                    no->dir = pai;
                    pai = rodaEsq(no);
                    pai->esq = DeleteR(pai->esq, val, true);
                    return pai;
                }
                else{
                    pai->val = no->esq->val;
                    pai->dir = no->esq->dir;
                    pai->esq = no->esq->esq;
                    no->esq = pai;
                    pai = rodaDir(no);
                    pai->dir = DeleteR(pai->dir, val, true);
                    return pai;
                }
            }
        }

    }

}


void treapF::Delete(int no, item val){
    noTreapF* R = new noTreapF;
    R = DeleteR(raizes[no], val, false);
    raizes.push_back(R);
}



bool SearchR(noTreapF* no, item val){
    // procura recursivamente em cada nó
    if(no==nullptr) return false;

    if(no->val == val) return true;

    if(val < no->val){
        return SearchR(no->esq, val);
    }
    else return SearchR(no->dir, val);
}


bool treapF::Search(int no, item val){
    noTreapF* R = raizes[no];
    return SearchR(R, val);
}



int MinR(noTreapF* no){
    // caminha sempre para a esquerda até não poder mais
    if(no->esq==nullptr) return no->val;
    else return MinR(no->esq);
}

int treapF::Min(int no){
    noTreapF* R = raizes[no];
    return MinR(R);
}



void PrintR(noTreapF* no, int i){
    if(no==nullptr) return;
    cout << no->val << " " << no->heapValue << endl;
    PrintR(no->esq, i+3);
    for(int j=0; j<i; j++) cout << " ";
    PrintR(no->dir, i+3);
}


void treapF::Print(int no){
    noTreapF* R = raizes[no];
    PrintR(R, 0);
    cout << endl;
}