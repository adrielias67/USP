#pragma once
#include <iostream>
#include <vector>

using namespace std;



typedef vector<pair<int,int>> lista_seg;


struct no_as{
    bool ini_fechado;     // intervalo: 1=fechado, 0=aberto
    bool fim_fechado;     // intervalo: 1=fechado, 0=aberto
    int ini;              // inicio do intervalo
    int fim;              // fim do intervalo
    int h;                // altura do nó
    no_as* esq;
    no_as* dir;
    vector<int> lista;    // lista de segmentos no nó
    no_as(){
        esq = nullptr;
        dir = nullptr;
    }
};


class as{
    public:
        no_as* raiz;
        lista_seg segmentos;
    
        as(lista_seg S);
        ~as();
    
        vector<int> Segments(no_as* r, int x);
    
        void Print(no_as* r); 
};
