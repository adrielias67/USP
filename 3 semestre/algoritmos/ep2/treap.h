#include<iostream>
#include"palavra.h"

using namespace std;

#define heapMaxValue 10000



struct noTreap{
    //dados
    Key key;
    item val;
    //valor heap do nó
    int heapValue;
    //ponteiros dos filhos
    noTreap * esq;
    noTreap * dir;

    //construtor de um nó
    noTreap(){
        srand(time(0));
        heapValue = rand() % heapMaxValue;
        esq = nullptr;
        dir = nullptr;
    }
};



class treap{
    private:
        //raíz da treap
        noTreap * raiz;

        //insere recursivamente no heap. É usada para que a adição possa ser recursiva
        noTreap * insere(noTreap * no, Key key, item val);

    public:
        treap();
        ~treap();

        //insere recursivamente numa folha, e corrige o heap subindo
        void add(Key key, item val);

        //faz uma busca binária
        item value(Key key);
};