void arquivo(){
	int tamLinha = 2000000, i ; 
	char linha[tamLinha];
	char *token;
	FILE *arquivo;
	//Nome do Arquivo
	arquivo = fopen("A-n32-k5.vrp", "r");
	if(arquivo == NULL){
		printf("Erro, nao foi possivel abrir o arquivouivo. \n");
	}else{
		while(!feof(arquivo)){
			fgets(linha, tamLinha , arquivo);
			printf("%s", linha);
		}
	}	
	fclose(arquivo);
}