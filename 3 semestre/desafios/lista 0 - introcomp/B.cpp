#include<iostream>
using namespace std;

int main(){
    int t, tamanho, i, j;
    char palavra[101], maior;
    cin >> t;
    for(i=0;i<t;i++){
        cin >> tamanho;
        cin >> palavra;
        maior = 'a';
        for(j=0;j<tamanho;j++){
            if(palavra[j]>maior) maior = palavra[j];
        }
        cout << (int)maior - 'a' + 1 << endl;
    }
}