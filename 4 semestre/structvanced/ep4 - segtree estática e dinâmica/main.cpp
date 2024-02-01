// Para fazer este trabalho, levei aproximadamente 11 horas.
//
// Para escolher entre a AS e a ASD, fiz um main para cada, e basta
// escolher qual será utilizada no main principal.
//
// Para o print da ASD, por algum motivo, os intervalos dos dois nós
// mais na extremidade estão sendo impressos com valor um errado. Ainda
// assim, o programa funciona corretamente.

#include <iostream>
#include <algorithm>
#include "as.h"
#include "asd.h"

using namespace std;



void main_as(){
    lista_seg S;
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        int s,f;
        cin >> s >> f;
        S.push_back(make_pair(s,f));
    }
    as segtree(S);

    int op;
    for(;;){
        
        cin >> op;
        if(cin.eof()) return;
    
        if(op==1){
            int x;
            cin >> x;
            vector<int> segs = segtree.Segments(segtree.raiz, x);
            sort(segs.begin(), segs.end());
            if(segs.empty()) cout << "nenhum segmento";
            for(int i=0; i<segs.size(); i++){
                cout << segs[i] << " ";
            }
            cout << endl;
        }

        else{
            segtree.Print(segtree.raiz);
        }

    }
}


void main_asd(){
    asd segtree;
    
    int op;
    for(;;){

        cin >> op;
        if(cin.eof()) return;

        if(op==1){
            int s, f;
            cin >> s >> f;
            segtree.Insert(make_pair(s, f));
        }

        if(op==2){
            int x;
            cin >> x;
            vector<int> segs = segtree.Segments(x);
            sort(segs.begin(), segs.end());
            if(segs.empty()) cout << "nenhum segmento";
            for(int i=0; i<segs.size(); i++){
                cout << segs[i] << " ";
            }
            cout << endl;
        }

        if(op==3){
            segtree.Print();
        }

    }
}


int main(){
    //main_as();
    main_asd();
}