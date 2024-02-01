#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "propriedadesnumericas.h"
#include "vetoraleatorio.h"

int main(){
	long long *V;
	int semente=23489891, tamanho=10, i;

	V = criaVetorAleatorio(semente,tamanho);

	for(i=0; i<tamanho; i++){
		if(i==2 || i==6 || i==7 || i==8) assert(ehPar(V[i]));
		else assert(ehPar(V[i])==0);
	}

	for(i=0; i<tamanho; i++){
		assert(ehPrimo(V[i])==0);
	}

	for(i=0; i<tamanho; i++){
		assert(ehQuadradoPerfeito(V[i])==0);
	}

	for(i=0; i<tamanho; i++){
		assert(ehCuboPerfeito(V[i])==0);
	}

	for(i=0; i<tamanho; i++){
		assert(ehFibonacci(V[i])==0);
	}

	for(i=0; i<tamanho; i++){
		assert(ehFatorial(V[i])==0);
	}

	exit(0);
}