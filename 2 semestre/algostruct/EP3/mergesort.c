#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int trocas=0, comp=0;

void  intercala (int p, int q, int r, char **v)  {
  int n1, n2;
  char **A, **B;
  int i, j, k;

   
  n1 = q - p + 1;
  n2 = r - q;
  
  A = malloc (sizeof(char*) * n1);
  B = malloc (sizeof(char*) * n2);

  for(i=0; i<n1; i++){
    A[i] = malloc (sizeof(char) * 11);
  }
  for(i=0; i<n2; i++){
    B[i] = malloc (sizeof(char) * 11);
  }

  for (i = 0; i < n1; i++)
    A[i] = v[p+i];

  for (i = 0; i < n2; i++)
    B[i] = v[q+1 + i];

  
  i = 0, j = 0;
  k = p;
  while (i < n1 && j < n2) {
    if(strcmp(A[i], B[j]) <= 0){
      comp++;
      v[k] = A[i++];
    }
    else{
      v[k] = B[j++];
    }
    comp++;
    trocas++;
    k++;
  }

  while (i < n1)
    v[k++] = A[i++];
  while (j < n2)
    v[k++] = B[j++];

  free(A);
  free(B);
}

void mergeSort(int p, int r, char **v) {
  int q;
  
  if(p < r) {                 
    q = (p + r)/2;         
    mergeSort(p, q, v);
    mergeSort(q+1, r, v);
    intercala(p, q, r, v);
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

  mergeSort(0, n-1, palavras);

  printf("\nComparacoes: %ld\nTrocas: %ld\n", comp, trocas);

  for(i=0; i<n; i++){
    free(palavras[i]);
  }
  free(palavras); 

  return 0;
}