#include "Pacman.h"
#include <iostream>

using namespace std;



Pacman::Pacman(){
	l=0;
	c=0;
}


Pacman::~Pacman(){
	cerr << "Pacman destruido\n";
}


int Pacman::verificaMovimento(int l, int c, char* labirinto, int linhas, int colunas){
	if(l==-1) l = linhas-1;
 	if(c==-1) c = colunas-1;
  	l = l % linhas;
  	c = c % colunas;

	if(labirinto[l*colunas+c] == '*') return 1;
	return 0;
}


int Pacman::foiComido(Fantasma* fantasmas, int nFantasmas){
	int i;
	for(i=0; i<nFantasmas; i++){
		if(fantasmas[i].getPosicaoC() == c && fantasmas[i].getPosicaoL() == l) return 1;
	}
	return 0;
}


int Pacman::comePacdot(char* labirinto, int colunas){
	if(labirinto[l*colunas+c] == '.'){
		labirinto[l*colunas+c] = ' ';
		return 1;
	}
	return 0;
}

