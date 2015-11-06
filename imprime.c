/*
 * Impressão na tela dos resultados obtidos.
 * Imprime no formado especificado pelo TSPLIB 95.
 */
void imprime(int *rotas, int quantRotas, int *cidadeD){
 	int y = 1, i=0;
 	int demanda = 0;
 	printf("Route #1: ");
 	/*
 	* Para vizualizar o depósito na impressão descomente.
 	* printf("%d ", rotas[i]);
 	*/
 	for (i = 1; i < quantRotas-1; ++i){
 		if(rotas[i] != 0){
 			printf("%d ", rotas[i]);
			demanda += cidadeD[rotas[i]];
 		}else{
 			y++;
 			demanda = 0;
		 	/*
		 	 * Para verificar a demanda da rota descomente.
 			 * printf(" - Demanda: %d", demanda);
 			 */
 			 printf("\nRoute #%d: ", y);
 			 /*
 			  * Para vizualizar o depósito na impressão descomente.
 			  * printf("%d ", rotas[i]);
 			  */
 		} 
 	}
 	/*
 	 * Para verificar a demanda da rota descomente.
 	 * printf(" - Demanda: %d",demanda);
	 */
}