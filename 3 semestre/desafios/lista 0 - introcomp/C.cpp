#include<iostream>
using namespace std;

int main(){
    int n, i, eh=0;
    cin >> n;
    for(i=2;i<=n/2;i+=2){
        if((n-i)%2==0){
            eh = 1;
            break;
        }
    }
    if(eh) cout << "YES" << endl;
    else cout << "NO" << endl;
}