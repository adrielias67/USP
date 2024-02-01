#include<bits/stdc++.h>

using namespace std;

using ll = long long;



int n, a, b, c;
int laco[4001];



int main() {
    int i, maior;
    cin >> n >> a >> b >> c;

    laco[0] = 1;
    for(i=1; i<=n; i++){
        maior = 0;
        if(i>=a) maior = max(maior, laco[i-a]);
        if(i>=b) maior = max(maior, laco[i-b]);
        if(i>=c) maior = max(maior, laco[i-c]);
        laco[i] = maior;
        if(maior>0) laco[i]++;
    }
    
    cout << laco[n]-1 << endl;
}
