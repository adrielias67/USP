#include <stdio.h>


int ehprimo(int x){
	int i;

	if(x == 1) return 0;
	for(i=2; i*i<=x; i++){
		if(x%i == 0) return 0;
	}
	return 1;
}


int proxPrimo(int x){
	int i, achou_prox_primo=0;

	i = x;
	while(achou_prox_primo==0){
		i ++;
		achou_prox_primo = ehprimo(i);
	}
	return i;
}


int main(){
	int modo, num, i;
	scanf("%d%d", &modo, &num);

	if(modo==0){
		printf("%d\n", proxPrimo(num));
	}

	else{
		for(i=2; i*i<=num; i=proxPrimo(i)){
			if(num%i == 0 && ehprimo(num/i)){
				printf("%d %d\n", i, num/i);
			}
		}
	}

	return 0;
}