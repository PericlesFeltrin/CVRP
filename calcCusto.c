float calcCusto(int *rotas, float **distancia, int quantRotas){
	//CUSTO FILNAL
	float result = 0;
	int cidadeAtual, proxCidade, i;
	
	//cidadeAtual = rotas[0];

	#pragma acc kernels loop
	for (i = 1; i < quantRotas; ++i){
		//printf("%d ", cidadeAtual );
		cidadeAtual = rotas[i-1];
		proxCidade = rotas[i];
		if(cidadeAtual < proxCidade){
			#pragma acc atomic update
			result += distancia[proxCidade][cidadeAtual];
		}else{
			#pragma acc atomic update
			result += distancia[cidadeAtual][proxCidade];
		}
		/*
		proxCidade = rotas[i];
		if(cidadeAtual < proxCidade){
			result += distancia[proxCidade][cidadeAtual];
		}else{
			result += distancia[cidadeAtual][proxCidade];
		}
		cidadeAtual = proxCidade;
		*/
	}
//	printf("\n");
	return result;
}