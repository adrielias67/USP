#include "Partida.h"
#include <iostream>


Partida::Partida(){
	pontos = 0;
	pacdotsRestantes = 0;
}


Partida::~Partida(){
	cerr << "Partida destruida\n";
}


int Partida::getPacdotsRestantes(){
	return pacdotsRestantes;
}


int Partida::getPontos(){
	return pontos;
}


void Partida::initializePacdotsRestantes(char* labirinto, int linhas, int colunas){
	pacdotsRestantes = 0;
  	int i, j;

  	for(i=0; i<linhas; i++){
  		for(j=0; j<colunas; j++){
  			if(labirinto[i*colunas+j] == '.') pacdotsRestantes++;
  		}
  	}
}


void Partida::decreasePacdotsRestantes(){
	pacdotsRestantes--;
	pontos++;
}