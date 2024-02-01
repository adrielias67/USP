#include <iostream>
#include "pilhaR.h"

using namespace std;



pilhaR::pilhaR(){}
pilhaR::~pilhaR(){}


void pilhaR::Insert(int t, string op, item x){
    // Usa o insert da treap, com sum correspondente à operação
    if(op == "Push"){
        arvore.raiz = arvore.Insert(arvore.raiz, t, x, 1);
    }
    else if(op == "Pop"){
        arvore.raiz = arvore.Insert(arvore.raiz, t, x, -1);
    }
}


void pilhaR::Delete(int t){
    // Usa o delete da treap
    arvore.raiz = arvore.Delete(arvore.raiz, t);
}


int sizeR(noTreap* no, int t){
    if(no->esq==nullptr && no->dir==nullptr){
        if(no->chave==t) return no->sum;
        else return 0;
    }
    if(t <= no->esq->max) return sizeR(no->esq, t);
    else return no->esq->sum + sizeR(no->dir, t);
}

int pilhaR::Size(int t){
    if(t>arvore.raiz->max) t = arvore.raiz->max;
    return sizeR(arvore.raiz, t);
}


noTreap* search(noTreap* no, int k){
    // Para o k-th e para o top. Quando sobe na recursão, para procurar o push certo caso sum_max >= k na folha da esquerda
    if(no->esq==nullptr && no->dir==nullptr) return no;
    if(no->dir->sum_max >= k) return search(no->dir, k);
    else return search(no->esq, k - no->dir->sum);
}


pair<int, noTreap*> kthR(noTreap* no, int t, int k){
    // desce até t'
    //chegou na folha
    if(no->esq==nullptr && no->dir==nullptr){
        if(no->sum == -1){
            if(no->chave==t) return make_pair(2+k-1, nullptr);    //pop em t
            else return make_pair(1+k-1, nullptr);                //pop em t'
        }
        else{
            if(no->chave==t) return make_pair(k-1, nullptr);      //push em t
            else return make_pair(1+k-1, nullptr);                //push em t'
        }
    }
    // desce para a esquerda
    else if(t <= no->esq->max){
        return kthR(no->esq, t, k);
    }
    //desce para a direita, e na subida procura o push certo na esquerda
    else{
        pair<int, noTreap*> volta = kthR(no->dir, t, k);
        if(volta.second != nullptr) return volta;    // já achou o push certo
        k = volta.first;
        if(no->esq->sum_max >= k) return make_pair(0, search(no->esq, k));
        return make_pair(k - no->esq->sum, nullptr);
    }
}


item pilhaR::Kth(int t, int k){
    if(t>arvore.raiz->max) t = arvore.raiz->max;
    if(k==1) return Top(t);
    return kthR(arvore.raiz, t, k).second->val;
}


pair<int, noTreap*> topR(noTreap* no, int t){
    // desce até t'
    //chegou na folha
    if(no->esq==nullptr && no->dir==nullptr){
        if(no->sum == -1){
            if(no->chave==t) return make_pair(2, nullptr);    //pop em t
            else return make_pair(1, nullptr);                //pop em t'
        }
        else{
            if(no->chave==t) return make_pair(0, no);         //push em t
            else return make_pair(1, nullptr);                //push em t'
        }
    }
    // desce para a esquerda
    else if(t <= no->esq->max){
        return topR(no->esq, t);
    }
    // desce para a direita, e na subida procura o push certo na esquerda
    else{
        pair<int, noTreap*> volta = topR(no->dir, t);
        if(volta.second != nullptr) return volta;    // já achou o push certo
        int k = volta.first;
        if(no->esq->sum_max >= k) return make_pair(0, search(no->esq, k));
        else return make_pair(k - no->esq->sum, nullptr);
    }
}


item pilhaR::Top(int t){
    if(t>arvore.raiz->max) t = arvore.raiz->max;
    return topR(arvore.raiz, t).second->val;
}


void pilhaR::Print(int t){
    for(int i=1; i<=Size(t); i++){
        cout << Kth(t, i) << " ";
    }
    cout << endl;
}