#include <bits/stdc++.h>
using namespace std;


int main(){
    int t;
    cin >> t;

    for(int i=0; i<t; i++){
        cout << "Case " << i+1 << ":\n";

        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int m;
        cin >> m;

        for(int j=0; j<m; j++){
            int xv, yv;
            cin >> xv >> yv;

            if(xv>x1 && xv<x2 && yv>y1 && yv<y2)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }
}