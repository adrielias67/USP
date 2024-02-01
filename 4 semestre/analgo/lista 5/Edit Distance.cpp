#include<bits/stdc++.h>
using namespace std;



int edit_distance(string A, string B){
    int a=A.size();
    int b=B.size();
    int ED[b+1][a+1];
    
    for(int j=0; j<=a; j++){
        ED[0][j] = j;
    }
    for(int i=0; i<=b; i++){
        ED[i][0] = i;
    }

    for(int i=1; i<=b; i++){
        for(int j=1; j<=a; j++){
            if(A[j-1]==B[i-1]){
                ED[i][j] = ED[i-1][j-1];
            }
            else{
                ED[i][j] = 1 + min(ED[i-1][j], min(ED[i][j-1], ED[i-1][j-1]));
            }
            // cout << ED[i][j] << " ";
        }
        // cout << endl;
    }

    return ED[b][a];
}


int main(){
    string A, B;
    cin >> A >> B;

    cout << edit_distance(A, B) << endl;
}