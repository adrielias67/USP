#include <iostream>
#include "Labirinto.h"


/*!
 * \brief Classe: Partida
 * A classe partida guarda os pontos e o número de pacdots 
 * restantes da partida, e altera seus valores.
 */  
class Partida{

  // Attributes
private:

  /*!
   * \brief Parâmetro: (int) pontos
   * Número de pontos feitos na partida.
   */
  int pontos;

  /*!
   * \brief Parâmetro: (int) pacdotsRestantes
   * Números de pac-dots restantes na partida.
   */
  int pacdotsRestantes;

  // Operations
public:

  /*!
   * \brief Função: Partida
   * Cria uma partida.
   */
  Partida();

  /*!
   * \brief Função: ~Partida
   * Destrói uma partida.
   */
  ~Partida();

  /*!
   * \brief Função: getPacdotsRestantes
   * Retorna o número de pac-dots restantes.
   * \return retorno: (int) número de pac-dots restantes
   */
  int getPacdotsRestantes();

  /*!
   * \brief Função: getPontos
   * Retorna o número de pontos feitos na partida até esse instante.
   * \return retorno: (int) pontos feitos na partida
   */
  int getPontos();

  /*!
   * \brief Função: initializePacdotsRestantes
   * Inicializa o numero de pac-dots da partida, dado um tabuleiro.
   * \param labirinto: (char*) vetor de char do labirinto
   * \param linhas: (int) numero de linhas do labirinto
   * \param colunas: (int) numero de colunas do labirinto
   */
  void initializePacdotsRestantes(char* labirinto, int linhas, int colunas);

  /*!
   * \brief Função: decreasePacdotsRestantes
   * Decrementa o numero de pacdots restantes, e incrementa a pontuação.
   */
  void decreasePacdotsRestantes();

};

