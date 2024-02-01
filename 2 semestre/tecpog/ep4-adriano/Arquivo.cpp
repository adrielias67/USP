#include "Arquivo.h"
#include <iostream>
#include <fstream>

#define MAX 256

using namespace std;



Arquivo::Arquivo(){
	file = new fstream;
	linhas = 0;
	colunas = 0;
}


Arquivo::~Arquivo(){
	delete(file);
	delete(labirinto);
	cerr << "Arquivo destruido\n";
}


int Arquivo::getLinhas(){
	return linhas;
}


int Arquivo::getColunas(){
	return colunas;
}


char* Arquivo::getLabirinto(){
	return labirinto;
}


int Arquivo::getNFantasmas(char* filename){
	int j, nFantasmas=0;
    char linha[MAX];
    file->open(filename);

    while(file->getline(linha, MAX)){
    	for(j=0; j<MAX; j++){
    		if(linha[j]== 'F') nFantasmas++;
    	}
    }
    file->close();
    return nFantasmas;
}


void Arquivo::initializePosicaoFantasmas(char* filename, int linhas, int colunas, Fantasma* fantasmas){
	int i=0, j, k=0;
    char linha[MAX];
    file->open(filename);

    while(file->getline(linha, MAX)){
        for(j=0; j<colunas; j++){
            if(linha[j]== 'F'){
                fantasmas[k].setPosicao(i, j, labirinto, linhas, colunas);
                k++;
            }
        }
        i++;
    }
    file->close();
}


void Arquivo::initializePosicaoPacman(Pacman& pacman){
    pacman.setPosicao(linhas/2, colunas/2, labirinto, linhas, colunas);
}


void Arquivo::leLabirinto(char* filename){
    int i=0, j;
    char linha[MAX];
    file->open(filename);

    while(file->getline(linha, MAX)){
        colunas = file->gcount()-1;
        i++;
    }
    linhas = i;
    file->close();

    labirinto = new char[linhas*colunas];
    i = 0;

    file->open(filename);
    while(file->getline(linha, MAX)){
    	for(j=0; j<colunas; j++){
    		if(linha[j]== 'F') labirinto[i*colunas+j] = '.';
    		else labirinto[i*colunas+j] = linha[j];
    	}
        i++;
    }
    file->close();
}

