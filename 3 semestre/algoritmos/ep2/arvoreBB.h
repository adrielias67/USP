#include<iostream>
#include"palavra.h"

using namespace std;



struct noABB{
    //dados
    Key key;
    item val;
    //ponteiros dos filhos
    noABB * esq;
    noABB * dir;

    //construtor de um nó
    noABB(){
        esq = nullptr;
        dir = nullptr;
    }
};



class arvoreBB{
    private:
        //raíz da árvore
        noABB * raiz;

    public:
        arvoreBB();
        ~arvoreBB();

        //inserção iterativa
        void add(Key key, item val);

        //faz uma busca binária
        item value(Key key);
};