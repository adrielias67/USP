#include <bits/stdc++.h>
using namespace std;

using coord = long int;



int main(){
    int n;
    cin >> n;

    coord matrizMagica[n+1][2];
    for(int i=0; i<n; i++){
        cin >> matrizMagica[i][0] >> matrizMagica[i][1];
    }
	matrizMagica[n][0] = matrizMagica[0][0];
	matrizMagica[n][1] = matrizMagica[0][1];	

	coord area=0;
    for(int i=0; i<n; i++){
    	area += matrizMagica[i][0] * matrizMagica[i+1][1];
		area -= matrizMagica[i][1] * matrizMagica[i+1][0];
	}

    cout << abs(area) << endl;
}