#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long int trocas, comp;

typedef struct{
	char **H;
	int tamanho;
} heap;

void corrigeHeapDescendo(heap H, int i);
void constroiHeap(heap H, int n);
void troca(heap H, int i, int j);