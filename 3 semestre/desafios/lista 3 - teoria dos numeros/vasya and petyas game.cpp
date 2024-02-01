#include<bits/stdc++.h>

using namespace std;

using i64 = int64_t;


int fast_exp(int a, int e) {
	if(e == 0) return 1;
	int x = fast_exp(a, e/2);
	x = x * x;
	if(e % 2 == 1) x = x * a;
	return x;
}



constexpr int N = 1100;
vector<int> primes;
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
    int i=0, j=1, n;
    crivo();
    vector<int> resposta;

    cin >> n;
    
    while(primes[i]<=n){
        while(fast_exp(primes[i], j) <= n){
            resposta.push_back(fast_exp(primes[i], j));
            j++;
        }
        j = 1;
        i++;
    }

    cout << resposta.size() << endl;

    for(i=0; i<resposta.size(); i++){
      cout << resposta[i] << " ";
    }
    cout << endl;


}