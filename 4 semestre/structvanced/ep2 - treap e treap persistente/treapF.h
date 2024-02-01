#include <iostream>
#include <vector>
#include <random>

using namespace std;

#define heapMaxValue 10000


typedef int item;
typedef int Key;

struct noTreapF{
    item val;
    //valor heap do nó
    int heapValue;
    //ponteiros dos filhos
    noTreapF * esq;
    noTreapF * dir;

    //construtor de um nó
    noTreapF(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, heapMaxValue);
        heapValue = distribution(gen);
        esq = nullptr;
        dir = nullptr;
    }
};



class treapF{
    public:
        vector<noTreapF*> raizes;

        treapF();
        ~treapF();
        
        void Insert(int no, item val); 
        
        void Delete(int no, item val);

        bool Search(int no, item val);

        int Min(int no);

        void Print(int no);
};