#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void linhas_colunas(FILE *file, int *linhas, int *colunas); //conta_linhas_colunas(..)
void calcula_ilbp(int matriz[3][3], int *ilbp);
void vetor_treinameto(int *numeros, int quantNumeros, int limite);
void vetor_teste(int *numeros_trein, int *numeros_test);
bool existe(int *valores, int tam, int valor);

void linhas_colunas(FILE *file, int *linhas, int *colunas){
    int c=0, li=0, co;
    int numero;
    char caractere; 

    while((fscanf(file,"%d%c", &numero, &caractere))!=EOF) {
        if(caractere=='\n'){
            li++;
            c++;            
        }
        if(caractere==';')
            c++;        
    }
    co = c/li;

    *linhas = li;
    *colunas = co;
}

void calcula_ilbp(int matriz[3][3], int *ilbp) {
    int i, j, soma=0;

    int *binario = NULL;
    binario = (int *) calloc(9, sizeof(int));

    for(i=0; i<3; i++) 
        for(j=0; j<3; j++) 
            soma += matriz[i][j];
        
    double avg = soma/9;
        
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(matriz[i][j]<= avg) 
                matriz[i][j] = 0;
            else if(matriz[i][j]> avg)
                matriz[i][j] = 1;
        }
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

    int decimal=0;
    for(i=0; i<9; i++) {
        decimal += binario[i] * pow(2, 8-i);
    }

    *ilbp = decimal;
    free(binario);

    // binario = (int *) calloc(9, sizeof(int));
    // free(binario);
}

void vetor_treinameto(int *numeros, int quantNumeros, int limite){
    int v;
    for(int i=1; i<=quantNumeros; i++){
        v = 1+(rand() % limite);
        while(existe(numeros,i,v)){
            v = 1+(rand() % limite);
        }
        numeros[i] = v;
    }	
}

void vetor_teste(int *numeros_trein, int *numeros_test) {
	int i, count=0;
	for(i=1; i<=50; i++) {
        if(!existe(numeros_trein, 25, i)) {
        	count+=1;
        	numeros_test[count] = i;
        }
	}		
}

bool existe(int *valores, int tam, int valor){
    for(int i=1; i<=tam; i++){
        if(valores[i]==valor)
            return true;
    }
    return false;
}
