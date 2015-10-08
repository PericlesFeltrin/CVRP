void imprime(int *rotas, int quantRotas, int *cidadeD){
 	int y = 1, i=0;
 	int demanda = 0;
 	printf("Route #1: ");
 	printf("%d ", rotas[i]);
 	for (i = 1; i < quantRotas-1; ++i){
 		if(rotas[i] != 0){
 			printf("%d ", rotas[i]);
 			demanda += cidadeD[rotas[i]];
 		}else{
 			y++;
 			printf(" - Demanda: %d\nRoute #%d: ",demanda, y);
 			printf("%d ", rotas[i]);
 			demanda = 0;
 		}
 	}
 	printf(" - Demanda: %d",demanda);
}