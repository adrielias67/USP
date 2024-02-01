#include <stdio.h>
#include <stdlib.h>



typedef struct node_q{
    int val;
    struct node_q* next;
}node_q;


node_q* new_node_q(int val){
    node_q* n = (node_q*)malloc(sizeof(node_q));
    n->val = val;
    n->next = NULL;
    return n;
}



typedef struct{
    // Fila feita com lista ligada
    node_q* first;    // primeiro nó
    node_q* last;    // último nó
}queue;


queue* new_queue(){
    queue* q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}


void enqueue(queue* q, int val){
    // Insere no final da fila
    node_q* l = new_node_q(val);
    if(q->first==NULL){
        q->first = l;
        q->last = l;
        return;
    }
    q->last->next = l;
    q->last = l;
}


int dequeue(queue* q, int val){
    // Remove o elemento com valor val e returna 1. Retorna 0 se o elemento não está
    node_q* n = q->first;
    if(n==NULL) return 0; 
    if(n->val==val){
        if(q->first->next==NULL){
            q->first = NULL;
            q->last = NULL;
            return 1;
        }
        q->first = q->first->next;
        return 1;
    }
    if(n->next==NULL) return 0;
    while(n->next->val!=val){
        n = n->next;
        if(n->next==NULL) return 0;
    }
    if(n->next->next==NULL){
        n->next = n->next->next;   
        q->last = n;
    }
    n->next = n->next->next;
    return 1;
}


void switch_first(queue *q){
    // Troca o primeiro elemento pelo último
    enqueue(q, q->first->val);
    q->first = q->first->next;
}


int first(queue* q){
    // Retorna o primeiro elemento e troca com o último
    if( q->first==NULL) return NULL;
    int f = q->first->val;
    switch_first(q);
    return f;
}