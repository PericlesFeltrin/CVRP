int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

void solucaoInicial(float **distancia, int quantCidade, int capacidade){
	int cidades[quantCidade];
	int cidadeAtual = 0, proxCidade, i, j, aux;
	float custo = 0, custoFinal = 0, newCusto;

	for (i = 1; i < quantCidade; i++){
		cidades[i-1] = i;
	}

	aux = (int)NULL;
	while(cidades[quantCidade-1] != 0){
		newCusto = 0;
		custo = 0;
		for (j = 0; j < i-1; j++){
			if(cidades[j] != 0){
				proxCidade = cidades[j];
				if(cidadeAtual < proxCidade){
					newCusto = distancia[proxCidade][cidadeAtual];
				}else{
					newCusto = distancia[cidadeAtual][proxCidade];
				}
				
				if ((newCusto != 0) && (newCusto < custo)){
					custo = newCusto;
					aux = j;
				}else if (custo == 0 && newCusto != 0){
					custo = newCusto;
					aux = j;
				}
			}
		}

		if (custoFinal+custo < capacidade && custo != 0){
			custoFinal += custo;
			printf("Foi %d \n", cidades[aux]);
			cidades[aux] = (int)NULL;
  			qsort (cidades, quantCidade-1, sizeof(int), compare);
		}else{
			custoFinal += custo;
			printf("Custo %f \n",custoFinal);
			custoFinal = 0;
		}
		i--;
	}
	printf("Custo %f \n",custoFinal);
}