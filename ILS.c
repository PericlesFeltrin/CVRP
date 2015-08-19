#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "arquivo.c"
/*

#include<solucaoInicial.c>
#include<ILS.c>
#include<perturbacao.c>
#include<criterioDeAceitacao.c>

*/

int main(int argc, char const *argv[]){
	int *cidadeX, *cidadeY, *cidadeD;
	char arq[50];
	/*
	printf("Arquivo: ");
	gets(arq);
	//Abre o arquivo
	arquivo(arq, cidadeX, cidadeY, cidadeD);
	*/
	arquivo("A-n32-k5.vrp", cidadeX, cidadeY, cidadeD);
	/*
	s = solucaoInicial(S);
	s1 = ILS(s);
	while(){
		p = perturbacao(s1);
		p1 = ILS(p1);
		s1 = criterioDeAceitacao(s1, p1);
	}
	*/
	return 0;
}