int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

void solucaoInicial(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas){
	int *cidades, cidadeAtual = 0, proxCidade, i, j, aux, newDemanda, demanda, demandaTotal = 0, index = 1;
	float custo = 0, newCusto;
	
	cidades = malloc((quantCidade-1) * sizeof(int));
	if (cidades == NULL) {
	  printf( "Erro Malloc Cidade X!\n");
	  exit(-1);
	}
	printf("\nSolucao Inicial\n");
	
	for (i = 0; i < quantCidade; i++){
		cidades[i] = i;
	}

	rotas[0] = 0;
	aux = (int)NULL;
	while(cidades[quantCidade-1] != 0){
		newCusto = 0;
		custo = 0;
		demanda = 0;
		for (j = 0; j < quantCidade; j++){
			proxCidade = cidades[j];
			newDemanda = cidadeD[proxCidade];
			if(proxCidade != 0 && demandaTotal+newDemanda < capacidade){
				if(cidadeAtual < proxCidade){
					newCusto = distancia[proxCidade][cidadeAtual];
				}else{
					newCusto = distancia[cidadeAtual][proxCidade];
				}

				if ((newCusto != 0) && (newCusto < custo)){
					custo = newCusto;
					aux = j;
					demanda = newDemanda;
				}else if (custo == 0 && newCusto != 0){
					custo = newCusto;
					aux = j;
					demanda = newDemanda;					
				}else if(newCusto == custo){
					if (demanda > newDemanda){
						custo = newCusto;
						aux = j;
						demanda = newDemanda;	
					}
				}
			}
		}

		if (demandaTotal+demanda < capacidade && demanda != 0){
			demandaTotal += demanda;
			rotas[index] = cidades[aux];
			index++;
			cidadeAtual = cidades[aux];
			cidades[aux] = 0;
  			qsort (cidades, quantCidade, sizeof(int), compare);
		}else{
			rotas[index] = 0;
			index++;
			demandaTotal = 0;
			cidadeAtual = 0;
		}	
	}
	rotas[index] = 0;
}