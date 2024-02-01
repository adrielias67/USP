#pragma once

#include <iostream>
#include "Fantasma.h"
#include "Pacman.h"

using namespace std;



/*!
 * \brief Classe: Arquivo
 * A classe arquivo lê um labirinto de um arquivo, 
 * e inicializa as posições dos personagens. 
 */ 
class Arquivo{

	// Attributes
protected:

	/*!
	 * \brief Parâmetro: (fstream*) file
	 * Arquivo de input.
	 */
	fstream* file;

	/*!
	 * \brief Parâmetro: (char*) labirinto
	 * Matriz do labirinto, em formato de vetor. 
	 */
	char* labirinto;

	/*!
	 * \brief Parâmetro: (int) linhas
	 * Número de linhas.
	 */
    int linhas;

    /*!
     * \brief Parâmetro: (int) colunas
	 * Número de colunas.
	 */
    int colunas;

	// Operations
public:

	/*!
	 * \brief Função: Arquivo
	 * Cria um arquivo.
	 */
	Arquivo();

	/*!
	 * \brief Função: ~Arquivo
	 * Destrói um arquivo.
	 */
	~Arquivo();

	/*!
	 * \brief Função: getLinhas
	 * Retorna o número de linhas no arquivo do labirinto.
	 * \return retorno: (int) número de linhas
	 */
	int getLinhas();

	/*!
	 * \brief Função: getColunas
	 * Retorna o número de colunas no arquivo do labirinto.
	 * \return retorno: (int) número de colunas
	 */
	int getColunas();

	/*!
	 * \brief Função: getLabirinto
	 * Retorna uma matriz em forma de vetor, de um labirinto.
	 * \return retorno: (char*) labirinto
	 */
	char* getLabirinto();

	/*!
	 * \brief Função: getFantasmas
	 * Lê um arquivo contendo o labirinto e retorna o número de fantasmas.
	 * \param filename: (char*) nome do arquivo
	 * \return retorno: (int) número de fantasmas
	 */
	int getNFantasmas(char* filename);

	/*!
	 * \brief Função: initalizePosicaoFantasmas
	 * Lê um arquivo contendo o labirinto e inicializa a posição dos fantasmas.
	 * \param labirinto: (char*) vetor de char do labirinto
	 * \param linhas: (int) numero de linhas do labirinto
	 * \param colunas: (int) numero de colunas do labirinto
	 * \param fantasmas: (Fantasma*) vetor dos fantasmas
	 */
	void initializePosicaoFantasmas(char* labirinto, int linhas, int colunas, Fantasma* fantasmas);

	/*!
	 * \brief Função: initalizePosicaoPacman
	 * Inicializa a posição do Pac-Man, no meio do labirinto.
	 * \param pacman: (Pacman&) Pac-Man
	 */
	void initializePosicaoPacman(Pacman& pacman);

	/*!
	 * \brief Função: leLabirinto
	 * Lê um arquivo contendo o labirinto e guarda-o no atributo char* labirinto, bem como suas linhas e colunas em seus reespectivos atributos.
	 * \param filename: (char*) nome do arquivo
	 */
	void leLabirinto(char* filename);

};

