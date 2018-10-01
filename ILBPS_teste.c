#include "projeto_2.h"

int main() {
	int i, j, matriz1[10][10], frequencia[64];
	int l = 1, c = 1, count;
	int ilbpp;
	
	for(i=0; i<10; i++) 
		for(j=0; j<10; j++) 
			scanf("%d", &matriz1[i][j]);		

	printf("\n");

	count = pow(10 -2 - 3 + 1, 2);

	int matriz2[3][3];
	int x=0;
	int t, u;

	// printf("Todas as matriz ilbpp de uma matriz 10x10\n");
	while(count--) {
		
		for(i=l; i<l+3; i++) 
			for(j=c; j<c+3; j++) 
				matriz2[i-l][j-c] = matriz1[i][j];		
			
		calcula_ilbp(matriz2, &ilbpp);  
		printf("\n---%d----\n", ilbpp);	

		for(i=l; i<l+3; i++) {
			for(j=c; j<c+3; j++) {
				printf("%.2d ", matriz1[i][j]);		
				// matriz2[i][j] = matriz1[i][j];
			}
			printf("\n");
		}
		printf("\n");	
		l++;
		if(l%(10-2-3+1+1)==0) {
			l-=(10-2-3+1);
			c++;
		}
	}

	return 0;
}
// 00 01 02 03 04 05 06 07 08 09
// 10 11 12 13 14 15 16 17 18 19
// 20 21 22 23 24 25 26 27 28 29
// 30 31 32 33 34 35 36 37 38 39
// 40 41 42 43 1032 45 46 47 48 49
// 50 51 52 53 54 55 56 57 58 59
// 60 61 62 63 64 65 25 17 10 69
// 70 71 72 73 74 75 12 15 34 79
// 80 81 82 83 84 85 90 11 12 89
// 90 91 92 93 94 95 96 97 98 99

// 25 17 10
// 12 15 34
// 90 11 12


// django rest nao e mvt 

// Quatas matrizes AxA cabem em uma matris YxY
// 				( Y - A + 1)^2
// 				(10 - 3	+ 1)^2 = 64
