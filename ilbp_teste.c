#include "projeto_2.h"

int main() {
	int matriz[3][3], i, j;
    int ILBP;

	for(i=0; i<3; i++) 
		for(j=0; j<3; j++) 
			scanf("%d", &matriz[i][j]);
		
	calcula_ilbp(matriz, &ILBP);

	printf("%d\n", ILBP);
	return 0;
}