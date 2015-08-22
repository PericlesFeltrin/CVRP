void distancia(int cidades, int *cidadeX, int *cidadeY, float **rota){
//float distancia(int xa, int ya, int xb, int yb){
	//return sqrt(fabs( pow((xb - xa), 2.0) + pow((yb - ya), 2.0)));
	for (int i = 1; i < cidades; ++i){
		for (int x = 0; x < i; ++x){
			rota[i][x] = sqrt(pow((cidadeX[i] - cidadeX[x]), 2.0) + pow((cidadeY[i] - cidadeY[x]), 2.0));
			printf("%f ", rota[i][x]);
		}
		printf("\n");
	}
//	return sqrt(pow((xb - xa), 2.0) + pow((yb - ya), 2.0));
}