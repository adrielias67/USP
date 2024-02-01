#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filaPrioridades.h"

long int trocas=0, comp=0;

void heapsort(heap H, int n){
	int i;
	constroiHeap(H, n);
	for(i=n-1; i>=1; i--){
		troca(H, 0, i);
		H.tamanho--;
		corrigeHeapDescendo(H, 0);
	}
	H.tamanho = n;
}





int main(){
  int n, i;
  char **palavras;
  heap H;

  if(scanf("%d", &n) != 1) printf("erro\n");

  palavras = malloc(sizeof(char*) * n);

  
  for(i=0; i<n; i++){
    palavras[i] = malloc(sizeof(char) * 11);
    if(scanf("%s", palavras[i])!=1) printf("erro\n");
  }

  H.H = palavras;
  H.tamanho = n;

  heapsort(H, n);

  printf("\nComparacoes: %ld\nTrocas: %ld\n", comp, trocas);

  for(i=0; i<n; i++){
  	free(palavras[i]);
  }
  free(palavras); 

  return 0;
}