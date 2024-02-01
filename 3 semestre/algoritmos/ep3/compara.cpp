#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main(){
    string a, b;
    cin >> a >> b;
    
    for(int i=0; i<a.length(); i++){
        if(a[i] != b[i]){
            cout << "noggers...\n";
            return 0;
        }
    }

    cout << "poggers!!!\n";
}