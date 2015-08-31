int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

void solucaoInicial(){
//(int *custoRota, int *index, int *vizinho, int inicial, int cidades, int caso){
	int custo, final, j, newCusto, aux;
	custo = (int)NULL;
	final = (int)NULL;
	aux = (int)NULL;
	for (j = 0; j < cidades; j++){
		newCusto = pesquisaRota(inicial, vizinho[j], custoRota, index);
		if ((newCusto != 0) && (newCusto < custo)){
			custo = newCusto;
			aux = j;
		}else if (newCusto != 0 && newCusto == custo && caso > 0){
			//rotaAlternativa(custoRota, index, vizinho, inicial, cidades, resposta);
			custo = newCusto;
			aux = j;
			caso--;
		}else if (custo == (int)NULL && newCusto != 0){
			custo = newCusto;
			aux = j;
		}
	}
	final = vizinho[aux];
	vizinho[aux] = vizinho[j-1];
	vizinho[j-1] = (int)NULL;
  	qsort (vizinho, cidades-1, sizeof(int), compare);
	return final;
}

}