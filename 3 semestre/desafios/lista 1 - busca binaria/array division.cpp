#include<iostream>

using namespace std;


int main(){
    int n, k, i, j=0, divisoes=0;
    cin >> n >> k;
    long long int ini=0, fim=0, mid, sParcial=0, A[200000];

    for(i=0; i<n; i++){
        cin >> A[i];
        fim += A[i];
    }

    while(ini<fim){
        divisoes = 1;
        sParcial = 0;
        mid = (ini+fim) / 2;

        for(j=0; j<n; j++){
            if(sParcial+A[j] <= mid) sParcial += A[j];
            else{
                sParcial = A[j];
                divisoes++;
            }
            if(sParcial>mid) break;
        }

        if(sParcial>mid) ini = mid+1;
        else if(divisoes>k) ini = mid+1;
        else fim = mid;
    }
    
    cout << ini << endl;
}