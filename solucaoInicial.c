/*
 * Solução Inicial utilizando o vizinho mais próximo.
 */
void solucaoInicial(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas, int depositoCentral){
	int *cidades, cidadeAtual = 0, proxCidade, i, j, aux, newDemanda, demanda, demandaTotal = 0, index = 1, w = 0;
	float custo = 0, proxCusto;
	/*
	 * Alocação do vetor que irá conter todas cidades do problema.
	 */
	cidades = malloc((quantCidade-1) * sizeof(int));
	if (cidades == NULL) {
	  printf( "Erro Malloc Cidade X!\n");
	  exit(-1);
	}
	/*
	 * Inserindo as cidades no vetor.
	 */
	#pragma acc kernels
	for (i = 0; i < quantCidade; i++){
		cidades[i] = i;
	}
	/*
	 * Inicio vizinho mais próximo.
	 * A primeira e ultima cidade da rota é o depositoCentral.
	 * O depositoCentral é o ponto onde inicia-se e termina-se a rota.
	 */
	rotas[0] = depositoCentral;
	while(quantCidade-1 != w){
		proxCusto = 0;
		custo = 0;
		demanda = 0;
		aux = 0;
		for (j = 0; j < quantCidade; j++){
			proxCidade = cidades[j];
			newDemanda = cidadeD[proxCidade];
			if(proxCidade != depositoCentral && demandaTotal+newDemanda < capacidade){
				/*
				 * Como distancia[i][j] é uma matriz triangular inferior 
				 * para encontrarmos a distância entre a cidadeAtual e a proxCidade
				 * o i da matriz sempre tem que ser maior que o j (i > j).
				 */
				if(cidadeAtual < proxCidade){
					proxCusto = distancia[proxCidade][cidadeAtual];
				}else{
					proxCusto = distancia[cidadeAtual][proxCidade];
				}
				/*
				 * Verificando para encontrar o vizinho de menor custo e que preencha mais o veículo.
				 */
				if ((proxCusto != 0) && (proxCusto < custo)){
					custo = proxCusto;
					aux = j;
					demanda = newDemanda;
				}else if (custo == 0 && proxCusto != 0){
					custo = proxCusto;
					aux = j;
					demanda = newDemanda;					
				}else if((proxCusto == custo) && (demanda < newDemanda)){
					custo = proxCusto;
					aux = j;
					demanda = newDemanda;	
				}
			}
		}
		/*
		 * Verificando se a soma da demanda do veículo +
		 * a demanda do vizinho mais próximo (cidade)
		 * não ultrapassam a capacidade do veículo.
		 */
		if (demandaTotal+demanda < capacidade && demanda != 0){
  			/*
  			 * Somando a nova demanda a demandaTotal da rota.
  			 * Adicionando uma nova cidade a rota.
  			 */
			demandaTotal += demanda;
			rotas[index] = cidades[aux];
			index++;
			cidadeAtual = cidades[aux];
			cidades[aux] = depositoCentral;
  			w++;
  		}else{
  			/*
  			 * Terminando a rota e iniciando uma nova rota.
  			 */
			rotas[index] = depositoCentral;
			index++;
			demandaTotal = 0;
			cidadeAtual = 0;
		}	
	}
	/*
	 * Terminando a rota.
	 */
	rotas[index] = depositoCentral;
}