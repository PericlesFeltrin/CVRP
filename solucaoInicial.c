/*
 * Solução Inicial utilizando o vizinho mais próximo.
 */
void solucaoInicial(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas, int depositoCentral){
	int *cidades, cidadeAtual = 0, proxCidade, i, j, aux, newDemanda, demanda, demandaTotal = 0, index = 1, w = 0;
	float custo = 0, newCusto;
	
	cidades = malloc((quantCidade-1) * sizeof(int));
	if (cidades == NULL) {
	  printf( "Erro Malloc Cidade X!\n");
	  exit(-1);
	}

	#pragma acc kernels loop
	for (i = 0; i < quantCidade; i++){
		cidades[i] = i;
	}

	rotas[0] = depositoCentral;
	while(quantCidade-1 != w){
		newCusto = 0;
		custo = 0;
		demanda = 0;
		aux = 0;
		for (j = 0; j < quantCidade; j++){
			proxCidade = cidades[j];
			newDemanda = cidadeD[proxCidade];
			if(proxCidade != depositoCentral && demandaTotal+newDemanda < capacidade){
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
				}else if((newCusto == custo) && (demanda < newDemanda)){
						custo = newCusto;
						aux = j;
						demanda = newDemanda;	
				}
			}
		}

		if (demandaTotal+demanda < capacidade && demanda != 0){
			demandaTotal += demanda;
			rotas[index] = cidades[aux];
			index++;
			cidadeAtual = cidades[aux];
			cidades[aux] = depositoCentral;
			printf("%d \n", cidadeAtual);
  			w++;
  		}else{
			rotas[index] = depositoCentral;
			index++;
			demandaTotal = 0;
			cidadeAtual = 0;
		}	
	}
	rotas[index] = depositoCentral;
}