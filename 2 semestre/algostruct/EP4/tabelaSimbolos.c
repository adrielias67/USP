#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv.h"



/* 

Tabela de símbolos para chave
 chave - é uma string

Implementada com Árvores de Busca Binária 

*/

      
/* Insere um elemento na tabela, devolve a raiz da árvore com o
   elemento inserido.
   Para cada chave inserida, verifica a linha em que está:
    Se já ocorreu naquela linha, adiciona 1 na quantidade.
    Caso contrário, adiciona uma nova linha de ocorrência.

no * insere (no * raiz, char * x); 
*/ 

no * insercao (no * raiz, char * x, int linha){
  int i=0, j;
  if (raiz == NULL){
    raiz = malloc (sizeof(no));
    raiz->chave = malloc(strlen(x)+1);
    raiz->linhas = malloc(2 * sizeof(int));
    raiz->quantidade = malloc(2 * sizeof(int));
    strcpy(raiz->chave,x);
    raiz->dir = raiz->esq = NULL;
    raiz->linhas[0] = linha;
    raiz->quantidade[0] = 1;
    raiz->linhas[1] = 0;
    raiz->quantidade[1] = 0;
    raiz->nlinhas = 2;
    return raiz;
  }
  if (strcmp(x, raiz->chave) == 0){
    i=0;
    while(raiz->linhas[i] != linha && raiz->linhas[i] != 0 && i<raiz->nlinhas-1)
      i++;
    if(i==raiz->nlinhas-1){
      raiz->nlinhas *= 2;
      int* newLinhas;
      int* newQuantidade;
      newLinhas = malloc(raiz->nlinhas*sizeof(int));
      newQuantidade= malloc(raiz->nlinhas*sizeof(int));
      for(j=0; j<raiz->nlinhas/2 -1; j++){
        newLinhas[j] = raiz->linhas[j];
        newQuantidade[j] = raiz->quantidade[j];
      }
      raiz->linhas = newLinhas;
      raiz->quantidade = newQuantidade;
    }
    if(raiz->linhas[i] == linha) raiz->quantidade[i] ++;
    else{
      raiz->linhas[i] = linha;
      raiz->quantidade[i] = 1;
      raiz->linhas[i+1] = 0;
      raiz->quantidade[i+1] = 0;
    }
  }
  else if (strcmp(x, raiz->chave) < 0)
    raiz->esq = insercao (raiz->esq, x, linha);
  else if (strcmp(x, raiz->chave) > 0)
    raiz->dir = insercao (raiz->dir, x, linha);
  return raiz;
}

