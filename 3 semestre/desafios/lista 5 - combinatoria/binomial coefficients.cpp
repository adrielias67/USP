#include<bits/stdc++.h>

using namespace std;


using ll = long long;
#define mod 1000000007
#define tamanho 1000001

ll fat[tamanho];
ll inversoFat[tamanho];


ll fast_exp(ll a, ll e) {
	if(e == 0) return 1;
	ll x = fast_exp(a, e/2);
	x = x * x % mod;
	if(e % 2 == 1) x = x * a % mod;
	return x;
}


ll inverso(ll x){
    return fast_exp(x, mod-2);
}


void calculaFats(){
    fat[0] = 1;
    inversoFat[0] = 1;
    for(int i=1; i<tamanho; i++){
        fat[i] = fat[i-1] * i % mod;
        inversoFat[i] = inverso(fat[i]);
    }
}


ll bin(int a, int b){
    return fat[a] * inversoFat[b]%mod * inversoFat[a-b]%mod;
}


int main(){
    int n, a, b;
    cin >> n;
    calculaFats();
    
    for(int i=0; i<n; i++){
        cin >> a >> b;
        cout << bin(a, b) << endl;
    }
}