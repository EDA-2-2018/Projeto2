#include "projeto_2.h"

int main() {

    int aspalt_treinamento[25], grass_treinamento[25];
    int aspalt_teste[25], grass_teste[25];
 	
	srand(time(NULL));
	
    vetor_treinameto(aspalt_treinamento, 25, 50);
	vetor_teste(aspalt_treinamento, aspalt_teste);

	vetor_treinameto(grass_treinamento, 25, 50);
	vetor_teste(grass_treinamento, grass_teste);

	char nome_imagem[25];
	FILE *arquivo;
	int maior_valor; 

	int *vetor_frequencia_ilbp=NULL;
	vetor_frequencia_ilbp = (int *) calloc(512, sizeof(int));

	if (vetor_frequencia_ilbp==NULL) {
		printf("Alocacao de falhou... FIM!\n");
		exit(1);
	}

	// lendo imagens grass
	for(int i=1; i<=25; i++) {
		sprintf(nome_imagem, "./grass/grass_%.2d.txt", grass_treinamento[i]);
		arquivo = fopen(nome_imagem, "r+"); 
		ler_imagem(arquivo, vetor_frequencia_ilbp, &maior_valor, nome_imagem);
		// printf("ilbp = %d, %d veses\n", 255, *(vetor_frequencia_ilbp + 255));
		fclose(arquivo);
	}

	// lendo imagens asphalt
	for(int i=1; i<=25; i++) {
		sprintf(nome_imagem, "./asphalt/asphalt_%.2d.txt", aspalt_treinamento[i]);
		arquivo = fopen(nome_imagem, "r+"); 
		ler_imagem(arquivo, vetor_frequencia_ilbp, &maior_valor, nome_imagem);
		// printf("ilbp = %d, %d veses\n", 255, *(vetor_frequencia_ilbp + 255));
		fclose(arquivo);
	}

	printf("\n\n\n");
	for(int i=0; i<512; i++) 
		printf("ilbp = %d, %d veses\n", i, *(vetor_frequencia_ilbp + i));

	free(vetor_frequencia_ilbp);
    return 0;
}
