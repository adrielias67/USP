#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimbolos.h"



/* Abaixo encontramos as palavras mais frequentes com pelo menos 
   "qtdLetras" letras */


int main() {
  int qtdLetras=2, linha=1;

  no * p = NULL;
  
  char palavra[100], CharAux, count=0;


  while (scanf("%c", &CharAux) > 0){
    if( (CharAux>='A' && CharAux<='Z') || (CharAux>='a' && CharAux<='z') ){
      palavra[count] = CharAux;
      count++;
    }
    else{
      palavra[count] = '\0';
      if (count >= qtdLetras){   
        p = insercao(p, palavra, linha);
      }
      if (CharAux == '\n')
        linha ++;
      count = 0;
    }
  }

  /* Neste ponto temos nossa tabela de símbolos criada e com as
     frequencias no texto, por linha */

  inordem(p);

  free(p);

  return 0;
}

