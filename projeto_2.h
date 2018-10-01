#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void ler_imagem(FILE *arquivo, int *vetor, int *maior_valor, char *nome_imagem);
void linhas_colunas(FILE *file, int *linhas, int *colunas); //conta_linhas_colunas(..)
// void frequencia_ilbp(int ilbp, int *frequencia);
void calcula_ilbp(int matriz[3][3], int *ilbp);
int converte_binario(int *vet);
void vetor_treinameto(int *numeros, int quantNumeros, int limite);
void vetor_teste(int *numeros_trein, int *numeros_test);
int existe(int *valores, int tam, int valor);

void linhas_colunas(FILE *file, int *lin, int *col){
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

    *lin = li;
    *col = co;

    // fclose(file);
}
void frequencia_ilbp(int ilbp, int *frequencia) {       
    (*(frequencia+ilbp))++;
}

void calcula_ilbp(int matriz[3][3], int *ilbp) {
    int i, j, soma=0;

    int *binario = NULL;
    binario = (int *) calloc(9, sizeof(int));
    
    if (binario==NULL) {
        printf("Memoria nao alocada\n");
        //exit...
    }


    for(i=0; i<3; i++) 
        for(j=0; j<3; j++) 
            soma += matriz[i][j];
        
    double avg = soma/9.00;

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

    int x, y=9;    
    int *shifts = NULL;
    shifts = (int *) calloc(9, sizeof(int));

    while(y--) {

        *(shifts+y) = converte_binario(binario);

        for(i=8; i>=0; i--) {
            if(i==8)
                x=binario[8];
            if (i==0)
                binario[0]=x;
            else
                binario[i] = binario[i-1];      
        }
    }

    int w, menor=511;

    for( w=8; w>=0; w--) {
        if (*(shifts+w)<menor)
            menor = *(shifts+w);
    }
    
    *ilbp = menor;

    free(binario);
}

int converte_binario(int *vet){
    int decimal = 0, i;
    for(i=0; i<9; i++) {
        decimal += vet[i] * pow(2, 8-i);
    }
    return decimal;
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

int existe(int *valores, int tam, int valor){
    for(int i=1; i<=tam; i++){
        if(valores[i]==valor)
            return 1;
    }
    return 0;
}

void ler_imagem(FILE *arquivo, int *vetor, int *maior_valor, char *nome_imagem) {
    
    int l=0, c=0, numm,maior=0;
    char letra;
    int linhas, colunas;

    linhas_colunas(arquivo, &linhas, &colunas); 
    fclose(arquivo);

// aloca memoria para matriz[linhas][colunas]
    int x;
    int **matriz = (int **) malloc(linhas * sizeof(int *)); //Aloca um Vetor de Ponteiros
    for (x = 0; x < linhas; x++) //Percorre as linhas do Vetor de Ponteiros
        matriz[x] = (int *) malloc(colunas * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
    
    // int matriz[linhas][colunas];

    arquivo = fopen(nome_imagem, "r+");

    while((fscanf(arquivo,"%d%c", &numm, &letra))!=EOF) { 
        matriz[l][c] = numm;    

        if(matriz[l][c]>maior)
            maior = matriz[l][c];
        
        c++;

        if(c==linhas){
            c-=linhas;
            l++;
        }
    }

    *maior_valor = maior;
    fclose(arquivo);
//------------------------------
    int lin=1, col=1, i, j;
    int co=1042441;
    int matriz2[3][3];
    int ILBP;
    
    int *freq = NULL;
    freq = (int *) calloc(512, sizeof(int));

    if(freq==NULL) 
        printf("Memoria nao alocada\n");

    while(co--) {

        for(i=lin; i<lin+3; i++) 
            for(j=col; j<col+3; j++) 
                matriz2[i-lin][j-col] = matriz[i][j];
        
        calcula_ilbp(matriz2, &ILBP);  
        (*(freq+ILBP))++;

        lin++;
        if(lin%(1025-2-3+1+1)==0) {
            lin-=(1025-2-3+1);
            col++;
        }
    }

    for(int i=0; i<512; i++) 
        (*(vetor+i)) += (*(freq + i));

// libera memorias alocadas
    
    free(freq);

    for(int x=0; x<linhas; x++) //percorre o vetor para liberar a segunda dimensao
        free(matriz[x]);  
    free(matriz); //libera a primeira dimensao
    
}

