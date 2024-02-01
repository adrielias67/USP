#include <iostream>
#include <random>

using namespace std;

#define heapMaxValue 10000


typedef int item;
typedef int Key;

struct noTreap{
    item val;
    //valor heap do nó
    int heapValue;
    //ponteiros dos filhos
    noTreap * esq;
    noTreap * dir;

    //construtor de um nó
    noTreap(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, heapMaxValue);
        heapValue = distribution(gen);
        esq = nullptr;
        dir = nullptr;
    }
};



class treap{
    public:
        noTreap* raiz;
        
        treap();
        ~treap();

        noTreap* Insert(noTreap* no, item val); 
        
        noTreap* Delete(noTreap* no, item val);

        bool Search(noTreap* no, item val);

        int Min(noTreap* no);

        void Print(noTreap* no);
};