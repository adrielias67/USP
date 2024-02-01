#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int trocas, comp;

typedef struct{
	char **H;
	int tamanho;
} heap;


void troca(heap H, int i, int j){
	char *aux;
  	aux = malloc(sizeof(char) * 11);
  	aux = H.H[i];
  	H.H[i] = H.H[j];
  	H.H[j] = aux;
  	trocas++;
}

void corrigeHeapDescendo(heap H, int i){
	int maior=i;

	if(H.tamanho>2*i+1){
		if(strcmp(H.H[2*i+1], H.H[i])>0) maior = 2*i+1;
		comp++;
	}
	if(H.tamanho>2*i+2){
		if(strcmp(H.H[2*i+2], H.H[i])>0 && strcmp(H.H[2*i+2], H.H[2*i+1])>0) maior = 2*i+2;
		comp++;
	}

	if(maior!=i){
		troca(H, i, maior);
		corrigeHeapDescendo(H, maior);
	}
}

void constroiHeap(heap H, int n){
	int i;
	for(i=(n-2)/2; i>=0; i--){
		corrigeHeapDescendo(H, i);
	}
}