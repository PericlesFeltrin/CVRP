int arquivo(char arq[50], int *cidadeX, int *cidadeY, int *cidadeD){
	int tamLinha = 100, iLinha = 0, cidades, capacidade; //, demandaTotal = 0 
	char linha[tamLinha];
	char *token;
	FILE *arquivo;
	float x;
	//Nome do Arquivo
	arquivo = fopen(arq, "r");
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
				//demandaTotal += atoi(token);
			}
			iLinha++;
		}
	}	
	fclose(arquivo);
	return capacidade;
}