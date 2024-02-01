#include<bits/stdc++.h>

using namespace std;

using ll = long long;
#define MAX 2510

struct par{
    int i;
    int j;
};

bool vis[MAX];
vector<int> adj[MAX];


int maiorDist=0;



void dfs(int u, int distancia){
    vis[u] = true;
    maiorDist = max(maiorDist, distancia);

    for(int v: adj[u]){
        if(vis[v]==false) dfs(v, distancia+1);
    }
}



bool abcPath(ll caso){
    int l, c, i, j;
    cin >> l >> c;

    if(l==0 || c==0) return false;

    char M[l][c];

    vector<par> comecos;

    for(i=0; i<l; i++){
        string linha;
        cin >> linha;
        for(j=0; j<c; j++){
            M[i][j] = linha[j];
            if(linha[j]=='A'){
                par pos;
                pos.i = i;
                pos.j = j; 
                comecos.push_back(pos);
            }
        }
    }

    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            if(j<c-1 && M[i][j+1] == (char)(M[i][j]+1)) adj[i*c+j].push_back(i*c+j+1);
            if(j<c-1 && i<l-1 && M[i+1][j+1] == (char)(M[i][j]+1)) adj[i*c+j].push_back((i+1)*c+j+1);
            if(i<l-1 && M[i+1][j] == ((char)(M[i][j]+1))) adj[i*c+j].push_back((i+1)*c+j);
            if(j>0 && i<l-1 && M[i+1][j-1] == ((char)(M[i][j]+1))) adj[i*c+j].push_back((i+1)*c+j-1);
            if(j>0 && M[i][j-1] == ((char)(M[i][j]+1))) adj[i*c+j].push_back(i*c+j-1);
            if(j>0 && i>0 && M[i-1][j-1] == ((char)(M[i][j]+1))) adj[i*c+j].push_back((i-1)*c+j-1);
            if(i>0 && M[i-1][j] == ((char)(M[i][j]+1))) adj[i*c+j].push_back((i-1)*c+j);
            if(j<c-1 && i>0 && M[i-1][j+1] == ((char)(M[i][j]+1))) adj[i*c+j].push_back((i-1)*c+j+1);
        }
    }

    for(par v: comecos){
        int u = v.i * c + v.j;
        dfs(u, 0);
    }

    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            while(!adj[i*c+j].empty()) adj[i*c+j].pop_back();
            vis[i*c+j] = false;
        }
    }
    
    if(!comecos.empty()) cout << "Case " << caso << ": " << maiorDist+1 << endl;
    else cout << "Case " << caso << ": " << 0 << endl;

    return true;
}



int main(){
    ll k=1;
    while(abcPath(k)){
        k++;
        maiorDist = 0;
    }
}