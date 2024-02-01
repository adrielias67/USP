#include<bits/stdc++.h>

using namespace std;

using ll = long long;
#define MAX 2510
#define INF INT_MAX



int main(){
    int n;
    int S;
    int t, m, i;
    cin >> n >> S >> t >> m;

    vector<pair<int, int>> adj[MAX];
    vector<int> dist(n+1, INF); // dist[x] é a menor distância de S até u

    for(i=0; i<m; i++){
        int u, v, custo;
        cin >> u >> v >> custo;
        adj[v].push_back({u, custo});
    }
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,S});
    dist[S] = 0;
    while(!pq.empty()){
        auto [cur_dist, u] = pq.top();
        pq.pop();
        if(cur_dist > dist[u]) continue;
        for(auto [v, cost]: adj[u]){
            if(dist[v] > dist[u]+cost){
                dist[v] = dist[u]+cost;
                pq.push({dist[v], v});
            }
        }
    }

    int cont=0;
    for(i=0; i<n+1; i++){
        if(dist[i]<=t) cont++;
    }
    
    cout << cont << endl;
}