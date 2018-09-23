#include "projeto_2.h"

int main() {

    int aspalt_treinamento[25], grass_treinamento[25];
    int aspalt_teste[25], grass_teste[25];
 	
	srand(time(NULL));
	
    vetor_treinameto(aspalt_treinamento, 25, 50);
	vetor_teste(aspalt_treinamento, aspalt_teste);

	vetor_treinameto(grass_treinamento, 25, 50);
	vetor_teste(grass_treinamento, grass_teste);

    printf("\nTREINAMENTO       TESTE\n\n");

    for(int i=1; i<=25; i++) 
    	// sprintf..
    	printf("aspalt_%.2d.txt   aspalt_%.2d.txt \n", aspalt_treinamento[i], aspalt_teste[i]);
    printf("\n");
	
	for(int i=1; i<=25; i++) 
    	printf("grass_%.2d.txt   grass_%.2d.txt \n", grass_treinamento[i], grass_teste[i]);
        
    return 0;
}
