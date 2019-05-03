/******************************************************************************
 *
 * File Name: main.c
 * Authors: David Ribeiro & Rafael Forte
 * Last modified: 12/12/2016
 * Revision:  v4.0
 *
 * COMMENTS
 *		Main program
 *
 *****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"wordmorph.h"
#include"ficheiros.h"
#include"ordenacao.h"
#include"matriz.h"
#include"functional.h"
#include"lista.h"
#include"heap.h"


/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Side-Effects: none
 *
 * Description: main Program
 *
 *****************************************************************************/


int main(int argc, char *argv[]){

  /*ponteiro para ficheiros de entrada*/
  FILE* fpin;
  /*contadores para ciclos*/
  int i, v;
  /*posiçao de palavra de origem e de destino no dicionario*/
  int pos1, pos2;
  /*ponteiro para a estrutura do dicionario*/
  dicionario *point;
  /*tabela que diz se existem problemas ou nao par dado tamanho*/
  int existe[STR_SIZE]={0};
  /*numero maximo de mutaçoes por tamanhos*/
  int num_max_mut[STR_SIZE]={0};
  /*ponteiro para a tabela de listas de adejacencias*/
  Item* tabela_adj=NULL;
  /*vetor com os pesos dos caminhos*/
  int* pesos;
  /*vetor com os caminhos. arvore de caminhos minimos*/
  int* caminho;
  /*ponreiro para a lista de problemas*/
  Item prob=NULL;
  /*ponteiro para os problemas auxiliar*/
  Item aux=NULL;
  /*ponteiro para a estrutura de problemas*/
  problema* probs=NULL;
  /*ponteiro para a lista de soluçoes*/
  solucao* sol=NULL;
  /*numero de problemas/soluçoes*/
  int num_sol;

  /*verificaçao do numero de inputs*/ 
  if(argc!=3){
    exit(1);
  }

  /*verificaçao das extensoes*/
  for(i=1; i<=2; ++i){
    verifica_inputs(i, argv);
  }

  /*alocaçao da memoria do dicionario*/
  point=create_dic();

  /*abre o ficheiro com o dicionario*/
  fpin=abre_ficheiro(argv[1], "r");

  /*contagem das palavras por tamanhos*/
  numero_pal(fpin, point->num_pal);

  /*fecho do ficheiro com o dicionario*/
  fclose(fpin);

  /*inicializacao do dicionario*/
  start_dic(point, argv);

  /*abertura do ficheiro com os problemas*/
  fpin=abre_ficheiro(argv[2], "r");

  /*cria lista com os problemas*/
  prob=guardar_prob(prob, fpin, num_max_mut, existe);

  /*fecho do ficheiro com os problemas*/
  fclose(fpin);

  /*cria uma tabela com o numero de problemas*/
  sol=(solucao*)malloc(sizeof(solucao)*(num_sol=cont_ele(prob)));
  if(sol==NULL){
    printf("Erro na alocaçao das soluçoes!\n");
    exit(1);
  }

  /*resoluçao do problema*/
  for(v=0; v<STR_SIZE; ++v){

    if(existe[v]!=0){

      /*ordenar a tabela de palavras de tamanho v*/
      organizar_tabelas(point->num_pal[v], point->position[v], point->matriz[v]);

      /*justifica-se fazer n² comparaçoes?*/
      if(num_max_mut!=0)
        /*criaçao do grafo para as palavras de tamanho a tratar*/
        tabela_adj=criar_tabela_adj(tabela_adj, num_max_mut[v], point->num_pal[v], point->matriz[v]);

      /*alocar memoria para a fila de prioridade*/
      PQinit(point->num_pal[v]);

      /*vetor com os pesos*/
      pesos=vetor_num(point->num_pal[v]);

      /*vetor com os caminhos*/
      caminho=vetor_num(point->num_pal[v]);

      /*equanto houver problemas*/
      for(aux=prob, i=0; aux!=NULL; aux=get_next(aux), ++i){

        /*vai buscar os dados do problema*/
        probs=get_est(aux);

        /*probela compativel com o grafo atual*/
        if(strlen((*(problema*)probs).palavra1)==v){

          /*posiçao da palavra de origem*/
          pos1=find_position((*(problema*)probs).palavra1, point->position[v], point->matriz[v], point->num_pal[v]);

          /*posiçao da palavra de destino*/
          pos2=find_position((*(problema*)probs).palavra2, point->position[v], point->matriz[v], point->num_pal[v]);

          /*vai achar os camnhos mais curtos para a palavra de origem*/
          achar_caminho(tabela_adj, pos1, pos2, caminho, pesos, point->num_pal[v], quadrado((*(problema*)probs).mutacoes));

          /*coloca na lista de soluçoes*/
          sol[i]=guardar_sol(pos1, pos2, caminho, pesos, point->matriz[v]);
        }
      }
      /*libertar tabela de pesos*/
      free(pesos);

      /*libertar tabela de caminhos*/
      free(caminho);

      /*libertaçao da memoria alocada na fila de prioridades*/
      PQfree();

      /*libertaçao da memoria ocupada pelo grafo*/
      free_tab_adj(tabela_adj, point->num_pal[v]);
    }
  }

  /*escrita das soluçoes num ficheiro de saida .path*/
  escreve_ficheiro(sol, num_sol, argv[2]);

  /*libertaçao da memoria utilizada ao longo do programa*/
  free_sol(sol, num_sol);
  free_matriz_3(point->matriz, point->num_pal);
  free_matriz_2((void**)point->position, STR_SIZE);
  free_lista(prob, free_prob);
  free(point->num_pal);
  free(point->matriz);
  free(point->position);
  free(point);

  return 0;
}
