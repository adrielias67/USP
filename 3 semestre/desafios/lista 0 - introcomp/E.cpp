#include<iostream>

using namespace std;


int main(){
    int i, j, k, t, n , q, num, tipo, valor, nPar=0;
    long long int soma=0;

    cin >> t;
    for(i=0; i<t; i++){
        cin >> n >> q;
        for(j=0; j<n; j++){
            cin >> num;
            if(num%2==0) nPar++;
            soma += num;
        }

        for(j=0; j<q; j++){
            cin >> tipo >> valor;
            if(tipo==0){
                soma += nPar * valor;
                if(valor%2==1) nPar = 0;
            }
            else{
                soma += (n-nPar) * valor;
                if(valor%2==1) nPar = n;
            }
            cout << soma << endl;
        }
        soma = 0;
        nPar = 0;
    }

}