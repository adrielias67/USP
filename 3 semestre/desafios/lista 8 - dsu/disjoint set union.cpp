#include<bits/stdc++.h>

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

// nenhuma otimização: complexidade por operação --- O(N)
// apenas uma otimização: complexidade (amortizada) por operação --- O(log N)
// as duas otimizações: complexidade (amortizada) por operação --- O(a(N)), em que a é o inverso da função de Ackermann (praticamente O(1))

int main() {
	// leitura rápida, importante para o problema A da lista
	ios::sync_with_stdio(false); cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

	// inicialização dos conjuntos
	for(int i=0;i<N;i++) {
		dad[i] = i;
		sz[i] = 1;
	}

    for(int i=0; i<Q; i++){
        int opcao, u, v;
        cin >> opcao >> u >> v;
        
        if(opcao){
            cout << same_set(u,v) << endl;
        }
        else{
            join(u, v);
        }
    }

}