#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"



typedef struct node_h{
    char* name;
    queue* q;
    struct node_h* next;
}node_h;


node_h* new_node_h(char name[], queue *q){
    node_h* n = (node_h*)malloc(sizeof(node_h));
    n->name = name;
    n->q = q;
    n->next = NULL;
    return n;
}



typedef struct{
    // Hash feito com lista ligada
    node_h* first;    // primeiro nó
    node_h* last;    // último nó
}hash;


hash* new_hash(){
    hash* h = (hash*)malloc(sizeof(hash));
    h->first = NULL;
    h->last = NULL;
    return h;
}


void add(hash* h, char name[], queue* q){
    // Insere no final da fila
    node_h* l = new_node_h(name, q);
    if(h->first==NULL){
        h->first = l;
        h->last = l;
        return;
    }
    h->last->next = l;
    h->last = l;
}


char* find_and_dequeue(hash* h, int val){
    // Procura o valor val (connfd) em todas as filas do hash, e remove ele;
    node_h* n = h->first;
    queue* q = n->q;
    while(n!=NULL){
        if(dequeue(q, val)) return n->name;
        n = n->next;
        q = n->q;
    }
    return NULL;
}


queue* find(hash* h, char name[]){
    // Retorna a fila de acordo com o nome
    node_h* current = h->first;
    while(current!=NULL){
        if(strcmp(name, current->name)==0) return current->q;
        current = current->next;
    }
    return NULL;
}