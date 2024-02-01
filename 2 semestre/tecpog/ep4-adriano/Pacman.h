#pragma once

#include "Personagem.h"
#include "Fantasma.h"



/*!
 * \brief Classe: Pacman
 * A classe pacman é responsável pelo movimento do Pac-Man, 
 * detecção de colisãocom fantasmas, e comer as pac-dots do labirinto. 
 */  
class Pacman : public Personagem {

  // Operations
public:

  /*!
   *\brief Função: Fantasma
   * Cria o Pac-Man.
   */
  Pacman();

  /*!
   * \brief Função: ~Pacman
   * Destrói o Pac-Man.
   */
  ~Pacman();

  /*!
   * \brief Função: verificaMovimento
   * Verifica se o movimento para a posição (l,c) do labirinto é valida, sem mover o Pac-Man para lá.
   * \param l: (int) Índice da linha do labirinto em que o personagem pretende ser colocado
   * \param c: (int) Índice da coluna do labirinto em que o personagem pretende ser colocado
   * \param labirinto: (char*) vetor de char do labirinto
   * \param linhas: (int) numero de linhas do labirinto
   * \param colunas: (int) numero de colunas do labirinto
   * \return retorno: (int) Retorna 0 se o movimento for válido, e retorna 1 se não for
   */
  int verificaMovimento(int l, int c, char* labirinto, int linhas, int colunas);

  /*!
   * \brief Função: foiComido
   * Verifica se nesse instante, há algum fantasma na mesma posição que o Pac-Man.
   * \param fantasmas (Fantasma*) vetor dos fantasmas
   * \param : (int) nFantasmas número de fantasmas
   * \return retorno: (int) Caso foi comido, retorna 1, caso não, retorna 0
   */
  int foiComido(Fantasma* fantasmas, int nFantasmas);

  /*!
   * \brief Função: comePacdot
   * Caso haja uma pac-dot na posição do Pac-Man, ela é retirada do labirinto.
   * \param labirinto: (char*) vetor de char do labirinto
   * \param colunas: (int) numero de colunas do labirinto
   * \return retorno: (int) Caso alguma pacdot foi comida, retorna 1, caso contrário retorna 0
   */
  int comePacdot(char* labirinto, int colunas);

};

