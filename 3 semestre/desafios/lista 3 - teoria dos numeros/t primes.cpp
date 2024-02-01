#include<bits/stdc++.h>

using namespace std;

using i64 = int64_t;



int buscaBin(long long V[], long long int x, int ini, int fim) {
  if(ini<=fim){
    int mid;
    mid = (ini+fim) / 2;

    if(V[mid] == x){
      return 1;
    }
    if(V[mid] > x){
      //cout << "AAAAAAA\n";
      return buscaBin(V, x, ini, mid - 1);
    }
    return buscaBin(V, x, mid + 1, fim);
  }

  return 0;
}



constexpr int N = 1000'000;
vector<long long> primes;
bool is_prime[N];
i64 factor[N];

void crivo() {
	// assumimos que todos são primos
	fill(is_prime+2, is_prime+N, true);
	for(i64 p = 2; p < N; p++) {
		if(is_prime[p]) {
			primes.push_back(p);
			factor[p] = p;
			// marca os multiplos de p como sendo não primos
			for(i64 i = p * 2; i < N; i += p) {
				// essa linha é executada no máximo N logN vezes!
				is_prime[i] = false;
				factor[i] = p;
			}
		}
	}
}



int main(){
    int i, n; 
    crivo();

    int nprimos = primes.size();
    cin >> n;
    long long Tprimos[nprimos];
    long long num[n];

    for(i=0; i<nprimos; i++){
        Tprimos[i] = primes[i] * primes[i];
    }

    for(i=0; i<n; i++){
        cin >> num[i];
    }

    for(i=0; i<n; i++){
        if(buscaBin(Tprimos, num[i], 0, nprimos-1)) cout << "YES\n";
        else cout << "NO\n";
    }
}