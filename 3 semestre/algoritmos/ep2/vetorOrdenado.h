#include<iostream>
#include"palavra.h"

using namespace std;



struct noVO{
    //dados
    Key key;
    item val;
};



class vetorOrdenado{
    private:
        //o vetor em si
        noVO * vetor;

        //tamanho absoluto do vetor (inclui casas sem palavra)
        int size;

        //numero de palavras no vetor
        int nPalavras;

        //da resize no tamanho do vetor
        void resize();

        //empurra todos as casas do vetor para frente, a partir da postição dada 
        void empurra(int pos);

    public:
        vetorOrdenado();
        ~vetorOrdenado();

        //add procura com busca binária e insere na posição encontrada
        void add(Key key, item val);

        //faz uma busca binária
        item value(Key key);
};