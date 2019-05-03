
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include"wordmorph.h"
#include"ordenacao.h"


/******************************************************************************
 * quick_sort()
 *
 * Arguments: position - tabela de posiçoes das palavras
 *            palavras - tabela de palavras de tamanho unico 
 *            min - index minimo da tabela pretendido
 *            max - index maximo da tabela pretendido
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: organiza a tabela de palavras alfabeticamente
 *
 *****************************************************************************/


void quick_sort(int* position, char** palavras, int min, int max){

  int i;

  if(max<=min) return;
  i=partition(position, palavras, min, max);

  /*divisao da tabela em duas partes e nova analise*/
  quick_sort(position, palavras, min, i-1);
  quick_sort(position, palavras, i+1, max);

}


/******************************************************************************
 * partition(()
 *
 * Arguments: position - tabela de posiçoes das palavras
 *            palavras - tabela de palavras de tamanho unico 
 *            min - index minimo da tabela pretendido
 *            max - index maximo da tabela pretendido
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: encontra as palavras a trocar de posiçao por comparaçao com o
 *              pivo
 *
 *****************************************************************************/


int partition(int* position, char** palavras, int min, int max){

  int i, j;
  Item v;
  v=palavras[position[max]];
  i=min-1;
  j=max;

  for( ; ; ){
    /*procura de uma palavra maior que o pivo*/
    while(strcmp(palavras[position[++i]], v)<0);

    /*procura de uma palavra menor que o pivo*/
    while(strcmp(v, palavras[position[--j]])<0)
      if(j==min) break;

    if(i>=j) break;

    /*troca a primeira palavra menor que o pivo com a ultima menor*/
    exch(position[i], position[j]);
  }

  /*troca o pivo com a palavra maior que achou*/
  exch(position[i], position[max]);

  return i;
}

/******************************************************************************
 * selection_sort()
 *
 * Arguments: num_pal - numero de palavras
 *            position - tabela de posiçoes das palavras
 *            palavras - tabela de palavras de tamanho unico 
 * Returns: (void)
 * Side-Effects: none
 * Description: organiza a tabela de palavras alfabeticamente
 *
 *****************************************************************************/


void selection_sort(int num_pal, int *position, char** palavras){

  bool troca=false;
  int new_min=0;
  int min;
  int i, v;

  /*"reduçao" da tabela: tamanho da tabela=size-v; primeira posiçao=v;*/
  for(v=0; v<num_pal; ++v){

    min=v;

    /*procura do index da palavra de menor valor alfabetico*/
    for(i=v+1; i<num_pal; ++i){
      new_min=strcmp(palavras[position[min]], palavras[position[i]]);

      if(new_min>0){
        min=i;
        /*caso seja necessessario trocar*/
        troca=true;
      } 
    }

    /*inserçao na primeira posiçao da tabela, caso esteja trocado*/
    if(troca==true){
      exch(position[v], position[min]);
      troca=false;
    }

  }

}


/******************************************************************************
 * organizar_tabelas()
 *
 * Arguments: num_pal - numero de palavras
 *            position - tabela de posiçoes das palavras
 *            palavras - tabela de palavras de tamanho unico 
 * Returns: (void)
 * Side-Effects: none
 * Description: organizar e selecionar qual o melhor algoritmo para o fazer
 *              para cada tabela
 *
 *****************************************************************************/


void organizar_tabelas(int num_pal, int* position, char** palavras){

    if(num_pal>SORT_POINT){
      quick_sort(position, palavras, 0, num_pal-1);
    }
    else{
      selection_sort(num_pal, position, palavras);
    }

}


/******************************************************************************
 *  find_position()
 *
 * Arguments: problema - tabela de palavras
 *            position - tabela de posiçoes de palavras
 *            palavras - tabela de palavras de tamanho unico
 *            max - index maximo da tabela pretendido
 * Returns: (int) index da posiçao da palavra
 * Side-Effects: none
 *
 * Description: procura uma palavra na tabela
 *
 *****************************************************************************/


int find_position(char* problema, int* position, char** palavras, int max){

  int min=0;
  int m_point=(max+min)/2;  /*ponto medio*/

  while(strcmp(problema, palavras[position[m_point]])!=0){

    if(strcmp(problema, palavras[position[m_point]])>0)
      /*caso esteja depois do ponto medio*/
      min=m_point+1;

    else if(strcmp(problema, palavras[position[m_point]])<0)
      /*caso esteja antes do ponto medio*/
      max=m_point-1;

    m_point=(max+min)/2;

    /*caso nao se encontre a palavra*/
    if(max<min){
      printf("Erro, palavra inexistente!\n");
      exit(1);
    }
  }

  /*quando encontrar retorna o index da tabela de palavras*/
  return position[m_point];
}

