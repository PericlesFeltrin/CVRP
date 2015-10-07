#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

//#include "arquivo.c"
#include "calcDistancia.c"
#include "calcCusto.c"
#include "solucaoInicial.c"
#include "criterioDeAceitacao.c"
#include "perturbacao.c"
#include "imprime.c"
#include "ILS.c"


int main(int argc, char const *argv[]){
	int *cidadeX, *cidadeY, *cidadeD, *rotas, *novasRotas, demandaTotal = 0, capacidade, quantCidades;
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
	//arquivo = fopen("E-n22-k4.vrp", "r");
	arquivo = fopen("A-n32-k5.vrp", "r");
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
					quantCidades = atoi(token);
				printf("Quantidade de Cidades: %d \n", quantCidades);
				//Alocação do vetor da posição X da cidade
				cidadeX = malloc((quantCidades) * sizeof(int));
				if (cidadeX == NULL) {
				  printf( "Erro Malloc Cidade X!\n");
				  exit(-1);
				}
				//Alocação do vetor da posição Y da cidade
				cidadeY = malloc((quantCidades) * sizeof(int));
				if (cidadeY == NULL) {
				  printf( "Erro Malloc Cidade Y!\n");
				  exit(-1);
				}
				//Alocação do vetor das Demandas
				cidadeD = malloc((quantCidades) * sizeof(int));
				if (cidadeD == NULL) {
				  printf( "Erro Malloc Demanda!\n");
				  exit(-1);
				}
				//Alocação do vetor de distancias
				distancia = malloc((quantCidades) * sizeof(float *));
				for (int i = 0; i < quantCidades; ++i){
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
			}else if (iLinha > 6 && iLinha <= 6+quantCidades){
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
			}else if (iLinha > (7+quantCidades) && iLinha <= (7+quantCidades*2)){
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
	int minimo = ceil((float)demandaTotal/(float)capacidade);
	printf("Minimo de Veículos: %d \n", minimo);
	int quantRotas = quantCidades+minimo;
	//Alocação do vetor das Rotas
	rotas = malloc((quantRotas) * sizeof(int));
	if (rotas == NULL) {
	  printf( "Erro Malloc Rotas!\n");
	  exit(-1);
	}


	//Gera a "matriz" com as distâncias
	calcDistancia(quantCidades, cidadeX, cidadeY, distancia);

	int x[] = {0, 21, 31, 19, 17, 13, 7, 26, 0, 12, 1, 16, 30, 0, 27, 24, 0, 29, 18, 8, 9, 22, 15, 10, 25, 5, 20, 0, 14, 28, 11, 4, 23, 3, 2, 6, 0};
	//int x[] = {0, 17, 20, 18, 15, 12, 0, 16, 19, 21, 14, 0, 13, 11, 4, 3, 8, 10, 0, 9, 7, 5, 2, 1, 6, 0};
 	printf("\n\nArquivo\n");
 	imprime(x, quantRotas, cidadeD);
	printf("\nResposta Arquivo: %f\n", calcCusto(x, distancia, quantRotas) );
	//printf("\n %f \n", distancia[20][17] + distancia[20][18] + distancia[18][15] + distancia[15][12] + distancia[19][16] + distancia[21][19] + distancia [21][14] + distancia[13][11] + distancia[11][4] + distancia[4][3] + distancia[8][3] + distancia[10][8] + distancia[9][7] + distancia[7][5] + distancia[5][2] + distancia[2][1] + distancia[6][1] + distancia[17][0] + distancia[12][0] + distancia[16][0] + distancia[14][0] + distancia[13][0] + distancia[10][0] + distancia[9][0] + distancia[6][0]);



	//Alocação do vetor das Rotas
	novasRotas = malloc((quantRotas) * sizeof(int));
	if (novasRotas == NULL) {
	  printf( "Erro Malloc novasRotas!\n");
	  exit(-1);
	}


	solucaoInicial(distancia, quantCidades, capacidade, cidadeD, rotas);
	imprime(rotas, quantRotas, cidadeD);
	printf("\nCost %f \n", calcCusto(rotas, distancia, quantRotas));
	rotas = ils(distancia, quantCidades, capacidade, cidadeD, rotas, quantRotas);	 
	for (int i = 0; i < 10000; i++){
		novasRotas = perturbacao(distancia, quantCidades, capacidade, cidadeD, rotas, quantRotas);
	 	//imprime(novasRotas, quantRotas, cidadeD);
	 	//printf("\nCost %f \n", calcCusto(novasRotas, distancia, quantRotas));
		novasRotas = ils(distancia, quantCidades, capacidade, cidadeD, novasRotas, quantRotas);
	 	//imprime(novasRotas, quantRotas, cidadeD);
	 	//printf("\nCost %f \n", calcCusto(novasRotas, distancia, quantRotas));	 	
		rotas = criterioDeAceitacao(rotas, novasRotas, distancia, quantRotas);
	}
	printf("\nFinal\n");
	imprime(rotas, quantRotas, cidadeD);
	printf("\nCost %f \n", calcCusto(rotas, distancia, quantRotas));

	/*
	s = solucaoInicial(S);
	s1 = ILS(s);
	while(){
		p = perturbacao(s1);
		p1 = ILS(p1); //2-OPT no ciclo 0-0
		s1 = criterioDeAceitacao(s1, p1);
	}
	*/

	free(cidadeX);
	free(cidadeY);
	free(cidadeD);
	free(distancia);

	return 0;
}