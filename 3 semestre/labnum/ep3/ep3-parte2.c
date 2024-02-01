/*
* Nome: Adriano Elias Andrade
* Nusp: 13671682
* EP3 de MAC0210
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



void doubleAleatorio01(double **U, int nPontos, int dimensao){
    // Cria uma matriz tamanho nPontos X dimensão, de doubles aleatórios entre 0 e 1
    // Sorteia 2 números e divide o menor pelo maior para gerar um double aleatório 

    time_t t;
    srand((unsigned)time(&t));
    
    for(int i=0; i<nPontos; i++){
        for(int j=0; j<dimensao; j++){
            int a = rand();
            int b = rand();

            if(a>b) U[i][j] = (double)b / a;
            else U[i][j] = (double)a / b;
        }
    }
}


double evalG1(double x){
    // Avalia a função 1 dada no enunciado, sin(x)
    return sin(x);
}

double evalG2(double u){
    // Avalia a função 2 dada no enunciado, x³, com a troca de variável x = 4u + 3
    return powf(4*u+3, 3) * 4;
}

double evalG3(double u){
    // Avalia a função 3 dada no enunciado, e^(-x), com a troca de variável x = - u/(u-1)
    return exp(u/(u-1)) / powf(u-1, 2);
}

double evalG4(double x, double y){
    // Avalia a função 4 dada no enunciado, do círculo
    return x*x + y*y <= 1;
}


double monteCarlo(int nPontos, int dimensao, int funcao){
    // Calcula a aproximação da integral por Monte Carlo
    // com um número de dimensões e n pontos sorteados
    double **U;
    U = malloc(sizeof(double)*nPontos);
    for(int i=0; i<nPontos; i++){
        U[i] = malloc(sizeof(double)*dimensao);
    }

    double soma=0;
    for(int i=0; i<dimensao; i++){
        doubleAleatorio01(U, nPontos, dimensao);
    }

    if(funcao==1){
        for(int i=0; i<nPontos; i++){
            soma += evalG1(U[i][0]);
        }
    }

    else if(funcao==2){
        for(int i=0; i<nPontos; i++){
            soma += evalG2(U[i][0]);
        }
    }

    else if(funcao==3){
        for(int i=0; i<nPontos; i++){
            soma += evalG3(U[i][0]);
        }
    }

    else{
        for(int i=0; i<nPontos; i++){
            soma += evalG4(U[i][0], U[i][1]);
        }
    }

    for(int i=0; i<nPontos; i++){
        free(U[i]);
    }
    free(U);

    return soma / nPontos;
}


int main(){
    double m1=0, m2=0, m3=0, m4=0;

    int nPontos;
    printf("Digite o numero de pontos a serem utilizados: ");
    scanf("%d", &nPontos);

    printf("Estimativa da integral de sin(x): %lf\n", monteCarlo(nPontos, 1, 1));
    printf("Estimativa da integral de x^3: %lf\n", monteCarlo(nPontos, 1, 2));
    printf("Estimativa da integral de e^-x: %lf\n", monteCarlo(nPontos, 1, 3));
    printf("Estimativa de pi: %lf\n", monteCarlo(nPontos, 2, 4) * 4.0);

    return 0;
}