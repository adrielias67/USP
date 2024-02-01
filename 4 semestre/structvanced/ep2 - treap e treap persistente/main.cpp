#include <iostream>
#include "treap.h"
#include "treapF.h"
#include <vector>

using namespace std;


int main(){
    int n, operacao;

    // treap //
    treap Treap;
    noTreap* R = Treap.raiz;
    
    cout << "##### TREAP #####\ninsira o numero de operacoes: ";
    cin >> n;

    for(int i=0; i<n; i++){
        cin >> operacao;

        if(operacao==1){
            int x;
            cin >> x;
            R = Treap.Insert(R, x);
        }

        if(operacao==2){
            int x;
            cin >> x;
            R = Treap.Delete(R, x);
        }
        
        if(operacao==3){
            int x;
            cin >> x;
            cout << Treap.Search(R, x) << endl;
        }

        if(operacao==4){
            cout << Treap.Min(R) << endl;
        }

        if(operacao==5){
            Treap.Print(R);
        }
    }




    // treap funcional //
    treapF func;

    cout << "##### TREAP FUNCIONAL #####\ninsira o numero de operacoes: ";
    cin >> n;

    for(int i=0; i<n; i++){
        cin >> operacao;

        if(operacao==1){
            int x, r;
            cin >> r >> x;
            func.Insert(r, x);
        }

        if(operacao==2){
            int x, r;
            cin >> r >> x;
            func.Delete(r, x);
        }
        
        if(operacao==3){
            int x, r;
            cin >> r >> x;
            cout << func.Search(r, x) << endl;
        }

        if(operacao==4){
            int r;
            cin >> r;
            cout << func.Min(r) << endl;
        }

        if(operacao==5){
            int r;
            cin >> r;
            func.Print(r);
        }
    }

}