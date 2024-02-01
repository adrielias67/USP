#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 100

ll passos[MAX];

ll collatz(ll n){
    if(n == 1) return 0;
    if(n < MAX && passos[n] != 0) return passos[n];
    ll ans = 1 + collatz(n % 2 == 0 ? n/2 : 3*n + 1);
    if(n < MAX) passos[n] = ans;
    return ans;
}


int main(){
    ll n;
    for(int i=1; i<=MAX; i++)
        cout << i << ": " << collatz(i) << endl;
    return 0;
}