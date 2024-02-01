#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long int trocas=0, comp=0;

void troca(char **A, int i, int j){
  char *aux;
  aux = malloc(sizeof(char) * 11);
  aux = A[i];
  A[i] = A[j];
  A[j] = aux;
  trocas++;
}

int particiona(char **v, int ini, int fim) {
  int i, j;
  char *pivo;
  pivo = malloc(sizeof(char) * 11);

  pivo = v[fim];
  i = ini;
  for(j = ini; j < fim; j++){
    if(strcmp(v[j], pivo) <= 0){
      comp++;
      troca(v, i, j);
      i++;
    }
    comp++;
  }
  troca(v, i, fim);

  return i;
}

void quicksort(char **v, int ini, int fim) {
  int x;

  if (ini < fim){
    x = particiona(v, ini, fim);
    quicksort(v, ini, x - 1);
    quicksort(v, x + 1, fim);
  }
}





int main(){
  int n, i;
  char **palavras; 

  if(scanf("%d", &n) != 1) printf("erro\n");

  palavras = malloc(sizeof(char*) * n);

  for(i=0; i<n; i++){
    palavras[i] = malloc(sizeof(char) * 11);
    if(scanf("%s", palavras[i])!=1) printf("erro\n");
  }

  quicksort(palavras, 0, n-1);

  printf("\nComparacoes: %ld\nTrocas: %ld\n", comp, trocas);

  for(i=0; i<n; i++){
    free(palavras[i]);
  }
  free(palavras); 

  return 0;
}