
/*!
 * \brief Função: criaVetorAleatorio
 * Cria um vetor aleatório, com cada valor sendo um número aleatório entre
 * -9223372036854775807 e 9223372036854775807 (tamanho mínimo e máximo do
 * long long). São especificados a semente para geração desses números, e
 * o tamanho do vetor.
 * 
 * \param semente: (int) semente para geração de números aleatórios
 * \param tamanho: (int) tamanho do vetor aleatório desejado
 * \return retorno: (long long) vetor aleatório, de tamanho e semente especificados
*/
long long * criaVetorAleatorio(int semente, int tamanho);