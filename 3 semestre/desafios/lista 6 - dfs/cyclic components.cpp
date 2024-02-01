#include<bits/stdc++.h>

using namespace std;


using ll = long long;
#define MAX 200010



bool vis[MAX];
vector<int> adj[MAX];
int acabeiDeSair, primeiroNo, nAndadas;
bool fuck;


void dfs(int u){
    int amongus;
    nAndadas++;
    vis[u] = true;

    //cout << "1" << u << endl;

    if(adj[u].size()>2 || adj[u].size() == 1){
        fuck = true;
        return;
    }

    for(int v: adj[u]){
        if(v==acabeiDeSair && nAndadas==1) continue;
        if(v==acabeiDeSair && vis[v]) continue;
        if(vis[v]){
            if(v!=primeiroNo){
                //cout << u  << " " << primeiroNo << endl;
                fuck = true;
                return;
            }
            else return;
        }
        amongus = v;
    }
    
    acabeiDeSair = u;
    dfs(amongus);
}


int main(){
    int n, m, u, v;
    cin >> n >> m;
    int nCiclos=0;

    for(int i=0; i<m; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=1; i<n+1; i++){
        if(vis[i]==true) continue;
        if(adj[i].empty()) continue;
        fuck = false;
        primeiroNo = i;
        acabeiDeSair = adj[i][0];
        nAndadas = 0;
        dfs(i);
        if(!fuck && nAndadas>1) nCiclos++;
    }

    cout << nCiclos << endl;
}