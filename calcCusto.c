/*
 * Cálculo do custo total das rotas encontradas.
 */
float calcCusto(int *rotas, float **distancia, int quantRotas){
	float custoTotal = 0;
	int cidadeAtual, proxCidade, i;
	
	#pragma acc kernels reduction(+:custoTotal)
	for (i = 1; i < quantRotas; i++){
		/*
 		 * cidadeAtual é a cidade em que o veículo esta na rota.
 		 * proxCidade é a próxima cidade que o veículo irá visitar na rota.
         */
		cidadeAtual = rotas[i-1];
		proxCidade = rotas[i];
		/*
		 * Como distancia[i][j] é uma matriz triangular inferior 
		 * para encontrarmos a distância entre a cidadeAtual e a proxCidade
		 * o i da matriz sempre tem que ser maior que o j (i > j).
		 * custoTotal é uma variável que irá armazenar o custo total
		 * de todas as rotas para o problema.
		 */
		if(cidadeAtual < proxCidade){
			custoTotal += distancia[proxCidade][cidadeAtual];
		}else{
			custoTotal += distancia[cidadeAtual][proxCidade];
		}
	}
	return custoTotal;
}