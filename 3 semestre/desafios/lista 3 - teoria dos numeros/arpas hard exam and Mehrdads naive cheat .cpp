#include<bits/stdc++.h>

using namespace std;


int main(){
    int n, amongus=0;
    cin >> n;
    if(n==0){
        cout << "1\n";
        amongus = 1;
    }
    if(!amongus){
        n %= 4;
        if(n==1) cout << "8\n";
        else if(n==2) cout << "4\n";
        else if(n==3) cout << "2\n";
        else cout << "6\n";
    }    
}

