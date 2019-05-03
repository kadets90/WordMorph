
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"wordmorph.h"
#include"matriz.h"
#include"ficheiros.h"


/******************************************************************************
 *  criar_matriz()
 *
 * Arguments: position - ponteiro para a matriz de posiçoes
 *            num_pal - ponteiro para o vetor de numero de palavras de cada
 *                      tamanho
 * Returns: (void)
 * Side-Effects: aloca memoria para uma tabela de inteiros de tamanho variavel
 *
 * Description: alocaçao de espaço para uma tabela de inteiros de tamanho
 *              variavel e inicianizaa tabela
 *
 *****************************************************************************/


void criar_matriz(int** position, int* num_pal){

  int x, y, i;

  for(i=0; i<STR_SIZE; ++i){

    position[i]=(int*)malloc(sizeof(int)*num_pal[i]);
    if(position[i]==NULL){
      printf("Erro na criaçao da tabela de posicao!\n");
      exit(1);
    }

  }

  /*inicializaçao da tabela*/
  for(x=0; x<STR_SIZE; ++x){
    for(y=0; y<num_pal[x]; ++y){
      position[x][y]=y;
    }
  }

}


/******************************************************************************
 *  criar_matriz_2()
 *
 * Arguments: tabela - ponteiro para tabela de palavras
 *            lim - limite de iteraçoes do ciclo
 *            size - tamanho da string a ser alocada
 * Returns: (void)
 * Side-Effects: alocaçao de espaço para uma tabela de palavras de tamanho
 *               unico
 *
 * Description: aloca memoria para uma tabela de palvras de tamanho unico
 *
 *****************************************************************************/


void criar_matriz_2(char** tabela, int lim, int size){

  int i;

  for(i=0; i<lim; ++i){

    tabela[i]=(char*)malloc(sizeof(char)*(size+1));
    if(tabela[i]==NULL){
      printf("Erro na criaçao da tabela!\n");
      exit(1);
    }

  }

}


/******************************************************************************
 *  criar_matriz_3()
 *
 * Arguments: num_pal - vetor de inteiros com o numero de palavras por tamanho
 *            palavras - ponteiro para matriz com palavras seperadas por
 *                       tamanhos
 * Returns: (void)
 * Side-Effects: alocaçao de espaço para varias tabelas de palavras
 *
 * Description: aloca memoria para varias tabelas de palavras
 *
 *****************************************************************************/


void criar_matriz_3(char*** palavras, int* num_pal){

  int i;

  for(i=0; i<STR_SIZE; ++i){
    
    palavras[i]=(char**)malloc(sizeof(char*)*num_pal[i]);
    if(palavras[i]==NULL){
      printf("Erro na criacao da matriz! (Parte 2)\n");
      exit(1);
    }

    criar_matriz_2(palavras[i], num_pal[i], i);
  }

}


/******************************************************************************
 *  prencher_matriz()
 *
 * Arguments: palavras - ponteiro para matriz com palavras seperadas por
 *                       tamanhos
 *            nome - nome do ficheiro dicionario a utilizar
 *            
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: preenche a matriz de palavras com as palavras contidas no
 *              dicionario
 *
 *****************************************************************************/


void prencher_matriz(char*** palavras, char* nome){

  FILE* fp;
  char aux[STR_SIZE];
  /*vetor auxiliar a 0's para preenchimento da matriz*/
  int num_pal_cpy[STR_SIZE]={0};

  /*abertura do ficheiro dicionario*/
  fp=abre_ficheiro(nome, "r");

  while(fscanf(fp, "%s", aux)==1){
    strcpy(palavras[strlen(aux)][num_pal_cpy[strlen(aux)]++],aux);
  }

  fclose(fp);
}


/******************************************************************************
 *  free_matriz_2()
 *
 * Arguments: vetor - tabela de palavras de tamanho unico
 *            lim - limite iteraçoes do ciclo
 * Returns: (void)
 * Side-Effects: memoria alocada pelo vetor é libertada
 *
 * Description: liberta a memoria ocupada pela tabela de palavras
 *
 *****************************************************************************/


void free_matriz_2(void** vetor, int lim){

  int x;

  for(x=0; x<lim; ++x){
    free(vetor[x]);
  }

}


/******************************************************************************
 *  free_matriz_3()
 *
 * Arguments:  num_pal - vetor de inteiros com o numero de palavras por tamanho
 *             matriz - ponteiro para matriz com palavras seperadas por
 *                      tamanhos 
 * Returns: (void)
 * Side-Effects: memoria alocada pela matriz é libertada
 *
 * Description: liberta a memoria alocada pelas tabelas de palvras
 *
 *****************************************************************************/


void free_matriz_3(char*** palavras, int* num_pal){

  int x;

  for(x=0; x<STR_SIZE; ++x){
      free_matriz_2((void**)palavras[x], num_pal[x]);
      free(palavras[x]);
  }

}
