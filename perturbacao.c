
int* perturbacao(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas, int quantRotas){
	int *novasRotas, i, a, b, aux, capacidadeRota;
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
	//printf("\nPerturbacao\n");

	for (a = 1; a < quantRotas-1; a++){
		//if(novasRotas[a] != 0){
			for (b = a+1; b < quantRotas-1; b++){
				//if(novasRotas[b] != 0){
					aux = novasRotas[a];
					novasRotas[a] = novasRotas[b];
					novasRotas[b] = aux;

					//Verificar Capacidade
					if (custoRota > calcCusto(novasRotas, distancia, quantRotas)){
						capacidadeRota = 0;
						for (i = 1; i < quantRotas; i++){
							if (novasRotas[i] != 0 ){
								capacidadeRota += cidadeD[novasRotas[i]];
							}else{
								capacidadeRota = 0;
							}

							if (capacidadeRota > capacidade){
								capacidadeRota = -1;
								break;
							}else if (novasRotas[i] == 0 ){
								capacidadeRota = 0;
							}
						}
						if(capacidadeRota == 0){
							custoRota = calcCusto(novasRotas, distancia, quantRotas);
						}else{
							aux = novasRotas[b];
							novasRotas[b] = novasRotas[a];
							novasRotas[a] = aux;
						}
					}else{
						aux = novasRotas[b];
						novasRotas[b] = novasRotas[a];
						novasRotas[a] = aux;
					}
				//}
			}
		//}
	}

	return novasRotas;
}