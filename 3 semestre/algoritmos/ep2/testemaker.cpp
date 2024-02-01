#include<bits/stdc++.h>

using namespace std;



string corrigePalavra(string palavra){
    // dada uma palavra, retira caracteres estranhos dela
    int i=0, j=0;

    /*acha o começo da palavra*/
    while(palavra[i]!='\0' && (palavra[i]>'z' || (palavra[i]>'Z' && palavra[i]<'a') || (palavra[i]<'A' && palavra[i]>'9')  || palavra[i]<'0' || palavra[i]=='-')) i++;

    for(j=0; j<palavra.length()-i; j++){
        palavra[j] = palavra[j+i];
    }
    palavra[j] = '\0';

    /*copia a palavra*/
    i = j-1;
    while(i>0 && (palavra[i]>'z' || (palavra[i]>'Z' && palavra[i]<'a') || (palavra[i]<'A' && palavra[i]>'9')  || palavra[i]<'0' || palavra[i]=='-')){    
        i--;
    }
    palavra.erase(i+1, palavra.length()-i);

    return palavra;
}



int main(){
    int nPalavras, i;
    string palavra;

    cin >> palavra;
    cin >> nPalavras;
    cout << nPalavras;

    for(i=0; i<nPalavras; i++){
        cin >> palavra;
        palavra = corrigePalavra(palavra);
        cout << "O " << palavra << endl;
    }
}

