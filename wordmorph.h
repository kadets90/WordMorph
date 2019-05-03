
#ifndef wordmorph

#define Item void*
#define STR_SIZE 30
#define NO_WAY -1
#define exch(A, B) {int t = A; A = B; B = t; }
#define quadrado(A) A*A
#define YES 1


typedef struct{

  /*matriz de palavras (linhas separadas por tamanhos)*/
  char*** matriz;
  /*tabela com o numero de palavras de cada tamanho*/
  int* num_pal;
  /*matriz com os indices de cada palavra*/
  int** position;

}dicionario;

typedef struct{

  /*palavra de origem*/
  char* palavra1;
  /*palavra de destino*/
  char* palavra2;
  /*numero de mutaçoes maximas permitidas*/
  int mutacoes;

}problema;

typedef struct{

  /*indice da palavra no dicionario*/
  int position;
  /*peso da aresta*/
  int peso;

}aresta;

typedef struct{

  /*custo do caminho total*/
  int custo;
  /*lista com as palavras que compoem o caminho*/
  Item caminho;

}solucao;

#endif
