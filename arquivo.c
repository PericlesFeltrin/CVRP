void arquivo(char arq[50]){
	int tamLinha = 2000000, i ; 
	char linha[tamLinha];
	char *token;
	FILE *arquivo;
	//Nome do Arquivo
	arquivo = fopen(arq, "r");
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