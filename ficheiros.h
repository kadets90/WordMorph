
#ifndef ficheiros

#define INPUT_EXTENSION 4

/*verifica se os ficheiros de input sao do formato pretendido*/
void verifica_inputs(int , char **);
/*funçao que seleciona qual a extensao pretendida e mensagem de
 *erro a ser mostrada em caso de erro*/
void sele_str(char **, int );
/*contagem de palavras por tamanhos*/
void numero_pal(FILE *, int*);
/*Abre um ficheiro*/
FILE* abre_ficheiro(char*, char*);
/*criaçao de um ficheiro com extensao ".stat" onde serao
 *escritos os resultados*/
FILE* cria_ficheiro(char*);
/*escreve as respostas aos problemas num ficheiro de saida*/
void escreve_ficheiro(solucao*, int, char*);

#endif
