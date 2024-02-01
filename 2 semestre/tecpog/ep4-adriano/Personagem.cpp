#include "Personagem.h"

#include <iostream>



int Personagem::setPosicao(int l, int c, char* labirinto, int linhas, int colunas){
  if(l==-1) l = linhas-1;
  if(c==-1) c = colunas-1;
  l = l % linhas;
  c = c % colunas;

  if(labirinto[l*colunas+c] != '*'){
    this->l = l;
    this->c = c;
    return 0;
  }
  return 1;
}


int Personagem::getPosicaoL(){
  return l;
}


int Personagem::getPosicaoC(){
  return c;
}

