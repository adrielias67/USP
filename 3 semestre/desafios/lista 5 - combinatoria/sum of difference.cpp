#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int modulo(int x){
    if(x<0) return -x;
    return x;
}

int main(){
    ll n, i, s=0;
    cin >> n;
    ll A[n];

    for(i=0; i<n; i++) cin >> A[i];
    sort(A, A+n);

    for(i=0; i<n-1; i++){
        s += modulo((A[i+1] - A[i])) * (n-1-i) * (i+1);
    }

    cout << s << endl;
}