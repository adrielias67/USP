#include "Labirinto.h"
#include <iostream>
#include <fstream>

using namespace std;



Labirinto::Labirinto(){

}


Labirinto::~Labirinto(){
  cerr << "Labirinto destruido\n";
}

void Labirinto::imprimeLabirinto(Pacman& pacman, Fantasma* fantasmas, int nFantasmas){
  int i, j, k, temFantasma=0, fantasmaComeuPacman=0;

  for(i=0; i<linhas; i++){
    for(j=0; j<colunas; j++){
      
      for(k=0; k<nFantasmas; k++){
        if(fantasmas[k].getPosicaoL() == i && fantasmas[k].getPosicaoC() == j){
          temFantasma = 1;
          if(pacman.getPosicaoL()== i && pacman.getPosicaoC() == j){
            fantasmaComeuPacman = 1;
          }
          break;
        }
      }
      if(temFantasma){
        if(fantasmaComeuPacman) cout << "X";
        else cout << "F";
        fantasmaComeuPacman = 0;
      }
      else if(pacman.getPosicaoL()== i && pacman.getPosicaoC() == j) cout << "C";
      else if(labirinto[i*colunas+j] == '*') cout << "*";
      else if(labirinto[i*colunas+j] == '.') cout << ".";
      else cout << " ";

      temFantasma = 0;
    }
    cout << endl;
  }
  cout << endl;
}

