#include<bits/stdc++.h>

using namespace std;


using ll = long long;
#define MAX 250010



bool vis[MAX];
int nDist;
struct posit{
    int dist;
    int posDist;
    bool operator < (posit outra){
        return(dist<outra.dist);
    }
};
posit pos[MAX];
char maze[510][510];
vector<int> adj[MAX];



void dfs(int u, int distancia){
    vis[u] = true;
    pos[u].dist = distancia;

    for(int v: adj[u]){
        if(vis[v]==false) dfs(v, distancia+1);
    }
}


int main(){
    for(int i=0; i<MAX; i++){
        pos[i].posDist = i;
    }

    int l, c, i, j, k;
    cin >> l >> c >> k;

    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            cin >> maze[i][j];
        }
    }

    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            if(maze[i][j]=='.'){
                if(j<c-1 && maze[i][j+1]=='.'){adj[i*c+j].push_back(i*c+j+1); adj[i*c+j+1].push_back(i*c+j);}
                if(j>0 && maze[i][j-1]=='.'){adj[i*c+j].push_back(i*c+j-1); adj[i*c+j-1].push_back(i*c+j);}
                if(i<l-1 && maze[i+1][j]=='.'){adj[i*c+j].push_back((i+1)*c+j); adj[(i+1)*c+j].push_back(i*c+j);}
                if(i<0 && maze[i][j+1]=='.'){adj[i*c+j].push_back((i-1)*c+j); adj[(i-1)*c+j].push_back(i*c+j);}
            }
        }
    }

    bool achou = false;
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            if(maze[i][j]=='.') achou = true;
            if(achou) break;
        }
        if(achou) break;
    }

    dfs(i*c+j,0);
    
    sort(pos, pos+l*c);

    int mazeVec[MAX];
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            mazeVec[i*c+j] = maze[i][j];
        }
    }

    for(i=l*c-1; i>l*c-1-k; i--){
        pos[i].dist = 0;
        mazeVec[pos[i].posDist] = 'X';
    }

    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            maze[i][j] = mazeVec[i*c+j];
        }
    }

    cout << endl;
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            cout << maze[i][j];
        }
        cout << endl;
    }
}