#include<iostream>

using namespace std;


int buscaBin(int x, int ini, int fim, int A[]){
    int mid = (ini + fim) / 2;
    if(ini==fim){
        return ini;
    }
    if(A[mid]<x) return buscaBin(x, mid+1, fim, A);
    return buscaBin(x, ini, mid, A);
}


int main(){
    int n, i;
    long int h, maiorDist, x1, x2, x2ant, ponto, D, maiorD;
    cin >> n >> h;
    int correntesini[n], NAOcorrentesAcumuladas[n+1], NAOcorrentesini[n+1];
    
    NAOcorrentesini[0] = 0;
    NAOcorrentesAcumuladas[0] = 0;
    x2ant = 0;
    for(i=0; i<n; i++){
        cin >> x1 >> x2;
        correntesini[i] = x1;
        NAOcorrentesini[i+1] = x2;
        NAOcorrentesAcumuladas[i] += x1 - x2ant;
        NAOcorrentesAcumuladas[i+1] = NAOcorrentesAcumuladas[i];
        x2ant = x2;
    }
    NAOcorrentesAcumuladas[n] += 2000000000 - x2ant;

    ponto = buscaBin(NAOcorrentesAcumuladas[0] + h, 1, n, NAOcorrentesAcumuladas);
    maiorD = NAOcorrentesini[ponto] - correntesini[0] + h - (NAOcorrentesAcumuladas[ponto-1] - NAOcorrentesAcumuladas[0]);
    for(i=1; i<n; i++){
        ponto = buscaBin(NAOcorrentesAcumuladas[i] + h, i, n, NAOcorrentesAcumuladas);
        D = NAOcorrentesini[ponto] - correntesini[i] + h - (NAOcorrentesAcumuladas[ponto-1] - NAOcorrentesAcumuladas[i]);
        if(D>maiorD) maiorD = D;
    }

    cout << maiorD << endl;
}