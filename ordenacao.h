
#ifndef ordenacao

#define SORT_POINT 34

/*organizar e selecionar qual o melhor algoritmo para o fazer
 *para cada tabela*/
void organizar_tabelas(int, int*, char**);
/*organiza a tabela de palavras alfabeticamente*/
void quick_sort(int*, char**, int, int);
/*organiza a tabela de palavras alfabeticamente*/
void selection_sort(int, int*, char**);
/*encontra as palavras a trocar de posiçao por comparaçao com o
 *pivo*/
int partition(int*, char**, int, int);
/*procura uma palavra na tabela*/
int find_position(char*, int*, char**, int);

#endif
