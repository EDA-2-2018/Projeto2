#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/// criar funcao de vetor_frequenciaILBP 512
/// e criar funcao ler imagem
// chamar na main apenas a funcao de ler_imagem(arquivo..)
// alocar memoria nas funcoes
int converte_binario(int *vet){
	int decimal = 0, i;

	for(i=0; i<9; i++) {
        decimal += vet[i] * pow(2, 8-i);
    }

    return decimal;
}

void calcula_ilbp(int matriz[3][3], int *ilbp);

int main() {
	int matriz[3][3], i, j;
    int ILBP;

while(1)	{
	for(i=0; i<3; i++) 
		for(j=0; j<3; j++) 
			scanf("%d", &matriz[i][j]);
		
	calcula_ilbp(matriz, &ILBP);

	printf("\n\nILBP = %d\n\n------------------------------------------------\n\n", ILBP);
	}
	return 0;
}

void calcula_ilbp(int matriz[3][3], int *ilbp) {
    int i, j, soma=0;

    int *binario = NULL;
    binario = (int *) calloc(9, sizeof(int));

    for(i=0; i<3; i++) 
        for(j=0; j<3; j++) 
            soma += matriz[i][j];
        
    double avg = soma/9.00;
        
    printf("\nmedia = %lf\n", avg);

    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(matriz[i][j]<= avg) 
                matriz[i][j] = 0;
            else if(matriz[i][j]> avg)
                matriz[i][j] = 1;
        }
    }
    printf("\n");
    for(i=0; i<3; i++) {
    	for(j=0; j<3; j++) {
    		printf("%d ", matriz[i][j]);
    	}
    printf("\n");
    }

    binario[0] = matriz[0][0];
    binario[1] = matriz[0][1];
    binario[2] = matriz[0][2];
    binario[3] = matriz[1][2];
    binario[4] = matriz[2][2];
    binario[5] = matriz[2][1];
    binario[6] = matriz[2][0];
    binario[7] = matriz[1][0];
    binario[8] = matriz[1][1];

    printf("\n");

    int x, y=9;    
	int *shifts = NULL;
    shifts = (int *) calloc(9, sizeof(int));

    while(y--) {
    	for(i=0; i<9; i++) {
			printf("%d", binario[i]);    	
    	}
    	printf(" -->  %d", converte_binario(binario));
    	*(shifts+y) = converte_binario(binario);

    	for(i=8; i>=0; i--) {
			if(i==8)
				x=binario[8];
			if (i==0)
				binario[0]=x;
			else
				binario[i] = binario[i-1];    	
    	}


    	printf("\n");
	}

    printf("\n");

    int w, menor=511;
    for( w=8; w>=0; w--) {

    	if (*(shifts+w)<menor)
    		menor = *(shifts+w);

    	printf("%d ", *(shifts+w));
    }
    
    *ilbp = menor;

    free(binario);
}

// 56 57 58 
// 25 17 10 
// 12 15 34 

// 25 17 10
// 12 15 34
// 90 11 12