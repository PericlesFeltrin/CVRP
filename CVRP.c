#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <sys/time.h>
/*
 * Funções utilizadas durante o código.
 * O nome do arquivo é o mesmo nome da função.
 */
#include "calcDistancia.c"
#include "calcCusto.c"
#include "solucaoInicial.c"
#include "criterioDeAceitacao.c"
#include "perturbacao.c"
#include "imprime.c"
#include "buscaLocal.c"

int main(int argc, char* argv[]){
	int *cidadeX, *cidadeY, *cidadeD, *rotas, *novasRotas, demandaTotal = 0, capacidade, quantCidades, depositoCentral;
	int tamLinha = 100, iLinha = 0, i;
	float **distancia;
	char arq[50];
	char linha[tamLinha];
	char *token;
	FILE *arquivo;
	struct timeval tpI, tpF;
    int sec, usec;
/*
 * INICIO LEITURA DO ARQUIVO
 */
 	printf("Arquivos disponiveis: \n");
 	system("ls A-VRP/");
 	printf("\nEx.: A-VRP/A-n32-k5.vrp\n\n");
	printf("Arquivo: ");
	scanf("%s", arq);
	arquivo = fopen(arq, "r");
	/*
	 * Pode-se utilizar a entrada de dados estática.
	 * arquivo = fopen("A-VRP/A-n32-k5.vrp", "r");
	 * arquivo = fopen("A-VRP/A-n44-k7.vrp", "r");
	 * arquivo = fopen("A-VRP/A-n53-k7.vrp", "r");
	 * arquivo = fopen("A-VRP/A-n63-k9.vrp", "r");
	 * arquivo = fopen("A-VRP/A-n80-k10.vrp", "r");
	 * arquivo = fopen("A-VRP/X-n1001-k43.vrp", "r");
	 */
	/*
	 * Tempo Inicial
	 */
	gettimeofday(&tpI,NULL);
	if(arquivo == NULL){
		printf("Erro, nao foi possivel abrir o arquivo. \n");
	}else{
		while(!feof(arquivo)){
			fgets(linha, tamLinha , arquivo);
			if (iLinha == 3){ 
				/*
 				 * Encontrado a quantidade de cidades/instancias no arquivo
				 */
				token = strtok(linha," ");
				token = strtok (NULL, " ");
				token = strtok (NULL, " ");
				quantCidades = atoi(token);
				printf("Quantidade de Cidades: %d \n", quantCidades);
				/*
				 * Alocação do vetor que irá conter o ponto x de cada cidade.  
				 */
				cidadeX = malloc((quantCidades) * sizeof(int));
				if (cidadeX == NULL) {
				  printf( "Erro Malloc Cidade X!\n");
				  exit(-1);
				}
				/*
				 * Alocação do vetor que irá conter o ponto y de cada cidade.  
				 */
				cidadeY = malloc((quantCidades) * sizeof(int));
				if (cidadeY == NULL) {
				  printf( "Erro Malloc Cidade Y!\n");
				  exit(-1);
				}
				/*
				 * Alocação do vetor que irá conter a demanda de cada cidade.  
				 */
				cidadeD = malloc((quantCidades) * sizeof(int));
				if (cidadeD == NULL) {
				  printf( "Erro Malloc Demanda!\n");
				  exit(-1);
				}
				/*
				 * Alocação da matriz triangular inferior de distancias.  
				 */
				distancia = malloc((quantCidades) * sizeof(float *));
				#pragma acc kernels
				for (i = 0; i < quantCidades; ++i){
					distancia[i] = malloc((i) * sizeof(float *));
				}
				if (distancia == NULL) {
				  printf( "Erro Malloc distancia!\n");
				  exit(-1);
				}
			}else if (iLinha == 5){ 
				/*
 				 * Encontrado a capacidade de cada veículo no arquivo
				 */
				token = strtok(linha," ");
				token = strtok (NULL, " ");
				token = strtok (NULL, " ");
				capacidade = atoi(token);
				printf("Capacidade: %d \n", capacidade);
			}else if (iLinha > 6 && iLinha <= 6+quantCidades){
				/*
 				 * Encontrado a cidade com seu respectivo ponto x e y no plano.
				 */
				int cidade;
				/*
				 * Encontrada a cidade.  
				 */
				token = strtok(linha," ");
				cidade = atoi(token);
				/*
				 * Encontrado o ponto x.  
				 */
				token = strtok (NULL, " ");
				cidadeX[cidade - 1] = atoi(token);
				/*
				 * Encontrado o ponto y.  
				 */
				token = strtok (NULL, " ");
				cidadeY[cidade - 1] = atoi(token);
			}else if (iLinha > (7+quantCidades) && iLinha <= (7+quantCidades*2)){
				/*
 				 * Encontrado a cidade com a sua respectiva demanda.
				 */
				int cidade;
				/*
				 * Encontrada a cidade.  
				 */
				token = strtok(linha," ");
				cidade = atoi(token);
				/*
				 * Encontrada a demanda.  
				 */
				token = strtok (NULL, " ");
				cidadeD[cidade - 1] = atoi(token);
				/* 
				 * Soma-se essa demanda na demanta total do problema.
				 */
				demandaTotal += atoi(token);
			}else if ( iLinha == (7+quantCidades*2+2)){
				/*
				 * Encontrado a cidade que é o depósito central do problema.  
				 */
				token = strtok(linha," ");
				depositoCentral = atoi(token)-1;
				printf("Deposito Central: %d\n",depositoCentral);
				break;
			}
			iLinha++;
		}
	}	
	fclose(arquivo);
/*
 * FIM LEITURA DO ARQUIVO
 */
	printf("Demanda Total: %d \n",demandaTotal);
	/*
	 * Cálculo que irá definir o mínimo de rotas necessárias para resolver o problema.
	 */
	int minimo = ceil((float)demandaTotal/(float)capacidade);
	printf("Minimo de Veículos: %d \n", minimo);
	/*
	 * Cálculo que irá definir o tamanho do vetor que irá armazenar a resposta (rotas) 
	 */
	int quantRotas = quantCidades+minimo;
	double valor, inteiro, fracionario;
	valor = (double)demandaTotal/(double)capacidade;
	fracionario = modf(valor , &inteiro);
	if(fracionario > 0.50){
		quantRotas +=1;
	}
	/*
	 * Alocação do vetor que irá conter a resposta (rotas) do problema.
	 */
	rotas = malloc((quantRotas) * sizeof(int));
	if (rotas == NULL) {
	  printf( "Erro Malloc Rotas!\n");
	  exit(-1);
	}
	/*
	 * Chamada ao cálculo que irá preencher a matris triangular inferior.
	 */
	calcDistancia(quantCidades, cidadeX, cidadeY, distancia);
	/*
	 * Alocação do vetor que irá conter a resposta (novasRotas) do problema.
	 */
	novasRotas = malloc((quantRotas) * sizeof(int));
	if (novasRotas == NULL) {
	  printf( "Erro Malloc novasRotas!\n");
	  exit(-1);
	}
	float newCost = 0, oldCoast = 0;
	/*
	 * Geração da solução inicial.
	 */
	solucaoInicial(distancia, quantCidades, capacidade, cidadeD, rotas, depositoCentral);
	/*
	 * Se quiser visualizar a solução incial encontrada é só descomentar as próximas duas linhas de código.
	 * imprime(rotas, quantRotas, cidadeD);
	 * printf("\nCost %f \n", calcCusto(rotas, distancia, quantRotas));
	 */
	/*
	 * Cálculo do custo da solução encontrada e armazenada na variável rotas.
	 */
	newCost = calcCusto(rotas, distancia, quantRotas);
	/*
	 * Aplica-se a busca local na variável rotas.
	 */
	rotas = buscaLocal(distancia, quantCidades, capacidade, cidadeD, rotas, quantRotas, depositoCentral);	 
	while(newCost != oldCoast){
		/*
		 * Atualizando variável para critério de parada.
		 */
		oldCoast = newCost;
		/*
		 * Aplica-se a perturbação na variável rotas.
		 */
		novasRotas = perturbacao(distancia, quantCidades, capacidade, cidadeD, rotas, quantRotas, depositoCentral);
		/*
		 * Aplica-se a busca local na variável novasRotas.
		 */
		novasRotas = buscaLocal(distancia, quantCidades, capacidade, cidadeD, novasRotas, quantRotas, depositoCentral);
		/*
		 * Aplica-se o critério de aceitação nas variáveis rotas e novasRotas.
		 */
		rotas = criterioDeAceitacao(rotas, novasRotas, distancia, quantRotas);
		/*
		 * Cálculo do custo da solução encontrada e armazenada na variável rotas.
		 */
		newCost = calcCusto(rotas, distancia, quantRotas);
	}
	/*
	 * Imprime resultado final, suas rotas e seu custo total.
	 */
	printf("\nResultado Final\n");
	imprime(rotas, quantRotas, cidadeD);
	printf("\nCost %f \n", calcCusto(rotas, distancia, quantRotas));
	/*
	 * Tempo Final
	 */
	gettimeofday(&tpF, NULL);
	sec = tpF.tv_sec - tpI.tv_sec;
	usec = tpF.tv_usec - tpI.tv_usec;
    if (usec<0){
    	usec += 1000000L;
    	sec -= 1;
	}
    printf("Tempo: %d s %d us\n", sec, usec);
	free(cidadeX);
	free(cidadeY);
	free(cidadeD);
	free(distancia);
	return 0;
}