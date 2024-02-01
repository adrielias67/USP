#include <iostream>
#include <vector>
#include "treap.h"

using namespace std;

typedef int item;


class pilhaR{    
    public:
        pilhaR();
        ~pilhaR();

        treap arvore;

        void Insert(int t, string op, item x);
        void Delete(int t);
        
        int Size(int t);
        
        item Kth(int t,int k);
        item Top(int t);
        
        void Print(int t);
};