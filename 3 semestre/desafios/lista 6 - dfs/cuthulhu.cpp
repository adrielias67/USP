#include<bits/stdc++.h>

using namespace std;


using ll = long long;
#define MAX 10100



bool vis[MAX];
vector<int> adj[MAX];

int dfs(int u){
    vis[u] = true;
    for(int v: adj[u]){
        if(vis[v]) continue;
        dfs(v);
    }
    return u;
}


int main(){
    int n, m, u, v;
    cin >> n >> m;
    if(n!=m){
        cout << "NO\n";
        return 0;
    }

    for(int i=0; i<m; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while(vis[u]==0){
        dfs(u);
    }

    for(int i=1; i<n; i++){
        if(vis[i]==0){
            cout << "NO\n";
            return 0;
        }
    }

    cout << "FHTAGN!\n";
}