/*
 * Busca Local baseada no 2-OPT.
 */
int* buscaLocal(float **distancia, int quantCidade, int capacidade, int *cidadeD, int *rotas, int quantRotas, int depositoCentral){
	int x, y, z, w, i, aux, *novasRotas;
	float custoRota;
	/*
	 * Alocação do vetor que irá conter a resposta (novasRotas) do problema.
	 */
	novasRotas = malloc((quantRotas) * sizeof(int));
	if (novasRotas == NULL) {
	  printf( "Erro Malloc novasRotas ILS!\n");
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
	 * Inicio 2-OPT
	 */
	for (x = 0; x < quantRotas-1; x++){
		if(rotas[x] == depositoCentral){
			for (y = x+1; rotas[y] != depositoCentral; y++){
				for (z = y+1; rotas[z] != depositoCentral; z++){
					/*
					 * Cruzando as cidades.
					 */
					for (i = y, w = z; i < w; i++, w--){
						aux = novasRotas[i];
						novasRotas[i] = novasRotas[w];
						novasRotas[w] = aux;
					}
					/*
					 * Verificando se houve redução no custo final.
					 */
					if (custoRota < calcCusto(novasRotas, distancia, quantRotas)){
						/*
						 * Desfazendo o cruzamento entre as cidades.
						 */
						for (i = y, w = z; i < w; i++, w--){
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