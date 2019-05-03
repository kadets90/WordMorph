
#ifndef functional

#define INFINITO 2000000
#define P (pesos[v] + (aux_est->peso))

/*alocaçao de espaço para as varias tabelas da estrutura 
 *dicionario (numero de palavras por tamanho, vetor que separa
 *o dicionario por tamanhos, posiçao das palavras, vetor de 
 *ordenaçao)*/
dicionario* create_dic(void);
/*cria e preenche as matriz dicionario e a matriz de posiçoes*/
void start_dic(dicionario*, char**);
/*aloca e preenche a lista com os problemas a resolver*/
Item guardar_prob(Item, FILE*, int*, int*);
/*alocaçao de memoria e inicializaçao de todos os parametros que 
 *compoem o grafo*/
Item* criar_tabela_adj(Item*, int, int, char**);
/*aloca memoria e inicializa os valores da aresta do grafo*/
Item init_aresta(int, int);
/*compara as duas palavras recebidas como argumentos caracter 
 *a caracter e retorna o numeor de caracteres diferentes*/
int cmp_char(char*, char*, int);
/*cria uma tabela com os valores dos preços da mutaçao de uma
 *palavra para uma sua adjacente*/
int* vetor_num(int);
/*encontra e regista os caminhos mais curtos ate uma raiz
 *defenida a partir de pesos e de uma fila de prioridade*/
void achar_caminho(Item*, int, int, int*, int*, int, int);
/*aloca e preenche uma tabela com as soluçoes aos problemas*/
solucao guardar_sol(int, int, int*, int*, char**);
/*liberta a memoria alocada para a estrutura problema e dos seus
 *respetivos campos*/
void free_prob(Item);
/*liberta a memoria alocada para as varias listas que compoem o
 *grafo e a tabela de ponteiros para as varias listas*/
void free_tab_adj(Item*, int);
/*liberta a memoria alocada para uma aresta*/
void free_adj(Item);
/*liberta a memoria da tabela de listas de soluçoes*/
void free_sol(solucao*, int);
/*funçao vazia*/
void free_sol_est();

#endif
