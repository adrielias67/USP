#include<bits/stdc++.h>

using namespace std;

using ll = long long;
#define MAX 8
#define INF INT_MAX



//int M[MAX][MAX];
vector<int> adj[MAX*MAX];

int l=8, c=8;



void mkm(){
    string ini, fim;
    cin >> ini >> fim;
    int Lini = (int)(ini[0]-'a');
    int Cini = ini[1]-'1';
    int Lfim = (int)(fim[0]-'a');
    int Cfim = fim[1]-'1';

    int S = Lini*c + Cini;

    vector<int> dist((l*c)+1, -1);
    queue<int> q;
    q.push(S);
    dist[S] = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v: adj[u]){
            if(dist[v] == -1){
                dist[v] = dist[u]+1;
                q.push(v);
            }
        }
    }

    cout << dist[Lfim*c + Cfim] << endl;
}



int main(){
    int i, j;
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
           if(j<c-2 && i<l-1) adj[i*c+j].push_back((i+1)*c+j+2);
           if(j<c-1 && i<l-2) adj[i*c+j].push_back((i+2)*c+j+1);
           if(j > 0 && i<l-2) adj[i*c+j].push_back((i+2)*c+j-1);
           if(j > 1 && i<l-1) adj[i*c+j].push_back((i+1)*c+j-2);
           if(j > 1 && i > 0) adj[i*c+j].push_back((i-1)*c+j-2);
           if(j > 0 && i > 1) adj[i*c+j].push_back((i-2)*c+j-1);
           if(j<c-1 && i > 1) adj[i*c+j].push_back((i-2)*c+j+1);
           if(j<c-2 && i > 0) adj[i*c+j].push_back((i-1)*c+j+2);
        }
    }

    int T;
    cin >> T;
    for(i=0; i<T; i++){
        mkm();
    }
}