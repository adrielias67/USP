#include <stdio.h>
#include <stdlib.h>



int *load_image_from_file(char *filename, int *w, int *h){
	int i, j, *V, lixo;

	char line[256]; 
	FILE *file;
	file = fopen(filename, "r");

	fscanf(file, "%[^\n]\n", line);
	fscanf(file, "%d%d", &*w, &*h);
	V = malloc(sizeof(int)* *w * *h);
	fscanf(file, " %d", &lixo);

	for(i=0; i<*h; i++){
		for(j=0; j<*w; j++){
			fscanf(file, "%d", &V[i**w+j]);
		}
	}
	fclose(file);
	return V;
}



void save_image_to_file(char *filename, int *I, int w, int h){
	int i, j;

	FILE *file;
	file = fopen(filename, "w");

	fprintf(file, "P2\n");
	fprintf(file, "%d %d\n", w, h);
	fprintf(file, "255\n");

	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			fprintf(file, "%d ", I[i*w+j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}



int *copia_imagem(int *A, int w, int h){
	int *B, i, j;
	B = malloc(sizeof(int)*w*h);
	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			B[i*w+j] = A[i*w+j];
		}
	}

	return  B;
}



int *invert_image(int *I, int w, int h){
	int i, j, *R;
	R = malloc(sizeof(int)*w*h);

	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			R[i*w+j] = 255 - I[i*w+j];
		}
	}

	return R;
}



int *binarize(int *I, int w, int h, int t){
	int i, j, *R;
	R = malloc(sizeof(int)*w*h);

	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			if (I[i*w+j] < t) R[i*w+j] = 0;
			else R[i*w+j] = 255;
		}
	}

	return R;
}



int *alarga_imagem(int *A, int w, int h, int expessura){
	int i, j, w2, h2;
	int *B;
	if(expessura!=0){			//Quando expessura == 0, a funcao devolve uma imagem com uma borda de zeros, para rotular componentes conexos
		w2 = w + (2*expessura);
		h2 = h + (2*expessura);
 		B = malloc(sizeof(int)*(w2)*(h2));

	 	for(i=0; i<h2; i++){
			for(j=0; j<w2; j++){

				if(i<expessura){
					if(j<expessura) B[i*w2+j] = A[0]; 
					else if(j>w+expessura-1) B[i*w2+j] = A[w - 1];
					else B[i*w2+j] = A[j - expessura];
				}

				else if(i>=h+expessura){
					if(j<expessura) B[i*w2+j] = A[w*(h - 1)];	
					else if(j>=w+expessura-1) B[i*w2+j] = A[w * h - 1];
					else B[i*w2+j] = A[w*(h-1) + j - expessura];
				}

				else{
					if(j<expessura) B[i*w2+j] = A[w * (i-expessura)];
					else if(j>w+expessura-1) B[i*w2+j] = A[w * (i-expessura+1) - 1];
					else B[i*w2+j] = A[(i-expessura)* w + j-expessura];
				}
			}
		}
	}
	else{  
		w2 = w + 2;
		h2 = h + 2;
 		B = malloc(sizeof(int)*(w2)*(h2));

 		for(i=0; i<h2; i++){
			for(j=0; j<w2; j++){
				if(i==0 || i==h2-1 || j==0 || j==w2-1){
					B[i*w2+j] = 0;
				}
				else{
					B[i*w2+j] = A[(i-1)*w + j-1];
				}
			}
		}
	}
	return B;
}

void troca(int *a, int *b){
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

int bubble_sort(int N[], int n){
	int i, j;
	for(i=0; i<n-1; i++){
		for (j=0; j<n-i-1; j++){
			if(N[j] > N[j+1]) troca(&N[j], &N[j+1]);
		}
	}
}

int *filter_image(int *I, int w, int h, int d, int tipo){
	int i, j, m, n, w2, h2;
	int *A, *FILTRO, *B;
	
	B = malloc(sizeof(int)*w*h);

	A = alarga_imagem(I, w, h, d/2);
	FILTRO = malloc(sizeof(int)*d*d);
	w2 = w + d -1;
	h2 = h + d -1;

	for(i=d/2; i<h; i++){
		for(j=d/2; j<w; j++){

			for(m=0; m<d; m++){
				for(n=0; n<d; n++){
					FILTRO[m*d+n] = A[(i-(d/2)+m)*w2 + j-(d/2)+n];
				}
			}
			bubble_sort(FILTRO,d*d);

			if(tipo==1) B[(i-d/2)*w + j-d/2] = FILTRO[0];
			if(tipo==2) B[(i-d/2)*w + j-d/2] = FILTRO[d*d/2];
			if(tipo==3) B[(i-d/2)*w + j-d/2] = FILTRO[d*d-1];
		}

	}
	return B;
}



int *calcula_contorno(int *I, int w, int h){
	int *R, *F, i, j;
	R = malloc(sizeof(int)*w*h);
	F = malloc(sizeof(int)*w*h);
	F = filter_image(I, w, h, 3, 1);

	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			R[i*w+j] = I[i*w+j] - F[i*w+j];
		}
	}

	free(F); F = NULL;
	return R;
}



int *label_components(int *I, int w, int h, int *ncc){
	int *A, *R, *FILA, *MEM, i, j, i2, j2, m, n, w2, h2, k=0, k_inicial, valor, valor_da_conexao=1;		//k: guarda a posicao atual na FILA / valor: guarda o valor atual da rotulacao / valor_da_conexao: variavel que sera usada para atribuir diferentes valores para diferentes conexoes
	*ncc = 0;

	w2 = w+2;
	h2 = h+2;

	A = alarga_imagem(I, w, h, 0);		//A: Vetor original, com uma borda de zeros
	R = malloc(sizeof(int)*w*h);		//R: Vetor de saida
	FILA = malloc(sizeof(int)*w*h);		//FILA: Vetor que empilha todos os componentes conexos de mesmo valor, guardando sua posicao na matriz
	MEM = malloc(sizeof(int)*w2*h2);	//MEM: Vetor memoria que guarda quais pontos ja foram vistos

	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			R[i*w+j] = 0;			//preenche R com zeros
			FILA[i*w+j] = -1;		//preenche FILA com -1
		}
	}

	for(i=0; i<h2; i++){
		for(j=0; j<w2; j++){
			MEM[i*w2+j] = 0;			//preenche MEM com zeros
		}
	}

	for(i=1; i<=h; i++){
		for(j=1; j<=w; j++){

			if(A[i*w2+j] != 0   &&   MEM[i*w2+j] == 0){			//procura pontos na imagem que ainda nao foram analisados
				FILA[k] = i*w2+j;								//cria uma fila, com a posicao na matriz do ponto achado sendo o primeiro elemento dessa fila  
				valor = A[i*w2+j];
				k_inicial = k;
				MEM[i*w2+j] = 1;
				k++;
			}

			while(FILA[k_inicial] != -1){

					for(m=0; m<3; m++){
						for(n=0; n<3; n++){

							if(A[FILA[k_inicial]-w2-1 + m*w2 + n] == valor   &&   MEM[FILA[k_inicial]-w2-1 + m*w2 + n] == 0){		//procura por pontos conexos e os coloca no final da fila
								FILA[k] = FILA[k_inicial]-w2-1 + m*w2 + n;
								MEM[FILA[k_inicial]-w2-1 + m*w2 + n] = 1;
								k++;
							}

						}
					}

				k_inicial++;			//percorre a fila, para achar os componentes conexos de todos os pontos da fila, ate nao restar mais nenhum

			}

			for(k=0; k<k_inicial; k++){
				R[FILA[k]-w2-1 -2*((FILA[k]/w2)-1)] = valor_da_conexao;		//preenche os pontos encontrados em R com o mesmo valor, ajustando a diferenca de largura e altura entre A e R
			}

			k = 0;
			for(i2=0; i2<h; i2++){
				for(j2=0; j2<w; j2++){
					FILA[i2*w+j2] = -1;		//preenche FILA com -1
				}
			}

			if(k_inicial>0){
				valor_da_conexao++;
				*ncc = *ncc +1;
			}
			k_inicial = 0;

		}
	}

	if(*ncc<=127){
		for(i=0; i<h; i++){
			for(j=0; j<w; j++){
				R[i*w+j] = R[i*w+j] * (int)(255 / *ncc);
			}
		}
	}

	return R;
}







int main(){
	int largura, altura, i, j, stop=0;
	int limiar, tipo_filtro, tamanho_filtro, primeira_imagem=1, numero_de_componentes;
	int *I, *R, *TEMP;
	char opcao;

	char entrada[256], saida[256];

	
	while(!stop){
		printf("----------------------------------------------\n");
		printf(" Escolha uma opcao\n");
		printf(" Q. Quit\n");
 		printf(" L. Ler um arquivo\n");
	 	printf(" S. Salvar imagem em arquivo\n");
 		printf(" M. Manter entrada anterior\n");
	 	printf("\n");
		printf(" B. Binarizar a imagem\n");
	 	printf(" C. Contorno da imagem\n");
 		printf(" I. Inverter a imagem\n");
	 	printf(" F. Filtrar a imagem\n");
 		printf(" R. Rotular os componentes conexos\n");
 	
	 	printf("==>");
		scanf(" %c", &opcao);
	 	printf("\n");
		

	 	if(opcao == 'q') stop = 1;
	 	

		if(opcao == 'l'){
			printf("==> Digite o nome do arquivo de entrada: "); 
			scanf("%s", entrada);
			I = load_image_from_file(entrada, &largura, &altura);
			printf("** Tamanho da imagem: %d x %d\n\n", largura, altura);
		}


		if(opcao == 's'){
			printf("==> Digite o nome do arquivo de saída: ");
			scanf("%s", saida);
			if(primeira_imagem==0){
			save_image_to_file(saida, R, largura, altura);
			}
			else{
			save_image_to_file(saida, I, largura, altura);
			}
			printf("**Imagem foi gravada no arquivo %s\n\n", saida);

		}


		if(opcao == 'm'){
			I = copia_imagem(TEMP, largura, altura);
			free(R); R = NULL;
			primeira_imagem = 1;
			printf("**Imagem foi mantida\n\n");
		}


		if(opcao == 'b'){
			printf("==> Digite o limiar: ");
			scanf("%d", &limiar);
			R = (binarize)(I, largura, altura, limiar);
			printf("**Imagem foi binarizada\n\n");
			primeira_imagem = 0;
		}


		if(opcao == 'c'){
			R = calcula_contorno(I, largura, altura);
			printf("**Contorno calculado\n\n");
			primeira_imagem = 0;
		}


		if(opcao == 'i'){
			R = invert_image(I, largura, altura);
			primeira_imagem = 0;
			printf("**Imagem foi invertida\n\n");
		}


		if(opcao == 'f'){
			printf("==> Digite o tipo do filtro: ");
			scanf("%d", &tipo_filtro);
			printf("==> Digite o tamanho do filtro: ");
			scanf("%d", &tamanho_filtro);
			R = filter_image(I, largura, altura, tamanho_filtro, tipo_filtro);
			printf("**Imagem foi filtrada\n\n");
			primeira_imagem = 0;
		}


		if(opcao == 'r'){
			R = label_components(I, largura, altura, &numero_de_componentes);
			printf("** Imagem foi rotulada\n");
 			printf("** Número de componentes conexos: %d\n\n", numero_de_componentes);
 			primeira_imagem = 0;
		}



		if(opcao != 's'){ 					//Salva a imagem I temporariamente, para poder usar a opcao de manter
			free(TEMP); TEMP = NULL;
			TEMP = malloc(sizeof(int)*largura*altura);
			TEMP = copia_imagem(I, largura, altura);
		}
		if(primeira_imagem==0){				//Copia R para I, para fazer a proxima alteracao na imagem
			I = copia_imagem(R, largura, altura);
		}

	}

	free(I); I = NULL;
	free(R); R = NULL;

}