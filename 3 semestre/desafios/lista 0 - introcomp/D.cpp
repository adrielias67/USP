#include<iostream>

using namespace std;


int len(char palavra[]){
    int i=0;
    while(palavra[i] >= 'A') i++;
    return i;
}


int main(){
    int i, j, letras[26], nLetrasImpar=0, letraImpar, l;
    char palavra[1000001], letra;
    cin >> palavra;

    for(i=0; i<26; i++){
        letras[i] = 0;
    }

    l = len(palavra);
    for(i=0; i<l; i++){
        letras[palavra[i] - 'A'] ++;
    }

    for(i=0; i<26; i++){
        if (letras[i] %2 != 0){
            nLetrasImpar++;
            letraImpar = i;
        }
    }

    if(nLetrasImpar>1) cout << "NO SOLUTION";

    else if(nLetrasImpar==0){
        letra = 'A';
        for(i=0; i<26; i++){
            for(j=0; j<letras[i]/2; j++) cout << letra;
            letra++;
        }
        letra = 'Z';
        for(i=25; i>=0; i--){
            for(j=0; j<letras[i]/2; j++) cout << letra;
            letra--;
        }
    }

    else{
        letra = 'A';
        for(i=0; i<26; i++){
            if(i!=letraImpar){
                for(j=0; j<letras[i]/2; j++) cout << letra;
            }
            letra++;
        }

        letra = (char)(letraImpar + 'A');
        for(j=0; j<letras[letraImpar]; j++) cout << letra;

        letra = 'Z';
        for(i=25; i>=0; i--){
            if(i!=letraImpar){
                for(j=0; j<letras[i]/2; j++) cout << letra;
            }
            letra--;
        }
    }

    cout << endl;
}