int* ils(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas, int quantRotas){
	int x, y, z, w, i, aux, *novasRotas;
	float custoRota;

	//Alocação do vetor das Rotas
	novasRotas = malloc((quantRotas) * sizeof(int));
	if (novasRotas == NULL) {
	  printf( "Erro Malloc novasRotas!\n");
	  exit(-1);
	}

	//copia vetor com as rotas
	for (i = 0; i < quantRotas; ++i){
		novasRotas[i] = rotas[i];
	}

	custoRota = calcCusto(rotas, distancia, quantRotas);
	//printf("\nILS\n");
	for (x = 0; x < quantRotas-1; x++){
		if(rotas[x] == 0){
			for (y = x+1; rotas[y] != 0; y++){
				for (z = y+1; rotas[z] != 0; z++){
					for (i = y, w = z; i < z; i++, w--){
						aux = novasRotas[i];
						novasRotas[i] = novasRotas[w];
						novasRotas[w] = aux;
					}
					if (custoRota < calcCusto(novasRotas, distancia, quantRotas)){
						for (i = y, w = z; i < z; i++, w--){
							aux = novasRotas[i];
							novasRotas[i] = novasRotas[w];
							novasRotas[w] = aux;
						}
					}
				}
			}
		}
	}

	return novasRotas;
}