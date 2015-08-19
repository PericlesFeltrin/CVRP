void arquivo(char arq[50], int *cidadeX, int *cidadeY, int *cidadeD){
	int tamLinha = 100, iLinha = 0, cidades, demanda = 0, capacidade; 
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
				cidadeX = malloc((cidades) * sizeof(int));
				cidadeY = malloc((cidades) * sizeof(int));
				cidadeD = malloc((cidades) * sizeof(int));
			}else if (iLinha == 5){ 
				//Capacidade
				token = strtok(linha," ");
				token = strtok (NULL, " ");
				token = strtok (NULL, " ");
				capacidade = atoi(token);
				printf("Capacidade: %d \n", capacidade);
			}else if (iLinha > 6 && iLinha <= 6+cidades){
				//Cidade X Y
				int cidade;
				token = strtok(linha," ");
				cidade = atoi(token);
				//printf("Cidade: %d ", atoi(token));
				token = strtok (NULL, " ");
				//printf("X: %d ", atoi(token));
				cidadeX[cidade - 1] = atoi(token);
				token = strtok (NULL, " ");
				//printf("Y: %d \n", atoi(token));
				cidadeY[cidade - 1] = atoi(token);
			}else if (iLinha > (7+cidades) && iLinha <= (7+cidades*2)){
				//Cidade Demanda
				int cidade;
				token = strtok(linha," ");
				cidade = atoi(token);
				//printf("Cidade: %s ", token);
				token = strtok (NULL, " ");
				//printf("Demanda: %s \n", token);
				cidadeD[cidade - 1] = atoi(token);
				demanda += atoi(token);
			}
			iLinha++;
		}
	}	
	fclose(arquivo);
	for (int i = 0; i < cidades; ++i){
		
		printf("X: %d ", cidadeX[i]);
		printf("Y: %d ", cidadeY[i]);
		printf("D: %d \n", cidadeD[i]);
	}
	printf("Demanda: %d \n", demanda );
	printf("Minimo de carros: %f  \n", ((float)demanda/(float)capacidade) );
}