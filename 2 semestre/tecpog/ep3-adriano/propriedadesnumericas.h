
/*!
 * \brief Função: ehPar
 * Verifica se um número é par. Para isso, utiliza o resto da divisão
 * desse número por 2. Se o resto for 0, o número é par. Caso o resto
 * seja 1, o número não é par.
 *
 * \param numero: (long long) número que vai ter a paridade testada
 * \return retorno: (int) 1 se for par. 0 se não for par.
*/
int ehPar(long long numero);

/*!
 * \brief Função: ehPrimo
 * Verifica se um número é primo. Para isso, verifica se esse número 
 * é divisível por algum outro entre 2 até a raiz desse número. Para
 * fazer essa verificação, vê se o resto da divisão por algum outro 
 * é 0: caso seja 0, o número não é primo, caso não haja nenhum outro
 * número que dê resto 0, o número é primo.
 * 
 * \param numero: (long long) número que vai ser testado como primo
 * \return retorno: (int) 1 se for primo. 0 se não for primo.
*/
int ehPrimo(long long numero);

/*!
 * \brief Função: ehQuadradoPerfeito
 * Verifica se um número é quadrado perfeito. Para isso, faz uma busca
 * binária, até encontrar o maior número cujo quadrado não é maior que
 * o número dado. Caso o quadrado do número encontrado seja igual ao 
 * número dado, este é quadrado perfeito, caso contrário, ele não é
 * quadrado perfeito.
 *
 * \param numero: (long long) número que vai ser testado como quadrado perfeito
 * \return retorno: (int) 1 se for quadrado perfeito. 0 se não for quadrado perfeito.
*/
int ehQuadradoPerfeito(long long numero);

/*!
 * \brief Função: ehCuboPerfeito
 * Verifica se um número é cubo perfeito. Para isso, faz uma busca binária, 
 * até encontrar o maior número cujo cubo não é maior que o número dado. 
 * Caso o cubo do número encontrado seja igual ao número dado, este é
 * cubo perfeito, caso contrário, ele não é cubo perfeito. (obs: caso o
 * número seja negativo, as mesmas operações são feitas com seu módulo)
 *
 * \param numero: (long long) número que vai ser testado como cubo perfeito
 * \return retorno: (int) 1 se for cubo perfeito. 0 se não for cubo perfeito.
*/
int ehCuboPerfeito(long long numero);

/*!
 * \brief Função: ehFibonacci
 * Verifica se um número faz parte da sequência de Fibonacci. Para isso,
 * calcula a sequência de Fibonacci até achar nela um número que não 
 * seja menor que o dado. Se o número achado for igual ao dado, este 
 * é Fibonacci, caso o número achado seja diferente ao dado, ele não 
 * é Fibonacci.
 * 
 * \param numero: (long long) número que vai ser testado como Fibonacci
 * \return retorno: (int) 1 se for Fibonacci. 0 se não for Fibonacci.
*/
int ehFibonacci(long long numero);

/*!
 * \brief Função: ehFaltorial
 * Verifica se um número faz parte da sequência dos fatoriais. Para isso,
 * calcula a sequência de fatoriais até achar nela um número que não 
 * seja menor que o dado. Se o número achado for igual ao dado, este 
 * é fatorial, caso o número achado seja diferente ao dado, ele não é 
 * fatorial.
 * 
 * \param numero: (long long) número que vai ser testado como fatorial
 * \return retorno: (int) 1 se for fatorial. 0 se não for fatorial.
*/
int ehFatorial(long long numero);