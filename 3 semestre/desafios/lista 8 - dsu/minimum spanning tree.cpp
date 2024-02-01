#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1'000'010;
int dad[N], sz[N];

// retorna o representante de a
int find(int a) {
	if(a == dad[a]) return a; // a é o representante de seu conjunto

	int rep = find(dad[a]); // achar o representante do pai de a

	dad[a] = rep; // otimização 1: compressão de caminho até o representante

	return dad[a] = find(dad[a]);
}

// une os conjuntos de a e b
void join(int a, int b) {
	// inicialmente, tomamos os representantes de a e b
	 a = find(a);
	 b = find(b); 

	 if(a == b) return; // a e b já são do mesmo conjunto

	 if(sz[a] < sz[b]) { // otimização 2: balancear a união de conjuntos
		 dad[a] = b;
		 sz[b] += sz[a];
	 } else {
		 dad[b] = a;
		 sz[a] += sz[b];
	 }
}

// retorna se a e b pertencem ao mesmo conjunto
bool same_set(int a, int b) {
	return find(a) == find(b);
}

// retorna o tamanho do conjunto que a pertence
int size_of_set(int a) {
	return sz[find(a)];
}



int mst() {
    int n, m, soma=0, k=0;
    cin >> n >> m;

    if(n==0) return 1;

    if(m==0){
        cout << "Impossible\n";
        return 0;
    }

    pair <int, pair<int, int>> aresta[m];
    vector<pair<int, int>> caminho;

	// inicialização dos conjuntos
	for(int i=0; i<n; i++) {
		dad[i] = i;
		sz[i] = 1;
	}

    for(int i=0; i<m; i++){
        int u, v, peso;
        cin >> u >> v >> peso;
        aresta[i].first = peso;
        if(u < v){
            aresta[i].second.first = u;
            aresta[i].second.second = v;
        }
        else{
            aresta[i].second.first = v;
            aresta[i].second.second = u;
        }
    }

    sort(aresta, aresta+m);

    for(int i=0; i<m; i++){
        int u, v;
        u = aresta[i].second.first;
        v = aresta[i].second.second;
        if(!same_set(u, v)){
            join(u, v);
            pair <int, int> aux;
            aux.first = u;
            aux.second = v;
            caminho.push_back(aux);
            soma += aresta[i].first;
            k++;
        }
    }

    for(int i=0; i<n; i++){
        if(!same_set(0,i)){
            cout << "Impossible\n";
            return 0;
        }
    }

    sort(caminho.begin(), caminho.end());

    cout << soma << endl;
    for(int i=0; i<k; i++){
        cout << caminho[i].first << " " << caminho[i].second << endl;
    }
    return 0;
}



int main(){
    while(mst()==0);
}
