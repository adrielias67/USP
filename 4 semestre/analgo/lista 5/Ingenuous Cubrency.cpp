#include <bits/stdc++.h>
using namespace std;



int cubo[22];
void dp_cubos(){
    for(int i=1; i<=21; i++){
        cubo[i] = i*i*i;
    }
}


// int cabe_mais[22][10000];
// void dp_cabe_mais(){
//     for(int i=0; i<=21; i++){
//         for(int j=0; j<10000; j++){
//             cabe_mais[i][j] = 0;
//         }
//     }
// 
//     for(int i=2; i<=21; i++){
//         int q = cubo[i];
//         for(int j=q; j<10000;j+=q){
//             cabe_mais[i][j] = 1;
//         }
//     }
// }


long int jeitos[22][10000];
void dp(){
    for(int i=0; i<=21; i++){
        for(int j=0; j<10000; j++){
            jeitos[i][j] = 1;
        }
    }

    for(int i=2; i<=21; i++){
        for(int j=1; j<10000; j++){
            if(j<cubo[i]){
                jeitos[i][j] = jeitos[i-1][j];
                continue;
            }
            int resto = j - cubo[i];
            jeitos[i][j] = jeitos[i][resto] + jeitos [i-1][j];
        }
    }

}



int main(){
    dp_cubos();
    // dp_cabe_mais();
    dp();

    int valor;
    while(cin >> valor){
        cout << jeitos[21][valor] << endl;
    }
}