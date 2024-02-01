#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int trocas=0, comp=0;

void insertionSort (char **A, int n) {
  int i, j;
  char *chave;
     
  for (i = 1; i < n; i++) {
    chave = A[i];
    j = i - 1;

    while (j >= 0 && strcmp(A[j],chave) > 0) {
      comp++;
      A[j + 1] = A[j];
      j = j - 1;
      trocas++;
    }
    comp++;
    A[j + 1] = chave;
    trocas++;
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

  insertionSort(palavras, n);
  printf("\nComparacoes: %ld\nTrocas: %ld\n", comp, trocas);

  for(i=0; i<n; i++){
    free(palavras[i]);
  }
  free(palavras);
  return 0;
}