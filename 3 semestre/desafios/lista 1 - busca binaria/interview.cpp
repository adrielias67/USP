#include<bits/stdc++.h>

using namespace std;


int main(){
    int i, j, t, n, ini, fim, mid, soma;
    cin >> t;
    for(i=0; i<t; i++){
        cin >> n;
        int A[n+1];
        A[0] = 0;
        for(j=1; j<=n; j++){
            cin >> A[j];
            A[j] += A[j-1];
        }
        ini = 1;
        fim = n;
        while(ini<fim){
            mid = (ini + fim) / 2;
            cout << "? " << mid - ini + 1  << " " << flush;
            for(j=ini; j<=mid; j++){
                cout << j << " " << flush;
            }
            cout << endl;
            cin >> soma;
            if(soma > A[mid] - A[ini-1]) fim = mid;
            else ini = mid + 1;
        }
        cout << "! " << ini << endl << flush;
    }


}