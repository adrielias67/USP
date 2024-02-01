#include<iostream>

using namespace std;



int main(){
    long long int t, i, j, ncincos=0;
    cin >> t;
    long long int N[t];

    for(i=0; i<t; i++){
        cin >> N[i];
    }

    for(i=0; i<t; i++){
        for(j=5; j<=N[i]; j*=5){
            ncincos += N[i]/j;
        }

        cout << ncincos << endl;
        ncincos = 0;
    }
}