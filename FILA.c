#include "FILA.h"

int *q;
int inicio, fim;

/* Cria uma fila vazia */
void FILAcria(int maxN){
	q = (int*) malloc(maxN*sizeof(int));
	inicio = 0;
	fim = 0;
}

/* Verifica se a fila esta vazia */
int FILAvazia(){
	return inicio == fim;
}
 /* Insere item na fila */
void FILAinsere (int item) {
	q[fim++] = item;
}

/* Recupera item da fila */
int FILAremove() {
	return q[inicio++];
}

/* Destroi fila */
void FILAdestroi(){
	free(q);
}
