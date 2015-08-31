#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

//#include "arquivo.c"
#include "calcDistancia.c"
/*

#include<solucaoInicial.c>
#include<ILS.c>
#include<perturbacao.c>
#include<criterioDeAceitacao.c>

*/

int main(int argc, char const *argv[]){
	int *cidadeX, *cidadeY, *cidadeD, demandaTotal = 0, capacidade, cidades;
	int tamLinha = 100, iLinha = 0;
	float **distancia;
	char arq[50];
	char linha[tamLinha];
	char *token;
	FILE *arquivo;
	
	//printf("Arquivo: ");
	//scanf("%s", arq);

	//Nome do Arquivo
	//arquivo = fopen(arq, "r");
	arquivo = fopen("E-n22-k4.vrp", "r");
	if(arquivo == NULL){
		printf("Erro, nao foi possivel abrir o arquivo %s. \n", arq);
	}else{
		while(!feof(arquivo)){
			fgets(linha, tamLinha , arquivo);
			if (iLinha == 3){ 
				//Quantidade de Cidades/Instancias
				token = strtok(linha," ");
				token = strtok (NULL, " ");
				token = strtok (NULL, " ");
				cidades = atoi(token);
				printf("Quantidade de Cidades: %d \n", cidades);
				//Alocação do vetor da posição X da cidade
				cidadeX = malloc((cidades) * sizeof(int));
				if (cidadeX == NULL) {
				  printf( "Erro Malloc Cidade X!\n");
				  exit(-1);
				}
				//Alocação do vetor da posição Y da cidade
				cidadeY = malloc((cidades) * sizeof(int));
				if (cidadeY == NULL) {
				  printf( "Erro Malloc Cidade Y!\n");
				  exit(-1);
				}
				//Alocação do vetor das Demandas
				cidadeD = malloc((cidades) * sizeof(int));
				if (cidadeD == NULL) {
				  printf( "Erro Malloc Demanda!\n");
				  exit(-1);
				}
				//Alocação do vetor de distancias
				distancia = malloc((cidades) * sizeof(float *));
				for (int i = 0; i < cidades; ++i){
					distancia[i] = malloc((i) * sizeof(float *));
				}
				if (distancia == NULL) {
				  printf( "Erro Malloc distancia!\n");
				  exit(-1);
				}
			}else if (iLinha == 5){ 
				//Capacidade do veículo
				token = strtok(linha," ");
				token = strtok (NULL, " ");
				token = strtok (NULL, " ");
				capacidade = atoi(token);
				printf("Capacidade: %d \n", capacidade);
			}else if (iLinha > 6 && iLinha <= 6+cidades){
				//Cidade X Y
				int cidade;
				//Pega a Cidade
				token = strtok(linha," ");
				cidade = atoi(token);
				//printf("Cidade: %d ", atoi(token));
				//Pega o X
				token = strtok (NULL, " ");
				cidadeX[cidade - 1] = atoi(token);
				//printf("X: %d ", atoi(token));
				//Pega o Y
				token = strtok (NULL, " ");
				cidadeY[cidade - 1] = atoi(token);
				//printf("Y: %d \n", atoi(token));
			}else if (iLinha > (7+cidades) && iLinha <= (7+cidades*2)){
				//Cidade Demanda
				int cidade;
				//Pega a Cidade
				token = strtok(linha," ");
				cidade = atoi(token);
				//printf("Cidade: %s ", token);
				//Pega a Demanda
				token = strtok (NULL, " ");
				cidadeD[cidade - 1] = atoi(token);
				//printf("Demanda: %s \n", token);
				demandaTotal += atoi(token);
			}
			iLinha++;
		}
	}	
	fclose(arquivo);

	printf("Demanda Total: %d \n",demandaTotal);
	printf("Minimo de Veículos: %f \n", ceil((float)demandaTotal/(float)capacidade));
	
	//Gera a "matriz" com as distâncias
	calcDistancia(cidades, cidadeX, cidadeY, distancia);

	printf("\n %f \n", distancia[20][17] + distancia[20][18] + distancia[18][15] + distancia[15][12] + distancia[19][16] + distancia[21][19] + distancia [21][14] + distancia[13][11] + distancia[11][4] + distancia[4][3] + distancia[8][3] + distancia[10][8] + distancia[9][7] + distancia[7][5] + distancia[5][2] + distancia[2][1] + distancia[6][1] + distancia[17][0] + distancia[12][0] + distancia[16][0] + distancia[14][0] + distancia[13][0] + distancia[10][0] + distancia[9][0] + distancia[6][0]);

/*
	int c, cc;
	float dis = 0;
	printf("Cidade: \n");
	scanf("%d", &c);
	while(1){
		printf("Cidade: \n");
		scanf("%d", &cc);
		if(c > cc){
			dis += distancia[c][cc];
		}else{
			dis += distancia[cc][c];
		}
		printf("Dis: %f \n", dis );		
		c = cc;
	}
*/
	/*
	s = solucaoInicial(S);
	s1 = ILS(s);
	while(){
		p = perturbacao(s1);
		p1 = ILS(p1);
		s1 = criterioDeAceitacao(s1, p1);
	}
	*/
	free(cidadeX);
	free(cidadeY);
	free(cidadeD);
	free(distancia);

	return 0;
}