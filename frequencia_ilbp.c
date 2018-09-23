//alocacao de matrizes   .....
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void frequencia_ilbp(int ilbp, int *frequencia) {		
	(*(frequencia+ilbp))++;
}

int main() {
	int *frequencia = NULL;
	frequencia = (int *) calloc(512, sizeof(int));

	if(frequencia==NULL) 
		printf("Memoria nao alocada\n");

	frequencia_ilbp(4, frequencia);
	frequencia_ilbp(4, frequencia);
	frequencia_ilbp(5, frequencia);
	frequencia_ilbp(4, frequencia);
	frequencia_ilbp(4, frequencia);
	frequencia_ilbp(8, frequencia);

	for (int i=0; i<10 ; i++) {
		printf("%d ", *(frequencia+i));		
	}

	free(frequencia);
	return 0;
}
