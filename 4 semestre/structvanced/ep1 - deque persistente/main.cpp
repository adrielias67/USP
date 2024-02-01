#include <iostream>
#include "deque.h"

using namespace std;



int main(){
    deque d;

    while(true){
        int operacao, t, x;
        cin >> operacao >> t;

        if(operacao==1){
            cin >> x;
            d.push_front(t, x);
        }

        if(operacao==2){
            cin >> x;
            d.push_back(t, x);
        }

        if(operacao==3){
            d.pop_front(t);
        }

        if(operacao==4){
            d.pop_back(t);
        }

        if(operacao==5){
            cout << d.front(t) << endl;
        }

        if(operacao==6){
            cout << d.back(t) << endl;
        }

        if(operacao==7){
            cin >> x;
            cout << d.k_th(t, x) << endl;
        }

        if(operacao==8){
            d.print(t);
        }
    }
}