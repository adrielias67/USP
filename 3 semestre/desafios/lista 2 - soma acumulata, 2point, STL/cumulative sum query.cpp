#include<bits/stdc++.h>

using namespace std;


int main(){
    int i, n, q, ini, fim;
    cin >> n;
    long long int A[n];

    cin >> A[0];
    for(i=1; i<n; i++){
        cin >> A[i];
        A[i] += A[i-1];
    }
    cin >> q;

    for(i=0; i<q; i++){
        cin >> ini >> fim;
        if(ini==0) cout << A[fim];
        else cout << A[fim] - A[ini-1];
        cout << endl;
    }

}