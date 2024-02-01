#include<bits/stdc++.h>

using namespace std;

// l := pi[i] is the largest l <= i such that
// s[0:l-1] = s[i-l+1:i]
template <typename T> vector<int> kmp(int sz, const T s[]) {
    vector<int> pi(sz);
    for(int i=1;i<sz;i++){
        int &l = pi[i];
        l = pi[i-1];
        while(l > 0 && s[i] != s[l])
            l = pi[l-1];
        if(s[i] == s[l]) l++;
    }
    return pi;
};


void test(int i) {
    cout << "Case " << i << ": ";

    vector<int> pi;
    string a, b;
    int tamanho;

    cin >> a >> b;
    tamanho = b.size();
    b.append("*");
    b.append(a);

    int ocorrencias=0;
    pi = kmp(b.size(), b.data());
    for(int i=0; i<pi.size(); i++) if(pi[i]==tamanho) ocorrencias++;
    cout << ocorrencias << endl;
}


int main(){
    int casos;
    cin >> casos;
    for(int i=1; i<=casos; i++) test(i);
}