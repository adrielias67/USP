#include<bits/stdc++.h>
using namespace std;

#define ll long long


typedef struct{
    ll ini;
    ll fim;
    ll val;
}atividade;

bool cmp_atv(atividade a, atividade b){
    return a.ini < b.ini;
}


ll bs(atividade A[], int ini, int fim, int x){
    int mid = (ini+fim)/2;
    if(ini==fim) return ini;
    if(A[mid].ini <= x){
        return bs(A, mid+1, fim, x);
    }
    return bs(A, ini, mid, x);
}


ll dp(ll s[], ll f[], ll v[], int n){
    atividade A[n];
    for(int i=0; i<n; i++){
        A[i].ini = s[i];
        A[i].fim = f[i];
        A[i].val = v[i];
    }

    sort(A, A+n, cmp_atv);

    ll dp[n+1];
    dp[n] = 0;
    dp[n-1] = A[n-1].val;

    for(ll i=n-2; i>=0; i--){
        dp[i] = dp[i+1];
        ll k = bs(A, i+1, n-1, A[i].fim);
        if(A[k].ini <= A[i].fim) k++;

        if(dp[i] < dp[k] + A[i].val){
            dp[i] = dp[k] + A[i].val;
        }
    }

    return dp[0];
}


int main(){
    int n;
    cin >> n;

    ll s[n], f[n], v[n];
    for(int i=0; i<n; i++){
        cin >> s[i] >> f[i] >> v[i];
    }

    cout << dp(s, f, v, n) << endl;
}