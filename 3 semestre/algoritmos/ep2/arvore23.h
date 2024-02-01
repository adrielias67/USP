#include<iostream>
#include"palavra.h"

using namespace std;

#define heapMaxValue 10000



struct no23{
    //dados 1
    Key key1;
    item val1;
    //dados 2
    Key key2;
    item val2;
    //flag de 3-nó
    bool tresNo;
    //ponteiros dos filhos
    no23 * esq;
    no23 * mid;
    no23 * dir;

    //construtor de um nó
    no23(){
        tresNo = false;
        esq = nullptr;
        mid = nullptr;
        dir = nullptr;
    }
};



class arvore23{
    private:
        //raíz da árvore
        no23 * raiz;

        //insere recursivamente na 2-3. É usada para que a adição possa ser recursiva
        no23 * insere(no23 * no, Key key, item val, bool * cresceu);

    public:
        arvore23();
        ~arvore23();

        //insere recursivamente numa folha, e corrige a 2-3 subindo
        void add(Key key, item val);

        //faz uma busca bi/tri-nária
        item value(Key key);
};