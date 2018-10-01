#include "projeto_2.h"

int main() {

    int aspalt_treinamento[25], grass_treinamento[25];
    int aspalt_teste[25], grass_teste[25];
 	
	srand(time(NULL));
	
    vetor_treinameto(aspalt_treinamento, 25, 50);
	vetor_teste(aspalt_treinamento, aspalt_teste);

	vetor_treinameto(grass_treinamento, 25, 50);
	vetor_teste(grass_treinamento, grass_teste);

	int maior_valor; 
	char nome_imagem[25];	

	int *frequencia_grass_treinamento=NULL;
	frequencia_grass_treinamento = (int *) calloc(512, sizeof(int));
	if (frequencia_grass_treinamento==NULL) {
		printf("Alocacao de falhou... FIM!\n");
		exit(1);
	}
	
	// lendo imagens grass
	for(int i=1; i<=25; i++) {
		sprintf(nome_imagem, "./grass/grass_%.2d.txt", grass_treinamento[i]);
		FILE *arquivo = fopen(nome_imagem, "r+"); 
		ler_imagem(arquivo, frequencia_grass_treinamento, &maior_valor, nome_imagem);		
	}

	int *frequencia_asphalt_treinamento=NULL;
	frequencia_asphalt_treinamento = (int *) calloc(512, sizeof(int));
	if (frequencia_asphalt_treinamento==NULL) {
		printf("Alocacao de falhou... FIM!\n");
		exit(1);
	}
	// lendo imagens asphalt
	for(int i=1; i<=25; i++) {
		sprintf(nome_imagem, "./asphalt/asphalt_%.2d.txt", aspalt_treinamento[i]);
		FILE *arquivo = fopen(nome_imagem, "r+"); 
		ler_imagem(arquivo, frequencia_asphalt_treinamento, &maior_valor, nome_imagem);
	}

//imprime 
	printf("\n\n\n");
	for(int i=0; i<512; i++) 
		printf("ilbp = %d, %d veses --- %d veses\n", i, *(frequencia_grass_treinamento + i), *(frequencia_asphalt_treinamento + i));

	free(frequencia_grass_treinamento);
	free(frequencia_asphalt_treinamento);
	 // free(frequencia_grass_teste);
	// free(frequencia_asphalt_teste);
    return 0;
}
