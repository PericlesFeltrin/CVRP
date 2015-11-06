/*
 * Critério de Aceitação de Markovin
 */
int * criterioDeAceitacao(int *rotasA, int *rotasB, float **distancia, int quantRotas){
	/*
	 * Compara-se o custoTotal da rotaA encotrada o problema
	 * com o custoTotal da rotaB encontrada para o problema
	 * retornando a rota de menor custo.
	 */
	if (calcCusto(rotasA, distancia, quantRotas) < calcCusto(rotasB, distancia, quantRotas)){
		return rotasA;
	}
	return rotasB;
}