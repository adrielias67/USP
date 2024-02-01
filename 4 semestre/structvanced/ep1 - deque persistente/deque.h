#include <iostream>
#include <vector>

using namespace std;



typedef int item;


class no{
    public:
        item value;
        int depth;
        int id;    // os nós possuem im id para possibilitar a operação "==" entre 2 nós
                   // o primeiro nó criado tem id=0, o segundo id=1, o terceiro id=2, ...
        no * parent;
        no * jump;
        no(item value, int depth, no* parent, no* jump);
};


class deque{
    public:
        deque();
        ~deque();

        vector<no*> inis;    // vector dos inícios de cada deque, i0, i1, i2, ...
        vector<no*> fins;    // vector dos fins de cada deque, f0, f1, f2, ...

        item front(int d);

        item back(int d);

        void push_front(int d, item x);

        void push_back(int d, item x);

        void pop_front(int d);

        void pop_back(int d);

        item k_th(int d, int k);

        void print(int d);
};