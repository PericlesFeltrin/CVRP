void calcDistancia(int cidades, int *cidadeX, int *cidadeY, float **distancia){
	for (int i = 1; i < cidades; ++i){
		for (int x = 0; x < i; ++x){
			distancia[i][x] = sqrt(pow((cidadeX[i] - cidadeX[x]), 2) + pow((cidadeY[i] - cidadeY[x]), 2));
			//printf("%.2f ", distancia[i][x]);
		}
	//	printf("\n");
	}
}