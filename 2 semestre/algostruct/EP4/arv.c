/* Árvores Binárias */

#include <stdio.h>
#include <stdlib.h>
#include "arv.h"



no * minimo (no * raiz){
  if (raiz == NULL || raiz->esq == NULL)
    return raiz;
  return minimo(raiz->esq);
} 


/******

Percurso in-ordem: esquerda, raiz, direita

void inordem (no *raiz); 
********/

void inordem (no *raiz) {
  int i=0;
  if (raiz != NULL){
    inordem (raiz->esq);
    printf("%s ", raiz->chave);
    while(raiz->linhas[i] != 0){
      if(raiz->quantidade[i] > 1) 
        printf("%d(%d) ", raiz->linhas[i], raiz->quantidade[i]);
      else
        printf("%d ", raiz->linhas[i]);
      i++;
    }
    printf("\n");
    inordem (raiz->dir);
  }
}

