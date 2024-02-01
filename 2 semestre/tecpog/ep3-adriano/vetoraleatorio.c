#include <stdio.h>
#include <stdlib.h>
#include "vetoraleatorio.h"

void numberShift(long long *esq, long long dir){
	int i=1;
	while(dir/i != 0){
		i *= 10;
	}
	*esq = *esq * i;
}

long long * criaVetorAleatorio(int semente, int tamanho){
	int i, sinal;
	long long esq, dir, *V;
	srand((unsigned)semente);
	V = malloc(tamanho*sizeof(long long));
	for(i=0; i<tamanho; i++){
		esq = rand();
		dir = rand();
		numberShift(&esq, dir);
		V[i] = esq + dir;
		sinal = rand() % 2;
		if(sinal==0) V[i] *= -1;
	}
	return V;
}