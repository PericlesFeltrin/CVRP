float calcCusto(int *rotas, float **distancia, int quantRotas){
	//CUSTO FILNAL
	float result = 0;
	int cidadeAtual, proxCidade;
	cidadeAtual = rotas[0];
	for (int i = 1; i < quantRotas; ++i){
		//printf("%d ", cidadeAtual );
		proxCidade = rotas[i];
		if(cidadeAtual < proxCidade){
			result += distancia[proxCidade][cidadeAtual];
		}else{
			result += distancia[cidadeAtual][proxCidade];
		}
		cidadeAtual = proxCidade;
	}
//	printf("\n");
	return result;
}