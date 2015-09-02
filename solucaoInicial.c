int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

void solucaoInicial(float **distancia, int quantCidade, int capacidade, int *cidadeD){
	int *cidades;
	int cidadeAtual = 0, proxCidade, i, j, aux, newDemanda, demanda, demandaTotal = 0;
	float custo = 0, custoFinal = 0, newCusto;


	cidades = malloc((quantCidade-1) * sizeof(int));
	if (cidades == NULL) {
	  printf( "Erro Malloc Cidade X!\n");
	  exit(-1);
	}
	printf("\nSolucao Inicial\n\n");
	
	for (i = 0; i < quantCidade; i++){
		cidades[i] = i;
	}

	i = 1;
	printf("Route #%d: ",i);
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
					if (demanda < newDemanda){
						custo = newCusto;
						aux = j;
						demanda = newDemanda;	
					}
				}
			}
		}

		if (demandaTotal+demanda < capacidade && demanda != 0){
			custoFinal += custo;
			demandaTotal += demanda;
			printf("%d ", cidades[aux]);
			cidades[aux] = 0;
  			qsort (cidades, quantCidade, sizeof(int), compare);
		}else{
			//printf("\nDemanda %d - %f \n", demandaTotal, custoFinal);
			i++;
			printf("\nRoute #%d: ",i);
			//custoFinal = 0;
			demandaTotal = 0;
		}	
	}
	printf("\nCost %f \n", custoFinal);
}