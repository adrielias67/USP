#include <stdio.h>
#include <stdlib.h>


typedef long long int numero;


numero proximo(numero x, int *p){
	/* A função retorna o próximo número, e o numero de passos feitos */

	if(x%2==1){
		*p = *p + 2;
		return x / 2 * 3 + 2;
	}
	
	/*else*/
	*p = *p + 1;
	return x / 2;
}


int main(){
	int j, passo=0, topo, dobro;
	long int i, f;

	numero num;			
	numero *MEM;				// MEM guarda os passos de cada número, onde MEM[i] = número de passos de i até 1.					

	printf("[i,f]: ");
	scanf("%ld%ld", &i, &f);

	topo = f + 1;						
	MEM = malloc(topo * sizeof(numero));				
	MEM[1] = 0;
	for(j=2; j<=topo; j++){
		MEM[j] = -1;
	}

	for(j=i; j<=f; j++){

		if(MEM[j] == -1){
			num = j;

			while(num != 1){

				num = proximo(num, &passo);

				if(num <= f && MEM[num] != -1){		// É necessário verificar se num <= f para não acessar um espaço de memória inexistente.
					passo += MEM[num];
					break;
				}

			}

			MEM[j] = passo;			
		
			dobro = j * 2;
			while(dobro <= topo){
				MEM[dobro] = ++passo;
				dobro *= 2;
			}

			passo = 0;

		}

		printf("%d - %lld\n", j, MEM[j]);

	}

	free(MEM);
	MEM = NULL;

	return 0;

}