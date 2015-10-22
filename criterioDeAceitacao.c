//Markovin
int * criterioDeAceitacao(int *rotasA, int *rotasB, float **distancia, int quantRotas){
	if (calcCusto(rotasA, distancia, quantRotas) < calcCusto(rotasB, distancia, quantRotas)){
		return rotasA;
	}
	return rotasB;
}