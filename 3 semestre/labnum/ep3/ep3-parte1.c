/*
* Nome: Adriano Elias Andrade
* Nusp: 13671682
* EP3 de MAC0210
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nPontosTabela 7



// guarda os valores dos denominadores do Li, para cada Lagrange i
double *denominador;

void calculaDenominador(double x[], int nPontos){
    // Calcula os denominadores de cada termo de Lagrange 
    int i, j;
    for(j=0; j<nPontos; j++){
        denominador[j] = 1;
        for(i=0; i<nPontos; i++){
            if(i!=j) denominador[j] *= x[j] - x[i]; 
        }
    }
}


double evalF(double xEval, double x[], double y[], int nPontos){
    // Avalia o valor interpolado de xEval por Lagrange 
    double nominador[nPontos];
    int i, j;

    for(j=0; j<nPontos; j++){
        nominador[j] = 1;
        for(i=0; i<nPontos; i++){
            if(i!=j) nominador[j] *= xEval - x[i];
        }
    }

    double somatoria=0;
    for(j=0; j<nPontos; j++){
        somatoria += y[j] * nominador[j]/denominador[j];
    }

    return somatoria;
}


double evalTrap(double intervalo, double y[], int nPontos){
    // Calcula a aproximação por trapézio, a partir dos pontos interpolados
    int i;
    double soma=0;
    for(i=0; i<nPontos-1; i++){
        soma += intervalo * (y[i]+y[i+1]) / 2;
    }
    return soma;
}


double evalSimp(double intervalo, double y[], int nPontos){
    // Calcula a aproximação por Simpson, a partir dos pontos interpolados
    int i;
    double soma=0;
    for(i=0; i<nPontos-2; i++){
        soma += intervalo * (y[i] + 4*y[i+1] + y[i+2]) / 6;
    }
    return soma;
}


int main(){
    // Leitura
    int metodo, nPontosInterpolar;
    printf("Digite o metodo a ser utilizado (1)Trapezio ou (2)Simpson: ");
    scanf("%d", &metodo);
    printf("Digite o numero de pontos a serem interpolados: ");
    scanf("%d", &nPontosInterpolar);

    // Dados da tabela
    double xTabela[nPontosTabela] = {0,5,10,15,20,25,30};
    double yTabela[nPontosTabela] = {0.0, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537}; 

    // Interpolação dos pontos
    double x;
    double y[nPontosInterpolar];
    double intervalo = (xTabela[nPontosTabela-1] - xTabela[0]) / (nPontosInterpolar-1);

    denominador = malloc(sizeof(double) * nPontosTabela);
    calculaDenominador(xTabela, nPontosTabela);

    for(int i=0; i<nPontosInterpolar; i++){
        x = xTabela[0] + i*intervalo;
        y[i] = evalF(x, xTabela, yTabela, nPontosTabela);
    }

    // Cálculo da integral por trapézio composto
    if(metodo==1){
        printf("A integral, aproximada por trapezio composto vale: %lf\n", evalTrap(intervalo, y, nPontosInterpolar));
    }
    
    // Cálculo da integral por Simpson composto
    else{
        printf("A integral, aproximada por Simpson composto vale: %lf\n", evalSimp(intervalo, y, nPontosInterpolar));
    }

    free(denominador);

    return 0;
}