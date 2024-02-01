#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<complex.h>

typedef double complex dc;
#define tol exp(-20)        /* tolerância para comparação de dois números de ponto flutuante*/
#define n_max_raizes 1000     /* número máximo de raizes tolerado para a função implementada */
#define max_iteracoes 40    /* número máximo de iterações tolerado para o método de Newton */



dc evalf(dc x);                         /* calcula a função x^5 - 1 em x */
dc evalDf(dc x);                        /* calcula a derivada da função x^5 - 1 em x */
dc newton(dc xk0, int * convergiu);     /* aplica o método de Newton em x0. */
void newton_basis(int l[], int u[], int p[]); /* calcula as bacias de convergência */



int main(){
    int l[2], u[2], p[2];
    printf("Digite lx, ux, ly, py, px, py: ");
    scanf("%d%d%d%d%d%d", &l[1], &u[1], &l[0], &u[0], &p[0], &p[1]);
    printf("\n");
    newton_basis(l, u, p);
}



dc evalf(dc x){
    return x*x*x*x*x - 1.0;
}



dc evalDf(dc x){
    return 5.0 * x*x*x*x;
}



dc newton(dc xk0, int * convergiu){
    /* para quando atinge max_iterações, ou se a derivada em x0 é igual a 0 */
    /* retorna para o ponteiro passado como parâmetro se convergiu ou não */
    int iteracoes = 1;
    dc xk1;
    * convergiu = 1;

    if(cabs(evalDf(xk0))<tol){
        * convergiu = 0;
        return xk0;
    }
    xk1 = xk0 - (evalf(xk0) / evalDf(xk0));
    while(cabs(xk1-xk0)>tol && iteracoes<max_iteracoes && cabs(evalDf(xk0))!=0.0){
        iteracoes++;
        xk0 = xk1;
        xk1 = xk0 - (evalf(xk0) / evalDf(xk0));
    }
    if(cabs(xk1-xk0) > tol){
        * convergiu = 0;
        return xk0;
    }
    return xk1;
}



void newton_basis(int l[], int u[], int p[]){
    /* dado o intervalo [l, u] e a quantidade de pixels desejada, calcula as bacias */
    /* guarda as informações em "output.txt" */
    FILE * output;
    output = fopen("output.txt", "w");

    double passox = (double)abs(u[0]-l[0]) / (p[0]-1);
    double passoy = (double)abs(u[1]-l[1]) / (p[1]-1);
    int i, j, k, convergiu, n_max_raizes_preenchidas=0;
    dc ponto, raiz, raizes[n_max_raizes];


    for(i=0; i<p[0]; i++){
        for(j=0; j<p[1]; j++){
            ponto = (l[0]+i*passox) + (l[1]+j*passoy)*I;
            raiz = newton(ponto, & convergiu);

            if(convergiu==1){
                for(k=0; k<n_max_raizes_preenchidas; k++){
                    if(cabs(raizes[k]-raiz) <= 2*tol) break;
                }
                if(k == n_max_raizes_preenchidas){
                    raizes[k] = raiz;
                    n_max_raizes_preenchidas++;
                }
                fprintf(output, "%.2f %+.2f %d\n", creal(ponto), cimag(ponto), k+2);
            }
            else fprintf(output, "%.2f %+.2f 1\n", creal(ponto), cimag(ponto));
        }
        fprintf(output, "\n");
    }
    
    fclose(output);
}