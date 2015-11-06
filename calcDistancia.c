/*
 * Cálculo da Distância Euclidiana.
 */
void calcDistancia(int quantCidades, int *cidadeX, int *cidadeY, float **distancia){
	int i, j;
	#pragma acc kernels loop
	for (i = 1; i < quantCidades; i++){
		for (j = 0; j < i; j++){
			/*
			 * Cálculo da Distância Euclidiana.
			 * Cálculo da cidade i até a cidade j.
			 * distancia[i][j] é uma matriz triangular inferior.
			 * cidadeX é um vetor que possue os pontos x das cidades (i e j) no plano.
			 * cidadeY é um vetor possue os pontos y das cidades (i e j) no plano.
			 */
			distancia[i][j] = sqrt(pow((cidadeX[i] - cidadeX[j]), 2) + pow((cidadeY[i] - cidadeY[j]), 2));
		}
	}
}