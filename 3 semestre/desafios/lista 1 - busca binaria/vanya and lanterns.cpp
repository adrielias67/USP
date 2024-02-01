#include<bits/stdc++.h>

using namespace std;

void troca(long int A[], long int i, long int j){
  int aux;
  aux = A[i];
  A[i] = A[j];
  A[j] = aux;
}

int particiona(long int v[], long int ini, long int fim) {
  int i, j, pivo;
  pivo = v[fim];
  i = ini;
  for(j = ini; j < fim; j++){
    if(v[j]<=pivo){
      troca(v, i, j);
      i++;
    }
  }
  troca(v, i, fim);

  return i;
}

void quicksort(long int v[], long int ini, long int fim) {
  int x;

  if (ini < fim){
    x = particiona(v, ini, fim);
    quicksort(v, ini, x - 1);
    quicksort(v, x + 1, fim);
  }
}


int main(){
    long int i, n, l, maiorGap=0, gap;
    cin >> n >> l;
    long int A[n];
    double resposta;
    for(i=0; i<n; i++){
        cin >> A[i];
    }

    quicksort(A, 0, n-1);
    for(i=1; i<n; i++){
        gap = A[i] - A[i-1];
        if(gap>maiorGap) maiorGap = gap;
    }

    if(2*A[0]>maiorGap) maiorGap = 2*A[0];
    if(2*(l-A[n-1])>maiorGap) maiorGap = 2*(l-A[n-1]);

    resposta = maiorGap/2.0;
    cout << fixed << setprecision(10);
    cout << resposta << endl;
}