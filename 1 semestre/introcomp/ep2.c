#include <stdio.h>

#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 /* zona de alerta */
#define DELTA_ALARME 60
#define EPS_COS 0.000001 /* precisão para cálculo do cosseno */
#define EPS 0.01 /* precisão para valores envolvendo metros */




/* operações */

double cosseno(double theta, double epsilon){
	int i = 0, sinal = 1;
	double S = 0, numerador = 1.0, denominador = 1.0;
	do{
		S = S + sinal * (numerador / denominador);
		numerador = numerador * theta * theta;
		denominador = denominador * (i+1) * (i+2);
		i = i + 2;
		sinal = sinal * -1;
	}while((numerador / denominador) >= epsilon);
	return S;
}


double rad(double angulo){
	return (angulo * PI) / 180;
}


double quadrado(double n){
	return n * n;
}


double mod(double n){
	if(n > 0) return n;
	else return -n;
}


int iguais(double x, double y) {
	if(x-y < EPS && y-x < EPS)
		return 1;
	else
		return 0;
}


int sinal(double n){
	if(n>0) return 1;
	else if(n<0) return -1;
	else return 0;
}


double raiz(double x, double epsilon){
	double ant, pos = x; /* ant = rn, pos = rn+1 */
	if(iguais(x, 0)) return 0;
	if(x<0) return -1; /* retorna -1 para números negativos, o que será utilizado na função intercepta (linha 193) */
	do{
		ant = pos;
		pos = (ant + (x / ant)) / 2;
	}while(mod(ant - pos) > epsilon);
	return pos;
}




/* funções */

double distancia(double H, double theta){
	return H * cosseno(theta, EPS_COS);
}


int localiza( double xi, double yi, double div, double xj, double yj, double djv, double xk, double yk, double dkv, double *xv, double *yv){
	/* definir as antenas */
	double x1, x2, x3, y1, y2, y3, d1v, d2v, d3v; /* compara xi, xj, xk para ver se as antenas são colineares. a antena 1 terá x diferente das outras.*/
	if(iguais(xi, xj)){
		if(iguais(xi, xk)) return 0;
		else{
			x1 = xk; y1 = yk; d1v = dkv;
			x2 = xi; y2 = yi; d2v = div;
			x3 = xj; y3 = yj; d3v = djv;
		}
	}
	else if(iguais(xi, xk)){
		x1 = xj; y1 = yj; d1v = djv;
		x2 = xi; y2 = yi; d2v = div;
		x3 = xk; y3 = yk; d3v = dkv;
	}
	else{
		x1 = xi; y1 = yi; d1v = div;
		x2 = xj; y2 = yj; d2v = djv;
		x3 = xk; y3 = yk; d3v = dkv;
	}


	/* resolver o sistema */
	double p12, q12, p13, q13; /* calcular pij, qij, pik, qik */
	p12 = (quadrado(x1) - quadrado(x2) + quadrado(y1) - quadrado(y2) - quadrado(d1v) + quadrado(d2v)) / (2.0 * (x1 - x2));
	q12 = (y2 - y1) / (x1 - x2);
	p13 = (quadrado(x1) - quadrado(x3) + quadrado(y1) - quadrado(y3) - quadrado(d1v) + quadrado(d3v)) / (2.0 * (x1 - x3));
	q13 = (y3 - y1) / (x1 - x3);

	if(q12 != 0){
		*xv = (p13 - q13 * (p12 / q12)) / (1.0 - (q13 / q12));
		*yv = (*xv - p12) / q12;
	}
	else{
		*xv = (p12 - q12 * (p13 / q13)) / (1.0 - (q12 / q13));
		*yv = (*xv - p13) / q13;
	}
	return 1;
}


double velocidade(double x0, double y0, double x1, double y1, double deltaT){
	return raiz(quadrado(x1 - x0) + quadrado(y1 - y0), EPS) / deltaT;
}


int sinal_relativo(double x0, double x1){
	return sinal(x1 - x0);
}


int intercepta(double x0, double y0, double x1, double y1, double *x, double *y){
	double m, delta, a, b, c, x_um, x_dois, y_um, y_dois;
	double s01, s1p, intercepta; /* sinais relativos dos pontos 0 a 1, e 1 à intersecção. 
								     Podemos dizer que o carro está se distanciando da AP quando os sinais relativos são inversos */

	if(!iguais(x0, x1)){
		s01 = sinal_relativo(x0, x1);
		m = (y1 - y0) / (x1 - x0);
		a = quadrado(m) + 1;
		b = 2.0 * m * (-m*x0 + y0);
		c = quadrado(-m*x0 + y0) - quadrado(RAIO_AP);
		delta = quadrado(b) - (4.0 * a * c);
		if (delta < 0) return 0; /* é mais facil dar return aqui ao invés de mudar a variável intercepta, pois assim,
									não é necessário verificar essa condição em todos os outros casos. */

		/* caso m = 0 */
		if (iguais(m, 0)){
			x_um = raiz(quadrado(RAIO_AP) - quadrado(y0), EPS);
			x_dois = -x_um;
			*y = y0;
			if (mod(x_um - x1) < mod(x_dois - x1)){
				*x = x_um;
				s1p = sinal_relativo(x1, *x);
				if (s01 == s1p) intercepta = 1;
				else intercepta = 0;
			}
			else{
				*x = x_dois;
				s1p = sinal_relativo(x1, *x);
				if (s01 == s1p) intercepta = 1;
				else intercepta = 0;
			}
		}


		/* caso m != 0 */
		else{
			x_um = (-b + raiz(delta, EPS)) / (2.0 * a);
			x_dois = (-b - raiz(delta, EPS)) / (2.0 * a);
			if (mod(x_um - x1) < mod(x_dois - x1)){
				*x = x_um;
				*y = raiz(quadrado(RAIO_AP) - quadrado(x_um), EPS);
				s1p = sinal_relativo(x1, *x);
				if (s01 == s1p) intercepta = 1;
				else intercepta = 0;
			}
			else{
				*x = x_dois;
				*y = raiz(quadrado(RAIO_AP) - quadrado(x_dois), EPS);
				s1p = sinal_relativo(x1, *x);
				if (s01 == s1p) intercepta = 1;
				else intercepta = 0;
			}
		}
	}


	/* caso x0 = x1 */
	else{
		s01 = sinal_relativo(y0, y1);
		*x = x0;
		y_um = raiz(quadrado(RAIO_AP) - quadrado(x0), EPS);
		if (y_um == -1) return 0;
		y_dois = -y_um;
		if(mod(y_um - y1) < (mod( - y1))){
			*y = y_um;
			s1p = sinal_relativo(y1, *y);
			if (s01 == s1p) intercepta = 1;
			else intercepta = 0;
		}
		else{
			*y = y_dois;
			s1p = sinal_relativo(y1, *y);
			if (s01 == s1p) intercepta = 1;
			else intercepta = 0;
		}
	}

	return intercepta;
}








int main(){
	double xi, yi, Hi, angulo_i, xj, yj, Hj, angulo_j, xk, yk, Hk, angulo_k;
	double di, dj, dk, xv1, yv1, xv2, yv2, intervaloT, velocidade_v, dist_origem, dist_AP, xv_intercepta, yv_intercepta, tempo_interseccao;
	int id_v, id_i, id_j, id_k;

	FILE *arq_entrada;
	char filename[256];
	int num_casos, i;

	printf("============================\n");
	printf("||Sistema de Monitoramento||\n");
	printf("============================\n\n");

	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", filename);
	arq_entrada = fopen(filename, "r");

	fscanf(arq_entrada, "%d", &num_casos);
	printf("Numero de casos a serem analisados: %d\n", num_casos);
	
	for(i=0; i<num_casos; i++){
		fscanf(arq_entrada, "%d", &id_v);
		printf("\n\n\n\nIDENTIFICACAO: veiculo %d\n", id_v);
		printf("-------------------------\n\n");

		fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_i, &xi, &yi, &Hi, &angulo_i);
		fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_j, &xj, &yj, &Hj, &angulo_j);
		fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_k, &xk, &yk, &Hk, &angulo_k);
		fscanf(arq_entrada, "%lf", &intervaloT);
		di = distancia(Hi, rad(angulo_i));
		dj = distancia(Hj, rad(angulo_j));
		dk = distancia(Hk, rad(angulo_k));
		printf("Antenas na posicao previa\n");
		printf("id\t | posicao\t\t | H (m)\t | theta (graus)\t | distancia (m)\n");
		printf("%d\t | (%.2lf , %.2lf)\t | %.2lf\t | %.2lf\t\t\t | %.2lf\n", id_i, xi, yi, Hi, angulo_i, di);
		printf("%d\t | (%.2lf , %.2lf)\t | %.2lf\t | %.2lf\t\t\t | %.2lf\n", id_j, xj, yj, Hj, angulo_j, dj);
		printf("%d\t | (%.2lf , %.2lf)\t | %.2lf\t | %.2lf\t\t\t | %.2lf\n", id_k, xk, yk, Hk, angulo_k, dk);

		if (!localiza(xi, yi, di, xj, yj, dj, xk, yk, dk, &xv1, &yv1)){
			printf("\nNao foi possivel calcular a localizacao inicial do veiculo %d\n", id_v);
			printf("\nNao foi possivel determinar a situacao do veiculo %d\n", id_v);
		}
		else{
			printf("\nlocalizacao previa: (%.2lf , %.2lf)\n", xv1, yv1);
			printf("\nIntervalo de tempo: %.2lf segundos\n", intervaloT);
		}

		if(localiza(xi, yi, di, xj, yj, dj, xk, yk, dk, &xv1, &yv1)){
			fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_i, &xi, &yi, &Hi, &angulo_i);
			fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_j, &xj, &yj, &Hj, &angulo_j);
			fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_k, &xk, &yk, &Hk, &angulo_k);
			di = distancia(Hi, rad(angulo_i));
			dj = distancia(Hj, rad(angulo_j));
			dk = distancia(Hk, rad(angulo_k));
			printf("\nAntenas na posicao atual\n");
	 		printf("id\t | posicao\t\t | H (m)\t | theta (graus)\t | distancia (m)\n");
			printf("%d\t | (%.2lf , %.2lf)\t | %.2lf\t | %.2lf\t\t\t | %.2lf\n", id_i, xi, yi, Hi, angulo_i, di);
			printf("%d\t | (%.2lf , %.2lf)\t | %.2lf\t | %.2lf\t\t\t | %.2lf\n", id_j, xj, yj, Hj, angulo_j, dj);
			printf("%d\t | (%.2lf , %.2lf)\t | %.2lf\t | %.2lf\t\t\t | %.2lf\n", id_k, xk, yk, Hk, angulo_k, dk);

			if(!localiza(xi, yi, di, xj, yj, dj, xk, yk, dk, &xv2, &yv2)){
				printf("\nNao foi possivel calcular a localizacao atual do veiculo %d\n", id_v);
				printf("\nNao foi possivel determinar a situacao do veiculo %d\n", id_v);
			}

			else{
				printf("\nlocalizacao atual: (%.2lf , %.2lf)\n", xv2, yv2);

				printf("\nDistancia percorrida: %.2lf \n", velocidade(xv1, yv1, xv2, yv2, 1)); /* usando o intervalo de tempo como 1, podemos calcular a distãncia atraves da função velocidade */
				velocidade_v = velocidade(xv1, yv1, xv2, yv2, intervaloT);
				printf("Velocidade: %.2lf m/s\n", velocidade_v);

				dist_origem = raiz(quadrado(xv2) + quadrado(yv2), EPS);
				printf("\nDistancia da origem: %.2lf\n", dist_origem);
				if(iguais(velocidade_v, 0)){
					printf("Veiculo estacionado");
					if(dist_origem > RAIO_ZA) printf(" FORA da zona de alerta\n");
					else if(dist_origem > RAIO_AP) printf(" na ZONA DE ALERTA\n");
					else printf(" na AP\n");
				}
				else{
					printf("Veiculo em movimento");
					if(dist_origem > RAIO_ZA) printf(" FORA da zona de alerta\n");
					else if(dist_origem > RAIO_AP) printf(" na ZONA DE ALERTA\n");
					else printf("na AP\n");
				}

				if(!intercepta(xv1, yv1, xv2, yv2, &xv_intercepta, &yv_intercepta)) {
					if ((dist_origem <= RAIO_ZA) && (!iguais(velocidade_v, 0.0)))printf("\nTrajetoria NAO INTERCEPTARA AP\n");
					if(dist_origem <= RAIO_AP){
						printf("\n*************************************\n");
						printf("  ALARME, ALARME, ALARME, ALARME !!\n");
						printf ("        Veiculo esta na AP !\n");
						printf("*************************************\n");
					}
				}
				else{
					if(dist_origem <= RAIO_AP){
						printf("\n*************************************\n");
						printf("  ALARME, ALARME, ALARME, ALARME !!\n");
						printf ("        Veiculo esta na AP !\n");
						printf("*************************************\n");
					}
					if((!iguais(velocidade_v, 0)) && (dist_origem <= RAIO_ZA)){
						printf("\nTrajetoria INTERCEPTARA AP\n");
						dist_AP = velocidade(xv2, yv2, xv_intercepta, yv_intercepta, 1);
						printf("Distancia atual a AP eh de %.2lf metros\n", dist_AP);
						tempo_interseccao = dist_AP / velocidade_v;
						printf("Interseccao ocorrera em %.2lf segundos\n", tempo_interseccao);
						printf("Na coordenada (%.2lf , %.2lf)\n\n", xv_intercepta, yv_intercepta);
						if(tempo_interseccao <= DELTA_ALARME){
							printf("*************************************\n");
							printf("  ALARME, ALARME, ALARME, ALARME !!\n");
							if(dist_origem <= RAIO_AP) printf ("        Veiculo esta na AP !\n");
							else printf("         Invasao iminente !\n");
							printf("*************************************\n");
						}
					}	
				}
			}
		}
		else{
			fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_i, &xi, &yi, &Hi, &angulo_i); /* escaneia os dados mesmo não os utilizando para o apontador andar 15 posições, para o próximo carro */
			fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_j, &xj, &yj, &Hj, &angulo_j);
			fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id_k, &xk, &yk, &Hk, &angulo_k);
		}
	}
	fclose(arq_entrada);
}