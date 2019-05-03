
#ifndef matriz

/*alocaçao de espaço para uma tabela de inteiros de tamanho
 *variavel e inicianizaa tabela*/
void criar_matriz(int**, int*);
/*aloca memoria para uma tabela de palvras de tamanho unico*/
void criar_matriz_2(char**, int, int);
/*aloca memoria para varias tabelas de palavras*/
void criar_matriz_3(char***, int*);
/*preenche a matriz de palavras com as palavras contidas no
 *dicionario*/
void prencher_matriz(char***, char*);
/*liberta a memoria alocada pelas tabelas de palvras*/
void free_matriz_3(char***, int*);
/*liberta a memoria ocupada pela tabela de palavras*/
void free_matriz_2(void**, int);

#endif
