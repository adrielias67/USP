typedef struct cel {
  char * chave;
  int* linhas;
  int nlinhas;
  int* quantidade;
  struct cel * esq;
  struct cel * dir; 
} no;

no * minimo (no * raiz);
void inordem (no *raiz);

