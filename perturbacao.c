/*
 * Perturbação realizada por trocas.
 */
int* perturbacao(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas, int quantRotas, int depositoCentral){
	int *novasRotas, i, a, b, aux, capacidadeRota;
	float custoRota;
	/*
	 * Alocação do vetor que irá conter a resposta (novasRotas) do problema.
	 */
	novasRotas = malloc((quantRotas) * sizeof(int));
	if (novasRotas == NULL) {
	  printf( "Erro Malloc novasRotas!\n");
	  exit(-1);
	}
	/*
	 * Cópia da solução final para uma solução provisória.
	 */
	for (i = 0; i < quantRotas; ++i){
		novasRotas[i] = rotas[i];
	}
	/*
	 * Cálculo do custo da solução final (rotas).
	 */
	custoRota = calcCusto(rotas, distancia, quantRotas);
	/*
	 * Inicio perturbação.
	 */
	for (a = 1; a < quantRotas-1; a++){
		for (b = a+1; b < quantRotas-1; b++){
			/*
			 * Realiza a troca entre duas cidades.
			 */
			aux = novasRotas[a];
			novasRotas[a] = novasRotas[b];
			novasRotas[b] = aux;
			/*
			 * Verifica se houve redução de custo final com a troca.
			 */
			if (custoRota > calcCusto(novasRotas, distancia, quantRotas)){
				capacidadeRota = 0;
				/*
				 * Realiza o cálculo para verificar se não foi ultrapassado a capacidade de cada veículo.
				 */
				for (i = 0; i < quantRotas; i++){
					if (novasRotas[i] != depositoCentral ){
						capacidadeRota += cidadeD[novasRotas[i]];
					}else{
						capacidadeRota = 0;
					}
					/*
					 * Se a capacidade da do veículo for ultrapassada.
					 */
					if (capacidadeRota > capacidade){
						capacidadeRota = -1;
						break;
					}
				}
				/*
				 * Se capacidadeRota = 0 então nenhuma rota ultrapassou a capacidade do veículo.
				 * Se capacidadeRota = -1 então alguma rota ultrapassou a capacidade do veículo 
				 * e deve ser retornada as cidades para a posição inicial no vetor da solução final (novasRotas).
				 */
				if(capacidadeRota == 0){
					/*
					 * Atualizando o valor do custoRota para o nova solução encontrada.
					 */
					custoRota = calcCusto(novasRotas, distancia, quantRotas);
				}else{
					/*
					 * Retornando as cidades para a posição original
					 * pois alguma rota ultrapassou a capacidade do veículo.
					 */
					aux = novasRotas[b];
					novasRotas[b] = novasRotas[a];
					novasRotas[a] = aux;
				}
			}else{
				/*
				 * Retornando as cidades para a posição original
				 * pois o novo custo é maior que o custo anterior.
				 */
				aux = novasRotas[b];
				novasRotas[b] = novasRotas[a];
				novasRotas[a] = aux;
			}
		}
	}
	return novasRotas;
}