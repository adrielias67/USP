#include <iostream>
//#include <gtest/gtest.h>

#include "Personagem.h"
#include "Pacman.h"
#include "Fantasma.h"
#include "Labirinto.h"
#include "Partida.h"
#include "Arquivo.h"

#define MAX 256



int main(int argc, char* argv[]){
	if(argc!=2){
		cout << "Uso: ./ep4 <nome do arquivo de mapa>\n";
		exit(1);
	}
	
	#ifdef TESTS
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	#endif

	Labirinto input;
	Partida partida;
	Pacman pacman;
	int linhas, colunas, nFantasmas, k, inputDirecaoL, inputDirecaoC, inputInvalido=0, GameOver=0;
	char* labirinto;
	labirinto = new char[MAX*MAX];
	char inputDirecao;

	
	input.leLabirinto(argv[1]);
	labirinto = input.getLabirinto();
	linhas = input.getLinhas();
  	colunas = input.getColunas();

  	nFantasmas = input.getNFantasmas(argv[1]);
  	Fantasma fantasmas[nFantasmas];

  	input.initializePosicaoFantasmas(argv[1], linhas, colunas, fantasmas);
  	input.initializePosicaoPacman(pacman);

	partida.initializePacdotsRestantes(labirinto, linhas, colunas);

	input.imprimeLabirinto(pacman, fantasmas, nFantasmas);
	cout << "Direcao (a - esquerda, d - direita, w - cima, s - baixo): ";
	while(partida.getPacdotsRestantes()>0){

		cin >> inputDirecao;
		inputInvalido = 0;

		if(inputDirecao=='w'){
			inputDirecaoL = -1;
			inputDirecaoC = 0;
		}
		else if(inputDirecao=='a'){
			inputDirecaoL = 0;
			inputDirecaoC = -1;
		}
		else if(inputDirecao=='s'){
			inputDirecaoL = 1;
			inputDirecaoC = 0;
		}
		else if(inputDirecao=='d'){
			inputDirecaoL = 0;
			inputDirecaoC = 1;
		}
		else inputInvalido = 1;

		if(!inputInvalido && pacman.verificaMovimento(pacman.getPosicaoL()+inputDirecaoL, pacman.getPosicaoC()+inputDirecaoC, labirinto, linhas, colunas)) inputInvalido = 1;

		if(!inputInvalido){
			for(k=0; k<nFantasmas; k++){
				fantasmas[k].moveFantasmaAleatorio(labirinto, linhas, colunas, fantasmas[k]);
			}
		}

		if(pacman.foiComido(fantasmas, nFantasmas)){
			GameOver = 1;
			input.imprimeLabirinto(pacman, fantasmas, nFantasmas);
			break;
		}

		if(!inputInvalido){
			pacman.setPosicao(pacman.getPosicaoL()+inputDirecaoL, pacman.getPosicaoC()+inputDirecaoC, labirinto, linhas, colunas);
			if(pacman.comePacdot(labirinto, colunas)){
				partida.decreasePacdotsRestantes();
			}
		}

		if(pacman.foiComido(fantasmas, nFantasmas)){
			GameOver = 1;
			input.imprimeLabirinto(pacman, fantasmas, nFantasmas);
			break;
		}

		input.imprimeLabirinto(pacman, fantasmas, nFantasmas);
		if(inputInvalido) cout << "Input invalido!\n";
		if(partida.getPacdotsRestantes()>0) cout << "Direcao (a - esquerda, d - direita, w - cima, s - baixo): ";
	}

	if(!GameOver) cout << "Congratulations! Pontos = " << partida.getPontos() << endl;
	else cout << "Game over! Pontos = " << partida.getPontos() << endl;

	delete(labirinto);

	return 0;
}	



// TEST(PersonagemSuite, PersonagemAndaCerto){
// 	Personagem PTest;
// 	char labirinto[] = {'*', '*', 'F', '.'};
// 	int linhas = 2, colunas = 2;
// 	int cIni, lIni, cDepois, lDepois;
// 
// 	PTest.setPosicao(1, 0, labirinto, linhas, colunas);
// 	cIni=PTest.getPosicaoC();
// 	lIni=PTest.getPosicaoL();
// 
// 	PTest.setPosicao(lIni+1, cIni, labirinto, linhas, colunas);
// 	cDepois=PTest.getPosicaoC();
// 	lDepois=PTest.getPosicaoL();
// 	ASSERT_EQ(cIni-cDepois,0);
// 	ASSERT_EQ(lIni-lDepois,0);
// 
// 	PTest.setPosicao(lIni, cIni+1, labirinto, linhas, colunas);
// 	cDepois=PTest.getPosicaoC();
// 	lDepois=PTest.getPosicaoL();
// 	ASSERT_EQ(cIni-cDepois,-1);
// 	ASSERT_EQ(lIni-lDepois,0);
// 
// 	PTest.setPosicao(lIni, cDepois+1, labirinto, linhas, colunas);
// 	cDepois=PTest.getPosicaoC();
// 	lDepois=PTest.getPosicaoL();
// 	ASSERT_EQ(cIni-cDepois,0);
// 	ASSERT_EQ(lIni-lDepois,0);
// }
// 
// 
// 
// TEST(FantasmaSuite, FantasmaComePacman){
// 	Pacman PTest;
// 	Fantasma FTest[1];
// 	int nFantasmas = 1;
// 	ASSERT_EQ(PTest.foiComido(FTest, nFantasmas), 1);
// }
// 
// 
// 
// TEST(PacmanSuite, PacmanComeCerto){
// 	Pacman PTest;
// 	char labirinto[] = {' ', '.'};
// 	int linhas=1, colunas=2;
// 
// 	PTest.setPosicao(0, 1, labirinto, linhas, colunas);
// 	PTest.comePacdot(labirinto, colunas);
// 
// 	ASSERT_EQ(labirinto[1], ' ');
// }
// 
// TEST(PacmanSuite, PacmanChecaMovimento){
// 	Pacman PTest;
// 	char labirinto[] = {' ', '*'};
// 	int linhas=1, colunas=2;
// 
// 	ASSERT_EQ(PTest.verificaMovimento(0, 1, labirinto, linhas, colunas), 1);
// }
// 
// 
// 
// TEST(ArquivoSuite, LabirintoInicializaCerto){
// 	Pacman PTest;
// 	Labirinto input;
// 	int linhas, colunas, nFantasmas;
// 	char* labirinto;
// 	char inputNome[] = "Ltest";
// 
// 	input.leLabirinto(inputNome);
// 	labirinto = input.getLabirinto();
// 	linhas = input.getLinhas();
//   	colunas = input.getColunas();
// 
//   	nFantasmas = input.getNFantasmas(inputNome);
//   	Fantasma FTest[nFantasmas];
// 
// 	input.initializePosicaoFantasmas(inputNome, linhas, colunas, FTest);
// 	input.initializePosicaoPacman(PTest);
// 
// 	ASSERT_EQ(FTest[0].getPosicaoL(), 0);
// 	ASSERT_EQ(FTest[0].getPosicaoC(), 0);
// 	ASSERT_EQ(FTest[1].getPosicaoL(), 2);
// 	ASSERT_EQ(FTest[1].getPosicaoC(), 2);
// 	ASSERT_EQ(PTest.getPosicaoL(), 1);
// 	ASSERT_EQ(PTest.getPosicaoC(), 1);
// 	ASSERT_EQ(labirinto[0], '.');
// }
// 
// 
// 
// TEST(PartidaSuite, PartidaInicializaCerto){
// 	Partida PTest;
// 	char labirinto[] = {' ', '.'};
// 	int linhas=1, colunas=2;
// 
// 	PTest.initializePacdotsRestantes(labirinto, linhas, colunas);
// 
// 	ASSERT_EQ(PTest.getPacdotsRestantes(), 1);
// 	ASSERT_EQ(PTest.getPontos(), 0);
// 
// 	PTest.decreasePacdotsRestantes();
// 
// 	ASSERT_EQ(PTest.getPacdotsRestantes(), 0);
// 	ASSERT_EQ(PTest.getPontos(), 1);
// }