#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define tol exp(-20)        /* tolerância para comparação de dois números de ponto flutuante*/
#define max_iteracoes 10000 /* número máximo de iterações tolerado para o método do ponto fixo */



double eval_g1(double x);                   /* avalia g1 = log(2x^2) */
double eval_Dg1(double x);                  /* avalia g'1 = 2/x */
double PF_g1(double x0, int * convergiu);   /* aplica o método do ponto fixo para g1 */

double eval_g2(double x);                   /* avalia g2 = sqrt((e^x)/2) */
double eval_Dg2(double x);                  /* avalia g'2 = e^(x/2)/2*sqrt(2); */
double PF_g2(double x0, int * convergiu);   /* aplica o método do ponto fixo para g2 */

double eval_g3(double x);                   /* avalia g3 = -sqrt((e^x)/2) */
double eval_Dg3(double x);                  /* avalia g'3 = -e^(x/2)/2*sqrt(2); */
double PF_g3(double x0, int * convergiu);   /* aplica o método do ponto fixo para g3 */



int main(){
    int convergiu;
    double x0, raiz;

    printf("Digite o ponto que deseja avaliar: ");
    scanf("%lf", &x0);
    
    raiz = PF_g1(x0, &convergiu);
    if(convergiu==1) printf("Para g1 = log(2x^2), o metodo converge para: %.2lf\n", raiz);
    else printf("Para g1 = log(2x^2), o metodo nao converge\n");
    
    raiz = PF_g2(x0, &convergiu);
    if(convergiu==1) printf("Para g2 = sqrt((e^x)/2), o metodo converge para: %.2lf\n", raiz);
    else printf("Para g2 = sqrt((e^x)/2), o metodo nao converge\n");

    raiz = PF_g3(x0, &convergiu);
    if(convergiu==1) printf("Para g3 = -sqrt((e^x)/2), o metodo converge para: %.2lf\n", raiz);
    else printf("Para g3 = -sqrt((e^x)/2), o metodo nao converge\n");
}



double eval_g1(double x){
    return log(2.0) + log(x) + log(x);
}


double eval_Dg1(double x){
    if(x==0) return 2;
    return 2.0 / x;
}


double PF_g1(double x0, int * convergiu){
    /* para quando atinge um ponto com pouco erro, ou atinge max_iterações */
    /* retorna para o ponteiro passado como parâmetro se convergiu ou não */
    /* retorna para o ponteiro que não converge, se a derivara em x0 > 1 */
    int iteracoes = 1;
    double x1;
    * convergiu = 1;

    if(fabs(eval_Dg1(x0))>1.0 || x0<0.0){
        * convergiu = 0;
        return x0;
    }

    x1 = eval_g1(x0);
    while(fabs(x1-x0)>tol && iteracoes<max_iteracoes){
        iteracoes++;
        x0 = x1;
        x1 = eval_g1(x0);
    }
    if(fabs(x0-x1) > tol){
        * convergiu = 0;
        return x0;
    }
    return x1;
}



double eval_g2(double x){
    return sqrt(exp(x)) / sqrt(2.0);
}


double eval_Dg2(double x){
    return exp(x/2.0) / (2.0 * sqrt(2.0));
}


double PF_g2(double x0, int * convergiu){
    /* para quando atinge um ponto com pouco erro, ou atinge max_iterações */
    /* retorna para o ponteiro passado como parâmetro se convergiu ou não */
    /* retorna para o ponteiro que não converge, se a derivara em x0 > 1 */
    int iteracoes = 1;
    double x1;
    * convergiu = 1;

    if(fabs(eval_Dg2(x0)) > 1.0){
        * convergiu = 0;
        return x0;
    }

    x1 = eval_g2(x0);
    while(fabs(x1-x0)>tol && iteracoes<max_iteracoes){
        iteracoes++;
        x0 = x1;
        x1 = eval_g2(x0);     
    }
    if(fabs(x0-x1) > tol){
        * convergiu = 0;
        return x0;
    }
    return x1;
}



double eval_g3(double x){
    return -sqrt(exp(x)) / sqrt(2.0);
}


double eval_Dg3(double x){
    return -exp(x/2.0) / (2.0 * sqrt(2.0));
}


double PF_g3(double x0, int * convergiu){
    /* para quando atinge um ponto com pouco erro, ou atinge max_iterações */
    /* retorna para o ponteiro passado como parâmetro se convergiu ou não */
    /* retorna para o ponteiro que não converge, se a derivara em x0 > 1 */
    int iteracoes = 1;
    double x1;
    * convergiu = 1;

    if(fabs(eval_Dg3(x0)) > 1.0){
        * convergiu = 0;
        return x0;
    }

    x1 = eval_g3(x0);
    while(fabs(x1-x0)>tol && iteracoes<max_iteracoes){
        iteracoes++;
        x0 = x1;
        x1 = eval_g3(x0);     
    }
    if(fabs(x0-x1) > tol){
        * convergiu = 0;
        return x0;
    }
    return x1;
}