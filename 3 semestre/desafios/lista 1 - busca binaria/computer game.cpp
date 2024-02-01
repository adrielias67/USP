#include<bits/stdc++.h>

using namespace std;


int main(){
    long long int i, q, k, n, a, b, ini, fim, mid, nrestantes, bateria;
    cin >> q;
    for(i=0; i<q; i++){
        cin >> k >> n >> a >> b;
        ini = 0;
        fim = k/a;
        if(k%a==0) fim--;
        while(ini<fim){
            mid = (ini + fim + 1) / 2;
            nrestantes = n;
            bateria = k;
            nrestantes -= mid;
            bateria -= a*mid;
            if(b*nrestantes >= bateria) fim = mid-1;
            else ini = mid;
        }
        ini = min(n, ini);
        if(ini==0 && b*n>=k) ini = -1;
        cout << ini << endl;
    }

}