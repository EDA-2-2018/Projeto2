#include "projeto_2.h"

int main() {
	int matriz[3][3], i, j;
    int ILBP;

	for(i=0; i<3; i++) 
		for(j=0; j<3; j++) 
			scanf("%d", &matriz[i][j]);
		
	calcula_ilbp(matriz, &ILBP);

	printf("\nILBP = %d\n", ILBP);
	
	return 0;
}

// 56 57 58 
// 25 17 10 
// 12 15 34 

// 25 17 10
// 12 15 34
// 90 11 12