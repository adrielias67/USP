#pragma once

#include "Personagem.h"



/*!
 * \brief Classe: Fantasma
 * A classe fantasma é responsável pelo movimento pseudo-aleatório dos fantasmas. 
 */  
class Fantasma : public Personagem{ 

  // Operations
public:

  /*!
   * \brief Função: Fantasma
   * Cria um fantasma.
   */
  Fantasma();

  /*!
   * \brief Função: ~Fantasma
   * Destrói um fantasma.
   */
  ~Fantasma();

  /**
   * Move um fantasma numa direção pseudo-aleatória.
   * \param labirinto: (char*) vetor de char do labirinto
   * \param linhas: (int) numero de linhas do labirinto
   * \param colunas: (int) numero de colunas do labirinto
   * \param fantasmas: (Fantasma&)
   */
  void moveFantasmaAleatorio(char* labirinto, int linhas, int colunas , Fantasma& fantasma);

};

