#include <iostream>
#include <random>

using namespace std;

#define heapMaxValue 10000


typedef int item;
typedef int Key;

struct noTreap{
    int chave;
    item val;
    int sum;    // soma das folhas
    int max;    // maior chave na subárvore
    int sum_max;    // soma máxima dos sufixos
    int heapValue;    // valor heap do nó
    // ponteiros dos filhos
    noTreap * esq;
    noTreap * dir;

    // construtor de um nó
    noTreap(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(1, heapMaxValue);    //heapvalue = 0 está reservado para folhas
        heapValue = distribution(gen);
        esq = nullptr;
        dir = nullptr;
        chave = NULL;
        val = NULL;
    }
};



class treap{
    public:
        noTreap* raiz;
        
        treap();
        ~treap();

        noTreap* Insert(noTreap* no, int chave, item val, int sum); 
        
        noTreap* Delete(noTreap* no, int chave);

        void Print(noTreap* no);    // para fins de debugar
};