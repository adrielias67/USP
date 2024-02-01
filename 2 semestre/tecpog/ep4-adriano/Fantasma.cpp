#include "Fantasma.h"
#include <iostream>
#include <random>

using namespace std;



Fantasma::Fantasma(){
	l=0;
	c=0;
}


Fantasma::~Fantasma(){
	cerr << "Fantasma destruido\n";
}

void Fantasma::moveFantasmaAleatorio(char* labirinto, int linhas, int colunas ,Fantasma& fantasma){
	int direcaoC, direcaoL, direcaoSorteada;
	random_device seed;
	default_random_engine gerador(seed());
	uniform_int_distribution<int> distrI(1,4);
	
	do{
		direcaoSorteada = distrI(gerador);

		if(direcaoSorteada == 1){
			direcaoL = -1;
			direcaoC = 0;
		}
		else if(direcaoSorteada == 2){
			direcaoL = 0;
			direcaoC = 1;
		}
		else if(direcaoSorteada == 3){
			direcaoL = 1;
			direcaoC = 0;
		}
		else{
			direcaoL = 0;
			direcaoC = -1;
		}

	}while(fantasma.setPosicao(fantasma.getPosicaoL()+direcaoL, fantasma.getPosicaoC()+direcaoC, labirinto, linhas, colunas));
}

