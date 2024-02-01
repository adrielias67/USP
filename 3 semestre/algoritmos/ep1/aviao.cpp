#include <iostream>
#include "aviao.h"

using namespace std;



bool comparaPrioridade(aviao * A, aviao * B){
    // compara os avioes A e B. Retorna true se A tiver maior prioridade, e false se B tiver maior prioridade
    if(A->emergencia){
        if(B->emergencia){
            if(A->tempo < B->tempo) return true;
            return false;
        }
        return true;
    }
    if(B->emergencia) return false;
    if(A->tempo < B->tempo) return true;
    return false;
}



aviao::aviao(){
    id = new char[5];
    aeroporto = new char[3];
    tempoEspera = 0;
    prox = nullptr;
    ehraiz = -1;
    emergencia = 0;
    tempo = 0;
}



aviao::~aviao(){
    delete(id);
    delete(aeroporto);
};



int filaVazia(aviao * raiz){
    return(raiz->ehraiz == -1);
}



aviao * inicializa(aviao * raiz, char * ID, char * AEROPORTO, int TEMPO, bool EMERGENCIA){
    /* caso da fila vaiza */
    if(filaVazia(raiz)){
        for(int i=0; i<5; i++) raiz->id[i] = ID[i];
        for(int i=0; i<3; i++) raiz->aeroporto[i] = AEROPORTO[i];
        raiz->tempoEspera = 0;
        raiz->tempo = TEMPO;
        raiz->emergencia = EMERGENCIA;
        raiz->ehraiz = 1;
        return raiz;
    }

    /* fila não vazia */
    aviao * novo = new(aviao);
    for(int i=0; i<5; i++) novo->id[i] = ID[i];
    for(int i=0; i<3; i++) novo->aeroporto[i] = AEROPORTO[i];
    novo->tempoEspera = 0;
    novo->tempo = TEMPO;
    novo->emergencia = EMERGENCIA;
    novo->ehraiz = 0;

    /* caso da raiz da fila */
    if(raiz->ehraiz==1){
        if(comparaPrioridade(raiz, novo)){
            if(raiz->prox!=nullptr){
                if(comparaPrioridade(raiz->prox, novo)) raiz->prox = inicializa(raiz->prox, ID, AEROPORTO, TEMPO, EMERGENCIA);
                else{
                    novo->prox = raiz->prox;
                    raiz->prox = novo;
                    return raiz;
                }
            }
            else{
                raiz->prox = novo;
                return raiz;
            }
        }
        else{
            novo->prox = raiz;
            raiz->ehraiz = 0;
            novo->ehraiz = 1;
            return novo;
        }
    }

    /* caso do meio da fila */
    else if(raiz->prox!=nullptr){
        if(comparaPrioridade(raiz->prox, novo)) raiz->prox = inicializa(raiz->prox, ID, AEROPORTO, TEMPO, EMERGENCIA);
        else{
            novo->prox = raiz->prox;
            raiz->prox = novo;
            return raiz;
        }
    }
    
    /* caso do final da fila */
    else{
        raiz->prox = novo;
        return raiz;
    }

    return raiz;
}



aviao *removeInicio(aviao * raiz){
    if(raiz->prox == nullptr){
        raiz->ehraiz = -1;
        return raiz;
    }
    if(raiz->ehraiz){
        raiz->prox->ehraiz = 1;
        return raiz->prox;
    }
    return raiz->prox;
}



void removeProx(aviao * raiz){
    if(raiz->prox != nullptr) raiz->prox = raiz->prox->prox;
}



void update(aviao * raiz){
    if(!filaVazia(raiz)){
        raiz->tempo = max(0, raiz->tempo-1);
        raiz->tempoEspera++;
        if(raiz->prox != nullptr){
            update(raiz->prox);
        }
    }
}



void imprimeLista(aviao * raiz){
    if(!filaVazia(raiz)){
        if(raiz->emergencia) cout << " " << raiz->id << "(E) ";
        else cout << " " << raiz->id << "    ";
        cout << " " << raiz->aeroporto << "\t      ";
        cout << " " << raiz->tempo << "\n";
        if(raiz->prox != nullptr){
            imprimeLista(raiz->prox);
        }
    }
}



int somaTempo(aviao * raiz){
    int soma=0;
    if(!filaVazia(raiz)){
        while(raiz->prox != nullptr){
            soma += raiz->tempo;
            raiz = raiz->prox;
        }
        soma += raiz->tempo;
    }
    return soma;
}



int tamanho(aviao * raiz){
    int tamanho=0;
    if(!filaVazia(raiz)){
        while(raiz->prox != nullptr){
            tamanho++;
            raiz = raiz->prox;
        }
        tamanho++;
    }
    return tamanho;
}