#pragma once

#include "Arquivo.h"
#include "Fantasma.h"
#include "Pacman.h"

#define MAX 256



/*!
 * \brief Classe: Labirinto
 * A classe labirinto imprime um labirinto. 
 */ 
class Labirinto : public Arquivo {

  // Operations
public:

  /*!
   * \brief Função: Labirinto
   * Cria um labirinto.
   */
  Labirinto();

  /*!
   * \brief Função: ~Labirinto
   * Destrói um labirinto.
   */
  ~Labirinto();

  /*!
   * \brief Função: imprimeLabirinto
   * Imprime o labirinto, com os fantasmas e Pac-Man em suas posições.
   * Se houverem fantasmas em cima de pac-dots, imprime "F".
   * Se hoverem fantasmas em cima de fantasmas, imprime um único "F".
   * Se houver um fantasma em cima do Pac-Man, imprime "X".
   * \param : (Pacman&) pacman do labirinto
   * \param : (Fantasma*) vetor dos fantasmas
   * \param : (int) nFantasmas número de fantasmas
   */
  void imprimeLabirinto(Pacman& pacman, Fantasma* fantasmas, int nFantasmas);
};

