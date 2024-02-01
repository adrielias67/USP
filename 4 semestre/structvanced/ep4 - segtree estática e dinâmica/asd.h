#include <iostream>
#include <vector>
#include "as.h"

using namespace std;

#define MAX 1000



class asd{
    public:
        as* raizes[MAX];
        int size;    // índice da maior raiz

        asd();
        ~asd();

        vector<int> Segments(int x);

        void Insert(pair<int,int> s);

        void Print();
};