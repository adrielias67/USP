#include<iostream>
#include"palavra.h"

using namespace std;

#define heapMaxValue 10000



struct noRN{
    //dados
    Key key;
    item val;
    //flag de nó preto
    bool preto;
    //ponteiros dos filhos
    noRN * esq;
    noRN * dir;

    //construtor de um nó
    noRN(){
        preto = false;
        esq = nullptr;
        dir = nullptr;
    }
};



class arvoreRN{
    private:
        //raíz da árvore
        noRN * raiz;

        //insere recursivamente na rubro-negra. É usada para que a adição possa ser recursiva
        noRN * insere(noRN * no, Key key, item val);

    public:
        arvoreRN();
        ~arvoreRN();

        //insere recursivamente numa folha, e corrige a rubro-negra subindo
        void add(Key key, item val);

        //faz uma busca binária
        item value(Key key);
};