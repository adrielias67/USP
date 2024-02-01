#include<bits/stdc++.h>

using namespace std;


int main(){
    int q, n, ini, fim, maiorIntervalo=0;
    char cor;
    cin >> q;


    for(int i=0; i<q; i++){

        cin >> n >> cor;

        char A[n];
        for(int j=0; j<n; j++){
            cin >> A[j];
        }

        if(cor=='g'){
            cout << 0 << endl;
            continue;
        }

        ini = 0; fim = 0;
        while(ini<n){
            if(A[ini]==cor){
                while(A[fim%n] != 'g') fim++;
                if(fim-ini > maiorIntervalo) maiorIntervalo = fim-ini;
                ini = fim;
                fim++;
            }
            ini++;
        }

        cout << maiorIntervalo << endl;
        maiorIntervalo = 0;

    }

}

