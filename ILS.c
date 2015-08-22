#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

//#include "arquivo.c"
#include "distancia.c"
/*

#include<solucaoInicial.c>
#include<ILS.c>
#include<perturbacao.c>
#include<criterioDeAceitacao.c>

*/

int main(int argc, char const *argv[]){
	int *cidadeX, *cidadeY, *cidadeD, demandaTotal = 0, capacidade, cidades;
	int tamLinha = 100, iLinha = 0;
	float **rota;
	char arq[50];
	char linha[tamLinha];
	char *token;
	FILE *arquivo;
	
	//printf("Arquivo: ");
	scanf("%s", arq);

	//Nome do Arquivo
	arquivo = fopen(arq, "r");
	//arquivo = fopen("A-n32-k5.vrp", "r");
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
				//Alocação do vetor de rotas
				rota = malloc((cidades) * sizeof(float *));
				for (int i = 0; i < cidades; ++i){
					rota[i] = malloc((i+1) * sizeof(float *));
				}
				if (rota == NULL) {
				  printf( "Erro Malloc Rota!\n");
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
	distancia(cidades, cidadeX, cidadeY, rota);

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
	free(rota);

	return 0;
}