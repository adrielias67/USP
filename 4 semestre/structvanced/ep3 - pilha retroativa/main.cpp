#include <iostream>
#include "pilhaR.h"

using namespace std;


int main(){
    pilhaR pilha;

    while(true){
        int operacao, t, x;
        cin >> operacao;
        if(cin.eof()) break;
        cin >> t;

        if(operacao==1){
            cin >> x;
            pilha.Insert(t, "Push", x);
        }

        if(operacao==2){
            pilha.Insert(t, "Pop", NULL);
        }

        if(operacao==3){
            pilha.Delete(t);
        }

        if(operacao==4){
            cout << pilha.Size(t) << endl;
        }

        if(operacao==5){
            cout << pilha.Top(t) << endl;
        }

        if(operacao==6){
            cin >> x;
            cout << pilha.Kth(t, x) << endl;
        }

        if(operacao==7){
            pilha.Print(t);
        }
        
        // para debugar
        //cout << "--------------------------" << endl;
        //pilha.arvore.Print(pilha.arvore.raiz);
        //cout << "--------------------------" << endl;
    }
}