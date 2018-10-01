#include "projeto_2.h"

int main() {

	int maior_valor;

	int *frequencia_grass_treinamento=NULL;
	frequencia_grass_treinamento = (int *) calloc(512, sizeof(int));

	char nome_imagem[25];
	sprintf(nome_imagem,"./asphalt/asphalt_09.txt");
	FILE *arquivo = fopen(nome_imagem , "r+");	
	ler_imagem(arquivo, frequencia_grass_treinamento, &maior_valor, nome_imagem);
	
	for(int i=0; i<512; i++) 
		printf("ilbp = %d, %d veses\n", i, *(frequencia_grass_treinamento + i));
	
	printf("\n%d\n", maior_valor);
	return 0;
}

