#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <const int MOD>
struct mint {
    ll x;
    mint(): x(0) {}
    mint(ll _x): x(_x%MOD<0?_x%MOD+MOD:_x%MOD) {}
    void operator+=(mint rhs) { x+=rhs.x; if(x>=MOD) x-=MOD; }
    void operator-=(mint rhs) { x-=rhs.x; if(x<0)x+=MOD; }
    void operator*=(mint rhs) { x*=rhs.x; x%=MOD; }
    void operator/=(mint rhs) { *this *= rhs.inv(); }
    mint operator+(mint rhs) { mint res=*this; res+=rhs; return res; }
    mint operator-(mint rhs) { mint res=*this; res-=rhs; return res; }
    mint operator*(mint rhs) { mint res=*this; res*=rhs; return res; }
    mint operator/(mint rhs) { mint res=*this; res/=rhs; return res; }
    mint inv() { return this->pow(MOD-2); }
    mint pow(ll e) {
        mint res(1);
        for(mint p=*this;e>0;e/=2,p*=p) if(e%2)
            res*=p;
        return res;
    }
};

using Z = mint<1000000007>;



constexpr int N = 1'000'010;
int dad[N];
Z sz[N];

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

	 if(sz[a].x < sz[b].x) { // otimização 2: balancear a união de conjuntos
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
Z size_of_set(int a) {
	return sz[find(a)];
}



bool vis[N];

int main() {
    int i;
    int n, k;
    cin >> n >> k;

	// inicialização dos conjuntos
	for(i=0;i<=N;i++){
		dad[i] = i;
		sz[i] = 1;
	}

    for(i=1; i<n; i++){
        int u, v, tipo;
        cin >> u >> v >> tipo;
        if(tipo==0){
            join(u, v);
        }
    }

    Z resp;
    resp.x = n;
    resp = resp.pow(k); 
    for(i=1; i<=n; i++){
        if(!vis[find(i)]){
            vis[find(i)] = true;
            Z aux;
            aux = size_of_set(i);
            resp -= aux.pow(k);
        }
    }

    cout << resp.x << endl;
}