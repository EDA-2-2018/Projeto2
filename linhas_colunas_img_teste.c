#include "projeto_2.h"

int main() {
	int linhas, colunas;

	FILE *arquivo;
	arquivo = fopen("./asphalt/asphalt_02.txt" , "r+");
	
	linhas_colunas(arquivo, &linhas, &colunas);
  	fclose(arquivo);
	
	printf("\n%d linhas\n", linhas);
	printf("\n%d colunas\n", colunas);

	return 0;
}

