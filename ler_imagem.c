#include "projeto_2.h"
// 
// void ler_imagem(char...);

int main() {
	int l=0, c=0, numm, count=0, i,j;
	char letra;
	int linhas, colunas;
	FILE *arquivo;

	//                 asphalt/asphalt_0X.txt
	arquivo = fopen("./asphalt/asphalt_02.txt" , "r+");	
	
	linhas_colunas(arquivo, &linhas, &colunas); //conta linhas e coluna da imagem e coloca nas variaveis linhas e colunas
	fclose(arquivo);														

	printf("\nO arquivo tem %d linhas e %d colunas!", linhas, colunas);

	int matriz[linhas][colunas];
	//               asphalt/asphalt_0X.txt
	arquivo = fopen("asphalt/asphalt_04.txt" , "r+");	

//---------------------
// lendo todos os numeros da imagem e colocanado em uma matriz 1025x1025
	while((fscanf(arquivo,"%d%c", &numm, &letra))!=EOF) { 
			matriz[l][c] = numm;			
			c++;
			if(c==linhas){
				c-=linhas;
				l++;
			}
	}
//------------------------------
	printf("\n\n");

	for(i=0; i<10; i++) {
		for(j=0; j<10; j++) {			
			printf("%.3d ", matriz[i][j]);	
		}
		printf("\n");
	}

	printf("\n\n");

	for(i=1; i<4; i++) {
		for(j=1; j<4; j++) {			
			printf("%.3d ", matriz[i][j]);	
		}
		printf("\n");
	}
	printf("\n");
	for(i=1021; i<1024; i++) {
		for(j=1021; j<1024; j++) {			
			printf("%.3d ", matriz[i][j]);	
		}
		printf("\n");
	}
							  //teste [][]					
	printf("\n\n----<%d>----\n", matriz[1][1]);
	printf("\n----<%d>----\n", matriz[1023][1023]);
	fclose(arquivo);
	printf("\n");
	return 0;
}


	// binario[0] = matriz[0][0];  // [x][y]
	// binario[1] = matriz[0][1];  // [x][y+1]
	// binario[2] = matriz[0][2];  // [x][y+2] 
	// binario[3] = matriz[1][2];  // [x+1][y+2]
	// binario[4] = matriz[2][2];  // [x+2][y+2]
	// binario[5] = matriz[2][1];  // [x+2][y+1]
	// binario[6] = matriz[2][0];  // [x+2][y]
	// binario[7] = matriz[1][0];  // [x+1][y]
	// binario[8] = matriz[1][1];  // [x+1][y+1]


// int main() {
// 	int linhas, colunas;
// // file	
// 	FILE *arquivo;
	// arquivo = fopen("asphalt_02.txt" , "r+");
	
// 	linhas_colunas(arquivo, &linhas, &colunas);
	
// 	printf("\n%d linhas\n", linhas);
// 	printf("\n%d colunas\n", colunas);

//   	fclose(arquivo);

// 	return 0;
// }
