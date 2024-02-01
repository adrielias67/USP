#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"


#define MAX 256
 

typedef struct{
	char *p;	/* palavra */
	int c; 		/* quantidade de caracteres da palavra */
	int indice;	/* índice que será usado no backtrack */
}palavra;



void leTabuleiro(int **T, int m, int n){
	int i, j, aux;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			scanf("%d", &aux);
			T[i][j] = aux;
		}
	}
}



void zeraMatriz(int **T, int m, int n){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			T[i][j] = 0;
		}
	}
}



void lePalavras(palavra P[], int n){
	/* coloca as palavras lidas e seus tamanhos num vetor */
	int i;
	for(i=0; i<n; i++){
		scanf("%s", P[i].p);
		P[i].c = strlen(P[i].p);
		P[i].indice = -1;	/*inicializa para ser usado no backtrack */
	}
}



void imprimeTabuleiro(int **T, int m, int n){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			if(T[i][j]==-1) printf("* ");
			else printf("%c ", (char)T[i][j]);
		}
		printf("\n");
	}
}



typedef struct{
	int i;
	int j;
	int l;
	int orientacao;	/* 0 = horizontal, 1 = vertical */
	int preenchida;	/* se a posição está preenchida no tabuleiro */
} coordenada;		/* usado em void casasTabuleiro() */

void casasTabuleiro(int **T, int m, int n, coordenada C[]){
	/* dado um tabuerio, retorna um vetor C com todas as casas disponíveis para as palavras */
	/* por exemplo: algum elemento de C com (i,j) = (1,2), l = 3 e orientacao = 0, significa que há uma casa horizontal para uma palavra com 3 caracteres em T[1][2] */
	/* o vetor C termina com uma casa de tamanho (l) = -1, para sinalizar o fim dele */
	int i=0, j=0, k=0, auxi, auxj;
	pilha *pi = cria();
	pilha *pj = cria();

	/* horizontal */
	for(i=0; i<m; i++){
    	for(j=0; j<n; j++){

    		if(pilhaVazia(pj) && T[i][j]==0){
    			empilha (pj, j);
    		}
    		if(T[i][j]==-1 && !pilhaVazia(pj)){	/*caso encontre -1 */
    			auxj = desempilha(pj);
    			if(j-auxj>1){
    				C[k].i = i;
          			C[k].j = auxj;
         		 	C[k].l = j-auxj;
         		 	C[k].orientacao = 0;
         			C[k].preenchida = 0;  /* inicializa para a verificação em tabuleiroCheio() */
        			k++;
    			}
    		}
    		if(j==n-1 && !pilhaVazia(pj)){	/*caso esteja na última coluna */
    			auxj = desempilha(pj);
    			if(j-auxj>0){
    				C[k].i = i;
          			C[k].j = auxj;
         		 	C[k].l = j-auxj+1;
         		 	C[k].orientacao = 0;
         			C[k].preenchida = 0;  /* inicializa para a verificação em tabuleiroCheio() */
        			k++;
    			}
    		}

    	}
	}



	/* vertical */
	for(j=0; j<n; j++){
    	for(i=0; i<m; i++){
    		
    		if(pilhaVazia(pi) && T[i][j]==0){
    			empilha (pi, i);
    		}
    		if(T[i][j]==-1 && !pilhaVazia(pi)){	/*caso encontre -1 */
    			auxi = desempilha(pi);
    			if(i-auxi>1){
    				C[k].i = auxi;
          			C[k].j = j;
         		 	C[k].l = i-auxi;
         		 	C[k].orientacao = 1;
         			C[k].preenchida = 0;  /* inicializa para a verificação em tabuleiroCheio() */
        			k++;
    			}
    		}
    		if(i==m-1 && !pilhaVazia(pi)){	/*caso esteja na última coluna */
    			auxi = desempilha(pi);
    			if(i-auxi>0){
    				C[k].i = auxi;
          			C[k].j = j;
         		 	C[k].l = i-auxi+1;
         		 	C[k].orientacao = 1;
         			C[k].preenchida = 0;  /* inicializa para a verificação em tabuleiroCheio() */
        			k++;
    			}
    		}

    	}
	}

	C[k].l = -1;

}



int tabuleiroCheio(coordenada C[]){
	/* dado o vetor de casas de um tabuleiro, verifica se ele está cheio, com todas as casas de palavras preenchidas */
	int i=0;
	while(C[i].l!=-1){
		if(C[i].preenchida==0) return 0;
		i++;
	}
	return 1;
}




int colocaPalavraH(char * p, int **T, int cordi, int cordj, int l, int **Tmem){
	/* dada uma palavra, um tabuleiro, as coordenadas dela no tabuleiro, e sua largura, coloca ela no tabuleiro NA HORIZINTAL, e na memória do tabuleiro */
	/* se for possível colocar, coloca e retorna 1, caso contrário, não coloca e retorna 0 */
	int i;
	for(i=0; i<l; i++){
		if(T[cordi][cordj+i] != p[i] && T[cordi][cordj+i] != 0){
			return 0;	/*se for impossível, para aqui */
		}
	}
	for(i=0; i<l; i++){
		T[cordi][cordj+i] = (int)p[i];
		Tmem[cordi][cordj+i] += 1;
	}
	return 1;
}

int colocaPalavraV(char * p, int **T, int cordi, int cordj, int l, int **Tmem){
	/* dada uma palavra, um tabuleiro, as coordenadas dela no tabuleiro, e sua largura, coloca ela no tabuleiro NA VERTICAL, e na memória do tabuleiro */
	/* se for possível colocar, coloca e retorna 1, caso contrário, não colca e retorna 0 */
	int i;
	for(i=0; i<l; i++){
		if(T[cordi+i][cordj] != p[i] && T[cordi+i][cordj] != 0){
			return 0;	/*se for impossível, para aqui */
		}
	}
	for(i=0; i<l; i++){
		T[cordi+i][cordj] = (int)p[i];
		Tmem[cordi+i][cordj] += 1;
	}
	return 1;
}



void retiraPalavra(int **T, int cordi, int cordj, int l, int orientacao, int **Tmem){
	/* dado um tablueiro, as coordenadas e largura de uma palavra, e sua orientação, tira-a do tabuleiro respeitando as cruzadas com ela, e tira da memória */
	int i;
	/* horizontal */
	if(orientacao==0){
		for(i=0; i<l; i++){
			if(Tmem[cordi][cordj+i]==1){
				T[cordi][cordj+i] = 0;	/*só tira o caractere se ele pertencer a apenas uma palavra naquela posição */
			}
		Tmem[cordi][cordj+i]--;
		}
	}
	/* vertical */
	else{
		for(i=0; i<l; i++){
			if(Tmem[cordi+i][cordj]==1){
				T[cordi+i][cordj] = 0;	/*só tira o caractere se ele pertencer a apenas uma palavra naquela posição */
			}
		Tmem[cordi+i][cordj]--;
		}
	}
}







void principal(int m, int n, int instancia){
	int nPalavras, i=0, j, naoTemPalavra=0, foiColocada=0;
	pilha *pilhavra = cria();	/* cria uma pilha para as palavras */

	coordenada *C;
	C = malloc(sizeof(coordenada)*(m*n));	/* cada tabuleiro pode ter no máximo (arredondado) essa quantidade de casas */

	int **T;	/* tabuleiro  */
	T = malloc(sizeof(int*)*m);
	for(i=0; i<m; i++){
		T[i] = malloc(sizeof(int)*n);
	}
	int **Tmem;	/* memória do tabuleiro (usada para retirar uma palavra sem alterar outras que estejam cruzadas com ela) */
	Tmem = malloc(sizeof(int*	)*m);
	for(i=0; i<m; i++){
		Tmem[i] = malloc(sizeof(int)*n);
	}
	zeraMatriz(Tmem, m, n);
	leTabuleiro(T, m, n);
	casasTabuleiro(T, m, n, C);

	scanf("%d", &nPalavras);
	palavra P[nPalavras];
	for(i=0; i<nPalavras; i++){
		P[i].p = malloc(sizeof(char)*MAX);
	}
	lePalavras(P, nPalavras);
	printf("\n");



	/* BACKTRACK */
	/* faz o backtrack buscando palavras do tamanho das casas, e empilhando as já colocadas */
	i = 0;	/*i será usado para referências à pilha de palavras (P) */
	j = 0;	/*j será usado para fazer referências ao vetor das casas (C) */
	while(C[j].l!=-1){
		/* acha uma palavra para a casa */
		while(C[j].l != P[i].c || P[i].indice!=-1){
			if(i==nPalavras-1){
				naoTemPalavra = 1;	/* chegou ao fim do P[] */
				i = 0;
				break;
			}
			i++;
		}

		if(naoTemPalavra==0){
			/* horizontal */
			if(C[j].orientacao==0){
				if(colocaPalavraH(P[i].p, T, C[j].i, C[j].j, C[j].l, Tmem)){	/* coloca palavra na horizontal */
					C[j].preenchida = 1;
					P[i].indice = j;	/* o indice guarda o índice j da casa (C[j]) em que cada palavra é colocada para buscar outra possibilidade durante o backtrack */
					empilha(pilhavra, i);
					i = 0;
					foiColocada = 1;
				}
			}

			/* vertical */
			else{
				if(colocaPalavraV(P[i].p, T, C[j].i, C[j].j, C[j].l, Tmem)){	/* coloca palavra na vertical */
					C[j].preenchida = 1;
					P[i].indice = j;	/* o indice guarda o índice j da casa (C[j]) em que cada palavra é colocada para buscar outra possibilidade durante o backtrack */
					empilha(pilhavra, i);
					i = 0;
					foiColocada = 1;
				}
			}
		}
		
		if(tabuleiroCheio(C)){
			/* Sucesso */
			printf("\n");
			printf("Instancia %d\n", instancia);
			imprimeTabuleiro(T, m, n);
			break;
		}

		if(naoTemPalavra){	/* caso não tenha mais nenhuma palavra que caiba na casa */
			if(!pilhaVazia(pilhavra)){
				do{
					i = desempilha(pilhavra);	
					j = P[i].indice;
					P[i].indice = -1;
					C[j].preenchida = 0;
					retiraPalavra(T, C[j].i, C[j].j, C[j].l, C[j].orientacao, Tmem);
				}while(i==nPalavras-1);
				j--;	/* -- porque vai fazer j++ no final do while */
				i++;	/* busca outra palavra para a posição */
			}
			else break;
		}

		if((i==nPalavras-1) && !naoTemPalavra){	/* caso esteja na última palavra */
			if(!foiColocada){
				i = desempilha(pilhavra);	
				j = P[i].indice;
				P[i].indice = -1;
				C[j].preenchida = 0;
				retiraPalavra(T, C[j].i, C[j].j, C[j].l, C[j].orientacao, Tmem);
				j--;	/* -- porque vai fazer j++ no final do while */
				i++;	/* busca outra palavra para a posição */
			}
		}

		else if(!foiColocada && !naoTemPalavra){	/* caso ache uma palavra para a casa, mas não possa cruzar com uma palavra que já está colocada */
			j--;	/* -- porque vai fazer j++ no final do while */
			if(i!=nPalavras-1) i++;	/* busca outra palavra para a posição */
		}

		foiColocada = 0;
		naoTemPalavra = 0;
		j++;

	}


	/* Falhou */
	if(!tabuleiroCheio(C)){
		printf("Instancia %d\n", instancia);
		printf("nao ha solucao\n\n");
	}


	/* Frees */
	for(i=0; i<m; i++){
		free(T[i]);
	}
	free(T);
	for(i=0; i<m; i++){
		free(Tmem[i]);
	}
	free(Tmem);
	for(i=0; i<nPalavras; i++){
		free (P[i].p);
	}

}



int main(){
	int m, n, i=1;
	scanf("%d %d", &m, &n);
	while(m!=0){
 		principal(m, n, i);
 		scanf("%d %d", &m, &n);
 		i++;
 	}
 	return 0;
}