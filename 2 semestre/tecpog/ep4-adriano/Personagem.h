#pragma once



/*!
 * \brief Classe: Personagem
 * A classe personagem cria personagens de posição l (linha) e c (coluna) no labirinto.
 * É possível mexer com suas posições.
 */  
class Personagem {

  // Attributes
protected:

  /*!
   * \brief Parâmetro: (int) l
   * Índice da linha do labirinto em que está o personagem.
   */
  int l;

  /*!
   * \brief Parâmetro: (int) c
   * Índice da coluna do labirinto em que está o personagem.
   */
  int c;

  // Operations
public:
   
  /*!
   * \brief Função: setPosicao
   * Muda a posição do personagem para (l,c) no labirinto.
   * \param l: (int) Índice da linha do labirinto em que o personagem será colocado
   * \param c: (int) Índice da coluna do labirinto em que o personagem será colocado
   * \param labirinto: (char*) vetor de char do labirinto
   * \param linhas: (int) numero de linhas do labirinto
   * \param colunas: (int) numero de colunas do labirinto
   * \return retorno: (int) Se o movimento for válido retorna 0, se for inválido retorna 1
   */
  int setPosicao(int l, int c, char* labirinto, int linhas, int colunas);

  /*!
   * \brief Função: getPosicaoL
   * Acessa e retorna a posição l (linha) do personagem.
   * \return retorno: (int) Retorna a posição l (linha) do personagem
   */
  int getPosicaoL();

  /*!
   * \brief Função: getPosicaoC
   * Acessa e retorna a posição c (coluna) do personagem.
   * \return retorno: (int) Retorna a posição c (coluna) do personagem
   */
  int getPosicaoC();

};

