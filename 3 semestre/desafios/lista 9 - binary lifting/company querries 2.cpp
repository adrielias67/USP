#include <bits/stdc++.h>
using namespace std;

constexpr int N = 200'001;
constexpr int LOGK = 31;

// binary lifting: há n planetas indexados por 1, 2, ..., n
// cada planeta tem um único teleportador que leva para um único outro planeta
// qual planeta eu chego se eu começar no planeta i e usar o teleportador k vezes?

// prox[i]: onde eu chego após usar o teleportador uma vez em i
int prox[N];
int prof[N];

// dp[i][b]: onde eu chego após usar o teleportador 2^b vezes em i
//           note que dp[i][0] = prox[i], pois 2^0 == 1
//           para calcular, utilizamos que dp[i][b] = dp[dp[i][b-1]][b-1]
int dp[N][LOGK];

// calcula onde eu chego após começar no planeta i e utilizar o teleportador k vezes
int go(int x, int k) {
    // extrair as potências de 2
    for(int b=LOGK-1;b>=0;b--) {
        int pot = 1 << b; // 2 ^ b
        if(k >= pot) {
            k -= pot;
            x = dp[x][b];
        }
    }
    return x;
}

int lca(int x, int k){
    if(prof[x]>prof[k])
        x = go(x, prof[x]-prof[k]);
    else
        k = go(k, prof[k]-prof[x]);

    if(x == k) return x;

    for(int b=LOGK-1;b>=0;b--){
        int pot = 1 << b;
        if(go(x,pot)!=go(k,pot)){
            x = go(x, pot);
            k = go(k, pot);
        }
    }
    return go(x,1);
}



int main() {
    ios::sync_with_stdio(false); cin.tie(0); // leitura rapida
    int n, q;
    cin >> n >> q;
    prox[1] = 1;
    for(int x=2;x<=n;x++){
        cin >> prox[x];
        prof[x] = prof[prox[x]] + 1;
    }
    for(int x=1;x<=n;x++)
        dp[x][0] = prox[x];
    for(int b=1;b<LOGK;b++){ 
        for(int x=1;x<=n;x++){
            dp[x][b] = dp[ dp[x][b-1] ][b-1];
        }
    }
    for(int i=0; i<q; i++){
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}