#include<bits/stdc++.h>

using namespace std;


int main(){
    int n, i, pares=0, numero=1, qtd=0;
    cin >> n;
    int A[n];

    for(i=0; i<n; i++){
        cin >> A[i];
    }
    sort(A, A+n);

    i = 0;
    while(i<n){
        if(A[i] != numero){
            numero = A[i];
            pares += qtd/2;
            qtd = 1;
        }
        else{
            qtd++;
        }
        if(i == n-1){
            if(A[i-1] == numero){
                pares += qtd / 2;
            }
        }
        i++;
    }

    cout << pares << endl;
}