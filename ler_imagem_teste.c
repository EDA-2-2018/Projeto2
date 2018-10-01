#include "projeto_2.h"

int main() {

	int maior_valor;
	FILE *arquivo;

	char nome_imagem[25] = "./asphalt/asphalt_09.txt";
	arquivo = fopen(nome_imagem , "r+");	

	int *vetor_frequencia_ilbp=NULL;
	vetor_frequencia_ilbp = (int *) calloc(512, sizeof(int));

	ler_imagem(arquivo, vetor_frequencia_ilbp, &maior_valor, nome_imagem);
	
	for(int i=0; i<512; i++) 
		printf("ilbp = %d, %d veses\n", i, *(vetor_frequencia_ilbp + i));
	
	printf("\n%d\n", maior_valor);
	fclose(arquivo);
	return 0;
}

