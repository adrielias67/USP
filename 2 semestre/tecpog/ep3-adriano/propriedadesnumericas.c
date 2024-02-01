#include <stdio.h>
#include "propriedadesnumericas.h"

#define RAIZ2_MAX_LONG_LONG 3037000499
#define RAIZ3_MAX_LONG_LONG 2097152

int ehPar(long long x){
	return !(x%2);
}

int ehPrimo(long long x){
	int i;
	if(x<0) x = -x;

	if(x==1 || x==2 || x==3) return 1;
	if(x==0) return 0;
	for(i=2; i*i<=x; i++){
		if(x%i==0) return 0;
	}
	return 1;
}

int ehQuadradoPerfeito(long long x){
	if(x==1) return 1;
	long long ini=0, fim=x, meio;

	meio = fim / 2;
	while(meio > RAIZ2_MAX_LONG_LONG){
		meio = fim / 2;
		fim = meio;
	}

	while(fim-ini > 1){
		meio = (fim + ini) / 2;
		if(meio*meio > x) fim = meio;
		else ini = meio;
	}
	if(ini*ini == x) return 1;
	return 0;
}

int ehCuboPerfeito(long long x){
	if(x<0) x = -x;
	long long ini=0, fim=x, meio;
	if(x==1) return 1;

	meio = fim / 2;
	while(meio > RAIZ3_MAX_LONG_LONG){
		meio = fim / 2;
		fim = meio;
	}

	while(fim-ini > 1){
		meio = (fim + ini) / 2;
		if(meio*meio*meio > x) fim = meio;
		else ini = meio;
	}
	if(ini*ini*ini == x) return 1;
	return 0;
}

int ehFibonacci(long long x){
	long long ant1=1, ant2=1, fib=1;
	while(x>fib){
		fib = ant1 + ant2;
		ant2 = ant1;
		ant1 = fib;
	}
	if(x==fib) return 1;
	return 0;
}

int ehFatorial(long long x){
	int i;
	long long fat=1;
	for(i=2; fat<x; i++){
		fat = fat * i;
	}
	if(x==fat) return 1;
	return 0;
}