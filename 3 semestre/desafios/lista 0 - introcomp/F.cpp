#include<iostream>
using namespace std;

int mod(int x){
    if(x<0) return -x;
    return x;
}


int main(){
    int i, j, l, metade, n, pos, t, Fmeio, Fborda, menorT, maiorT;
    cin >> t;
    for(i=0;i<t;i++){
cin >> l >> n;
metade = l/2;
cin >> pos;
Fmeio = pos; Fborda = pos;
for(j=1;j<n;j++){
   cin >> pos;
   if(mod(metade-pos)<mod(metade-Fmeio)) Fmeio = pos;
   if(mod(metade-pos)>mod(metade-Fborda)) Fborda = pos;
}

if(Fmeio>metade) menorT = l-Fmeio;
else menorT = Fmeio;
if(Fborda>metade) maiorT = Fborda;
else maiorT = l-Fborda;

cout << menorT << " " << maiorT << endl;
    }
}