#include <stdio.h>
#include "arquivo.c"
/*

#include<solucaoInicial.c>
#include<ILS.c>
#include<perturbacao.c>
#include<criterioDeAceitacao.c>

*/

int main(int argc, char const *argv[]){
	char arq[50];
	printf("Arquivo: ");
	gets(arq);
	//Abre o arquivo
	arquivo(arq);
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