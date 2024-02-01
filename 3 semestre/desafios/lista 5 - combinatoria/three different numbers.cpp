#include<bits/stdc++.h>

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



int main(){
    int n;
    vector<ll> V (3);
    Z v1, v2, v3;

    cin >> n;
    for(int i=0; i<n; i++){
        cin >> V[0] >> V[1] >> V[2];
        sort(V.begin(), V.end());
        v1 = V[0];
        v2 = V[1] - 1;
        v3 = V[2] - 2;
        cout << (v1 * v2 * v3).x << "\n";
    }
}