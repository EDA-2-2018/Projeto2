#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int *inicia_vetor(FILE *fp, int tam, int maior, int *vetor);

int *glcm(int *matriz,int l, int num_linhas, int num_colunas, int *metricas);

void destroi_vetor(int *p);








int main(){

	int *n_img, *p, *vetor;
	int metricas[24];
	int num_linhas=0, num_colunas=0, num=0, maior_num=0, i,j,f,g,a=0,b=0,adj1,adj2,c_adj=0,l=0, v_adj1, v_adj2;
	char c;

	FILE *fp;
	fp= fopen("img_teste_glcm.txt","r");

	if(!fp){
		printf("Erro na abertura do arquivo!!!! \n");
	}

		
	while(!feof(fp)){
		fscanf(fp,"%c",&c);
		
		
		if(c ==';'){
			num_colunas+=1;
		}

		if(c=='\n')
			num_linhas+=1;


		if(c !=';' && c!= '\n'){
			num+=1;
			//printf("%d \n",num);
		}
		else{
			if(num>=maior_num)
				maior_num=num;
			num=0;
		}

	}	
	

	fclose(fp);
	
	num_linhas= (num_linhas-1);
	num_colunas= (num_colunas+num_linhas)/(num_linhas);

	printf("Número de linhas: %d \n", num_linhas);
	printf("Número de colunas: %d \n", num_colunas);
	printf("O maior número de caracteres é: %d \n", maior_num);
		

	/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Vetor para alocação dinãmica.	

	vetor= (int *) malloc ((num_linhas*num_colunas) * sizeof (int));

	

	n_img= inicia_vetor(fp, (num_linhas*num_colunas), maior_num, vetor);
	
	for(i=0;i<(num_linhas*num_colunas);i++ ){
		printf("numero[%d]: %d\n",i, *(n_img+i));
		if(*(n_img+i) >= l)
			l=*(n_img+i);
	}
	
	printf("Maior valor do vetor: %d\n",l);


	
	p=glcm(n_img, l, num_linhas, num_colunas, metricas);


	for(i=0;i<8;i++){
		for(j=0;j<3;j++){
			printf("Métricas: %d\n",metricas[j+a]);
		}
		a+=3;
	}


	destroi_vetor(vetor);

	
	return 0;
}















int *inicia_vetor(FILE *fp, int tam, int maior, int *vetor){
	char c,car[1];
	char v[1]=" ";

	char num[maior];
	int i=0,j=0,k, menor=1;

	
	fp= fopen("img_teste_glcm.txt","r");
	
	while(!feof(fp)){
		fscanf(fp,"%c",&c);
		
		if(c !=';' && c!= '\n'){
			car[0]=c;
			num[i]=car[0];
			//printf("%s\n",num);
			if (i<(maior-1)){
				i++;
				//printf("%s\n",num);
			}
		}	

		else{
			if(j<tam){
				*(vetor+j)= atoi(num);
				//printf("numero[%d]: %d\n",j, vetor[j]);
				j++;
				
				for(k=0; k<maior;k++)
					num[k]=v[0];
				i=0;
			}
		}
	
	}

	

	return vetor;
}


int *glcm(int *matriz, int l, int num_linhas, int num_colunas, int *metricas){

	int i,j,f,g,v_adj1, v_adj2, c_adj=0, adj1=0,adj2=0, a=0,b=0;
	int contraste=0, homogeneidade=0, energia=0;
	int mat_glcm_d[l][l];
	int mat_glcm_e[l][l];
	int mat_glcm_b[l][l];
	int mat_glcm_c[l][l];
	int mat_glcm_dds[l][l];
	int mat_glcm_ddi[l][l];
	int mat_glcm_des[l][l];
	int mat_glcm_dei[l][l];


/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM à direita com tamanho L;
	for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas);f++){
					for(g=0;g<(num_colunas-1);g++){
				
						adj1= *(matriz+(g+a));
						adj2= *(matriz+(g+a+1));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				
			}
			
			mat_glcm_d[i-1][j-1]= c_adj;
			a=0;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM à direita\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_d[i][j]);
	//	}
	//	printf("\n");
	//}
	
	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_d[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_d[i][j]);
			homogeneidade+= (mat_glcm_d[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*metricas=contraste;
	*(metricas+1)= energia;
	*(metricas+2)=homogeneidade;

	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM à esquerda com tamanho L;
	
	for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas);f++){
					for(g=0;g<(num_colunas-1);g++){
				
						adj2= *(matriz+(g+a));
						adj1= *(matriz+(g+a+1));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				
			}
			
			mat_glcm_e[i-1][j-1]= c_adj;
			a=0;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM à esquerda:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_e[i][j]);
	//	}
	//	printf("\n");
	//}		



	

	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_e[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_e[i][j]);
			homogeneidade+= (mat_glcm_e[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+3)=contraste;
	*(metricas+4)= energia;
	*(metricas+5)=homogeneidade;
	
	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;
	

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM para baixo com tamanho L;

		b+=5; // inciando adj2 para começar a leitura na posição 5 do vetor dinâmico.
for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas-1);f++){
					for(g=0;g<(num_colunas);g++){
				
						adj1= *(matriz+(g+a));
						adj2= *(matriz+(g+b));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				b+=5;
				
			}
			
			mat_glcm_b[i-1][j-1]= c_adj;
			a=0;
			b=5;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM à para baixo:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_b[i][j]);
	//	}
	//	printf("\n");
	//}		




	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_b[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_b[i][j]);
			homogeneidade+= (mat_glcm_b[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+6)=contraste;
	*(metricas+7)= energia;
	*(metricas+8)=homogeneidade;

	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;



/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM para cima com tamanho L;
		b=0;	//zerando o valor incial de b;
		b+=5; // inciando adj2 para começar a leitura na posição 5 do vetor dinâmico.
for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas-1);f++){
					for(g=0;g<(num_colunas);g++){
				
						adj2= *(matriz+(g+a));
						adj1= *(matriz+(g+b));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				b+=5;
				
			}
			
			mat_glcm_c[i-1][j-1]= c_adj;
			a=0;
			b=5;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM à para baixo:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_c[i][j]);
	//	}
	//	printf("\n");
	//}



	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_c[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_c[i][j]);
			homogeneidade+= (mat_glcm_c[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+9)=contraste;
	*(metricas+10)= energia;
	*(metricas+11)=homogeneidade;
	
	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;




/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM para diagonal direita inferior com tamanho L;
		c_adj=0;
		b=0;
		b+=6; // inciando adj2 para começar a leitura na posição 6 do vetor dinâmico.
	for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas-1);f++){
					for(g=0;g<(num_colunas-1);g++){
				
						adj1= *(matriz+(g+a));
						adj2= *(matriz+(g+b));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				b+=5;
				
			}
			
			mat_glcm_ddi[i-1][j-1]= c_adj;
			a=0;
			b=6;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM para diagonal direita inferior:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_ddi[i][j]);
	//	}
	//	printf("\n");
	//}		



	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_ddi[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_ddi[i][j]);
			homogeneidade+= (mat_glcm_ddi[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+12)=contraste;
	*(metricas+13)= energia;
	*(metricas+14)=homogeneidade;

	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;



/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM para diagonal esquerda superior com tamanho L;
		c_adj=0;
		b=0;
		a=0;
		b+=6; // inciando adj2 para começar a leitura na posição 6 do vetor dinâmico.
	for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas-1);f++){
					for(g=0;g<(num_colunas-1);g++){
				
						adj2= *(matriz+(g+a));
						adj1= *(matriz+(g+b));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				b+=5;
				
			}
			
			mat_glcm_des[i-1][j-1]= c_adj;
			a=0;
			b=6;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM para diagonal esquerda superior:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_des[i][j]);
	//	}
	//	printf("\n");
	//}	



	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_des[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_des[i][j]);
			homogeneidade+= (mat_glcm_des[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+15)=contraste;
	*(metricas+16)= energia;
	*(metricas+17)=homogeneidade;

	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;	


/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM para diagonal esquerda inferior com tamanho L;
		c_adj=0;
		a=1;
		b=5;
		//b+=6; // inciando adj2 para começar a leitura na posição 6 do vetor dinâmico.
	for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas-1);f++){
					for(g=0;g<(num_colunas-1);g++){
				
						adj1= *(matriz+(g+a));
						adj2= *(matriz+(g+b));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				b+=5;
				
			}
			
			mat_glcm_dei[i-1][j-1]= c_adj;
			a=1;
			b=5;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM para diagonal esquerda inferior:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_dei[i][j]);
	//	}
	//	printf("\n");
	//}		



	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_dei[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_dei[i][j]);
			homogeneidade+= (mat_glcm_dei[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+18)=contraste;
	*(metricas+19)= energia;
	*(metricas+20)=homogeneidade;

	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;	


/////////////////////////////////////////////////////////////////////////////////////////////
///////////////Criando a matrix GLCM para diagonal direita superior com tamanho L;
		c_adj=0;
		a=1;
		b=5;
		//b+=6; // inciando adj2 para começar a leitura na posição 6 do vetor dinâmico.
	for(i=1;i<=l;i++){
		for(j=1;j<=l;j++){
			v_adj1=i;
			v_adj2=j;
			
			for(f=0;f<(num_linhas-1);f++){
					for(g=0;g<(num_colunas-1);g++){
				
						adj2= *(matriz+(g+a));
						adj1= *(matriz+(g+b));

						if(v_adj1==adj1 && v_adj2==adj2){
							
							c_adj+=1;
						}
					//printf("Matrix de posição glcm: %d, %d \n", v_adj1, v_adj2);
					//printf("Matrix cinza da imagem: %d, %d \n", adj1, adj2);			
					
					//printf("Valo da comparação:     %d\n", c_adj);
					//printf("\n\n\n");			
					}
				a+=5;
				b+=5;
				
			}
			
			mat_glcm_dds[i-1][j-1]= c_adj;
			a=1;
			b=5;
			c_adj=0;
			
		}
		//printf("\n\n\n\n");
	}
	
	printf("\nMATRIX GLCM para diagonal direita superior:\n");

	//for(i=0;i<l;i++){
	//	for(j=0;j<l;j++){
	//		printf("%d \t", mat_glcm_dds[i][j]);
	//	}
	//	printf("\n");
	//}	


	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			contraste+= ((i-j)*(i-j))*mat_glcm_dds[i][j];
			energia+= (mat_glcm_d[i][j]*mat_glcm_dds[i][j]);
			homogeneidade+= (mat_glcm_dds[i][j])/(1+ abs(i-j));
			
		}
	}
	
	*(metricas+21)=contraste;
	*(metricas+22)= energia;
	*(metricas+23)=homogeneidade;
	
	printf("%d \n", contraste);
	printf("%d \n", energia);
	printf("%d \n", homogeneidade);
	
	printf("\n\n");

	contraste=0;
	energia=0;
	homogeneidade=0;	




	return metricas;
}


void destroi_vetor(int *p){
	free(p);
}


