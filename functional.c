
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"wordmorph.h"
#include"functional.h"
#include"matriz.h"
#include"lista.h"
#include"heap.h"


/******************************************************************************
 *  create_dic()
 *
 * Arguments: (void)
 * Returns: ponteiro para dicionario
 * Side-Effects: aloca memoria para varias tabelas
 *
 * Description: alocaçao de espaço para as varias tabelas da estrutura 
 *               dicionario (numero de palavras por tamanho, vetor que separa
 *               o dicionario por tamanhos, posiçao das palavras, vetor de 
 *               ordenaçao)
 *
 *****************************************************************************/


dicionario* create_dic(void){

  /*alocaçao de memoria para a estrutura dicionario*/
  dicionario* point=(dicionario*)malloc(sizeof(dicionario));
  if(point==NULL){
    printf("Erro na criacao do dicionario!\n");
    exit(1);
  }

  /*allocaçao de memoria para matriz 3D */
  point->matriz=(char***)malloc(sizeof(char**)*STR_SIZE);
  if(point->matriz==NULL){
    printf("Erro na criacao da matriz! (Parte 1)\n");
    exit(1);
  }

  /*allocaçao de memoria para vetor de inteiros
  guarda numero de palavras com x numero de letras*/
  point->num_pal=(int*)calloc(sizeof(int), STR_SIZE);
  if(point->num_pal==NULL){
    printf("Erro na criaçao da tabela de contagens!\n");
    exit(1);
  }

  /*allocaçao de memoria para matriz 2D de inteiros
  guarda as posiçoes das palavras na matriz*/
  point->position=(int**)malloc(sizeof(int*)*STR_SIZE);
  if(point->position==NULL){
    printf("Erro na criaçao da tabela de posicoes!\n");
    exit(1);
  }
  

  return point;
}


/******************************************************************************
 *  star_dic()
 *
 * Arguments: point - estrutura dicionario
 *            argv - nome do ficheiro que contem o dicionario
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: cria e preenche as matriz dicionario e a matriz de posiçoes
 *
 *****************************************************************************/


void start_dic(dicionario* point, char** argv){

  /*criaçao da matriz 3D para as palavras*/
  criar_matriz_3(point->matriz, point->num_pal);

  /*preenchimento da tabela 3D*/
  prencher_matriz(point->matriz, argv[1]);

  /*criaçao da matriz 2D de posiçoes*/
  criar_matriz(point->position, point->num_pal);

}


/******************************************************************************
 * guardar_prob()
 *
 * Arguments: prob - ponteiro para a lista de problemas
 *            fp - ficheiro com os problemas
 *            num_max_mut - numero maximo de mutaçoes por tamanhos
 *            existe - informaçao de existencia de problema de um dado tamanho 
 * Returns: ponteiro para a cabeça da lista de problemas
 * Side-Effects: alocaçao de memoria para a lista e respetivas palavras
 *
 * Description: aloca e preenche a lista com os problemas a resolver
 *
 *****************************************************************************/


Item guardar_prob(Item prob, FILE* fp, int* num_max_mut, int* existe){

  char str1[STR_SIZE];
  char str2[STR_SIZE];
  int size;
  Item aux1=NULL;
  Item aux2=NULL;
  problema* aux_est=NULL;
  int avaliador;

  if(fscanf(fp, "%s %s %i", str1, str2, &size)==3){

    avaliador=cmp_char(str1, str2, size);

    aux2=criaNovoNo();

    /*alocaçao de memoria e inicializaçao dos varios campos da esturutura problema*/
    aux_est=(problema*)malloc(sizeof(problema));
    if(aux_est==NULL){
      printf("Erro na alocaçao da lista de problemas!\n");
      exit(1);
    }

    /*alocaçao de memoria para a palavra de origem*/
    aux_est->palavra1=(char*)malloc(sizeof(char)*(strlen(str1)+1));
    if(aux_est->palavra1==NULL){
      printf("Erro na alocaçao da lista de problemas(pal1)!\n");
      exit(1);
    }
    strcpy(aux_est->palavra1, str1);

    /*alocaçao de memoria para a palavra de destino*/
    aux_est->palavra2=(char*)malloc(sizeof(char)*(strlen(str2)+1));
    if(aux_est->palavra2==NULL){
      printf("Erro na alocaçao da lista de problemas(pal2)!\n");
      exit(1);
    }
    strcpy(aux_est->palavra2, str2);

    /*atualizar informaçao de existencia de problemas para o tamanho em causa*/
    existe[strlen(str1)]=YES;

    /*mutaçao maxima permitida*/
    if(avaliador<size)
      size=avaliador;

    aux_est->mutacoes=size;

    /*maximo de mutaçoes permitidas para cada tamanho de palavras*/
    if(num_max_mut[strlen(str1)]<size)
      num_max_mut[strlen(str1)]=size;

    /*inserçao da estrutura na lista*/
    insert_est(aux2, aux_est);

    /*obtençao do proximo no*/
    aux1=guardar_prob(prob, fp, num_max_mut, existe);

    /*adicionar o no previamento criado ao resto da lista como nova head*/
    if(aux1!=NULL)
      aux2=adicionar_elemento(aux2, aux1);

  }

  prob=aux2;

 return prob;
}


/******************************************************************************
 * criar_tabela_adj()
 *
 * Arguments: tabela_adj - ponteiro para o grafo
 *            num_max_mut - numero maximo de mutaçoes premitidas
 *            pal - tabela de palavras de tamanho unico
 *            num_pal - numero de palavras do tamanho a tratar  
 * Returns: ponteiro para o grafo
 * Side-Effects: alocaçao de memoria para o grafo
 *
 * Description: alocaçao de memoria e inicializaçao de todos os parametros que 
 *              compoem o grafo
 *
 *****************************************************************************/


Item* criar_tabela_adj(Item* tabela_adj, int num_max_mut, int num_pal, char** pal){

  int count, i, x;
  Item new_node;
  aresta* new_est;

  /*alocaçao de memoria para a tabela de ponteiros para as diversas listas de adejacencias*/
  tabela_adj=(Item*)calloc(sizeof(Item),num_pal);
  if(tabela_adj==NULL){
    printf("Erro a alocar tabela de adj!\n");
    exit(1);
  }

  for(i=0; i<num_pal; ++i){

    for(x=i+1; x<num_pal; ++x){

      /*comparaçao dos caracteres das palavras*/
      count=cmp_char(pal[i], pal[x], num_max_mut);

      if(count<=num_max_mut){

        /*adiçao da palavra à lista de palavras adejacentes*/
        new_node=criaNovoNo();
        new_est=init_aresta(x, count);
        insert_est(new_node, new_est);
        tabela_adj[i]=adicionar_elemento(new_node, tabela_adj[i]);

        /*faz-se a adiçao contraria*/
        new_node=criaNovoNo();
        new_est=init_aresta(i, count);
        insert_est(new_node, new_est);
        tabela_adj[x]=adicionar_elemento(new_node, tabela_adj[x]);

      }
    }
  }

  return tabela_adj;
}


/******************************************************************************
 * init_aresta()
 *
 * Arguments: position - posiçao na matriz dicionario
 *            peso - peso da mutaçao 
 * Returns: ponteiro para a aresta criada
 * Side-Effects: alocaçao de memoria para uma aresta do grafo
 *
 * Description: aloca memoria e inicializa os valores da aresta do grafo
 *
 *****************************************************************************/


Item init_aresta(int position, int peso){

  aresta* aux=NULL;

  /*alocaçao de memoria para a aresta*/
  aux=(aresta*)malloc(sizeof(aresta));
  if(aux==NULL){
    printf("Erro a alocar aresta!\n");
    exit(1);
  }

  /*inicializaçao dos campos*/
  aux->position=position;
  aux->peso=quadrado(peso);
  
  return (Item)aux;

}


/******************************************************************************
 * cmp_char()
 *
 * Arguments: pal1 - palavra a comparar
 *            pal2 - palavra a comparar
 *            num_dif - numero de diferenças maximas admitido
 * Returns: numero de caracteres diferentes entre as palavras
 * Side-Effects: none
 *
 * Description: compara as duas palavras recebidas como argumentos caracter 
 *              a caracter e retorna o numeor de caracteres diferentes
 *
 *****************************************************************************/


int cmp_char(char* pal1, char* pal2, int num_dif){

  int i;
  int count=0;

  for(i=0; pal1[i]!='\0'; ++i){
    if(pal1[i]!=pal2[i]){
      if(++count>num_dif) break;
    }
  }

  return count;
}


/******************************************************************************
 * vetor_minimos()
 *
 * Arguments: num_pal - numero de palavras do tamanho dado
 * Returns: tabela com os preços da passagem da palavra original para as
 *          adjancentes
 * Side-Effects: none
 *
 * Description: cria uma tabela com os valores dos preços da mutaçao de uma
 *              palavra para uma sua adjacente
 *
 *****************************************************************************/


int* vetor_num(int num_pal){

  int* pesos;

  pesos=(int*)malloc(sizeof(int)*num_pal);
  if(pesos==NULL){
    printf("Erro a alocar pesos!\n");
    exit(1);
  }

  return pesos;
}


/******************************************************************************
 * achar_caminho()
 *
 * Arguments: lista_adj - lista de palavras adjacentes
 *            num_pal - numero de palavras do tamanho dado
 *            ponto_partida - raiz da arvore de caminhos minimos
 *            caminho - vetor com os caminhos a seguir para chegar à raiz
 *            pesos - vetor com os pesos dos caminhos
 *            lim - limite de mutaçoes permitidas
 * Returns: (void)
 * Side-Effects: alocaçao de memoria para a fila prioritaria
 *
 * Description: encontra e regista os caminhos mais curtos ate uma raiz
 *              defenida a partir de pesos e de uma fila de prioridade
 *
 *****************************************************************************/


void achar_caminho(Item* tabela_adj, int ponto_partida, int ponto_chegada, int* caminho, int* pesos, int num_pal, int lim){

  int v, w;
  Item aux;
  aresta* aux_est=NULL;

  /*inicializaçao dos vetores caminho e pesos e sua inserçao na fila de prioridades*/
  for(v=0; v<num_pal; v++){

    caminho[v]=NO_WAY;
    pesos[v]=INFINITO;
  }

  /*defeniçao da raiz*/
  pesos[ponto_partida]=0;
  caminho[ponto_partida]=ponto_partida;
  PQinsert(ponto_partida, pesos);
  PQdec(ponto_partida, pesos);

  /*verificaçao de toda a lista*/
  while(!PQempty()&&v!=ponto_chegada){
    /*existe ligaçao?*/
    if(pesos[v=PQdelmin(pesos)]!=INFINITO)
      /*ligaçao das arestas encontradas e criaçao da arvore de caminhos minimos*/
      for(aux=tabela_adj[v], aux_est=(aresta*)get_est(aux); aux!=NULL; aux=get_next(aux), aux_est=(aresta*)get_est(aux))
        /*caso a aresta respeite o peso ao problema dado*/
        if(aux_est->peso<=lim){
          /*se ainda nao estiver na fila de prioridades*/
          if(pesos[aux_est->position]==INFINITO)
            PQinsert(aux_est->position, pesos);
          /*caminho mais curto?*/
          if(pesos[w=aux_est->position]>P){
            pesos[w]=P;
            PQdec(w, pesos);
            caminho[w]=v;
          }
        }
  }
  /*reinicializaçao do limite da fila*/
  PQrestart();
}


/******************************************************************************
 * guardar_sol()
 *
 * Arguments: pos1 - indice da palavra de origem
 *            pos2 - indice da palavra de destino
 *            caminho - vetor com os indices da proxima posiçao do caminho
 *            pesos - vetor com os pesos de cada posiçao
 *            palavras - tabela de palavras de tamanho unico do dicionario 
 * Returns: ponteiro para a estrutura soluçao
 * Side-Effects: alocaçao de memoria para a lista de palavras
 *
 * Description: aloca e preenche uma tabela com as soluçoes aos problemas
 *
 *****************************************************************************/


solucao guardar_sol(int pos1, int pos2, int* caminho, int* pesos, char** palavras){

  solucao sol;
  Item aux;

  sol.caminho=NULL;

  /*existe caminho?*/
  if(caminho[pos2]!=NO_WAY){

    sol.custo=pesos[pos2];

    /*caso de as palavras serem iguais*/
    if(pos1==pos2){

      /*criaçao de um novo no*/
      aux=criaNovoNo();
      sol.caminho=adicionar_elemento(aux, sol.caminho);

      /*inserçao das palavras*/
      insert_est(aux, (Item)palavras[pos2]);
    }
    else{

      while(pesos[pos2]!=0){

        /*criaçao de um novo no*/
        aux=criaNovoNo();
        sol.caminho=adicionar_elemento(aux, sol.caminho);

        /*inserçao das palavras*/
        insert_est(aux, (Item)palavras[pos2]);

        /*proxima aresta*/
        pos2=caminho[pos2];

      }
    }
  }
  else{

    sol.custo=NO_WAY;

    /*criaçao de um novo no*/
    aux=criaNovoNo();
    sol.caminho=adicionar_elemento(aux, sol.caminho);

    /*escrita da palavra de origem*/
    insert_est(aux, (Item)palavras[pos2]);

  }

  /*ultimo no no*/
  aux=criaNovoNo();
  sol.caminho=adicionar_elemento(aux, sol.caminho);

  /*escrita da palavra de destino*/
  insert_est(aux, (Item)palavras[pos1]);

  return sol;
}


/******************************************************************************
 *  free_prob()
 *
 * Arguments: est - estrutura do problema
 * Returns: (void)
 * Side-Effects: libertaçao da memoria alocada para a estrutura problema
 *
 * Description: liberta a memoria alocada para a estrutura problema e dos seus
 *              respetivos campos
 *
 *****************************************************************************/


void free_prob(Item est){

  free((*(problema*)est).palavra1);
  free((*(problema*)est).palavra2);
  free(est);

}


/******************************************************************************
 *  free_tab_adj()
 *
 * Arguments: tabela - tabela de ponteiros para listas
 *            num_pal - numero de ponteiros da tabela
 * Returns: (void)
 * Side-Effects: libertaçao da memoria alocada para o grafo
 *
 * Description: liberta a memoria alocada para as varias listas que compoem o
 *              grafo e a tabela de ponteiros para as varias listas
 *
 *****************************************************************************/


void free_tab_adj(Item* tabela, int num_pal){

  int i;

  for(i=0; i<num_pal; ++i){
     free_lista(tabela[i], free_adj);
  }

  free(tabela);

}


/******************************************************************************
 *  free_adj()
 *
 * Arguments: est - estrutura aresta
 * Returns: (void)
 * Side-Effects: liberta a memoria alocada para uma aresta
 *
 * Description: liberta a memoria alocada para uma aresta
 *
 *****************************************************************************/


void free_adj(Item est){

  free((aresta*)est);

}


/******************************************************************************
 *  free_sol()
 *
 * Arguments: sol - ponteiro tabela de soluçoes
 *            Num_sol - numero de soluçoes
 * Returns: (void)
 * Side-Effects: libertaçao de memoria alocada pela tabela de soluçoes
 *
 * Description: liberta a memoria da tabela de listas de soluçoes
 *
 *****************************************************************************/


void free_sol(solucao* sol, int num_sol){

  int i;

  for(i=0; i<num_sol; ++i){
    free_lista(sol[i].caminho, free_sol_est);
  }

  free(sol);
}


/******************************************************************************
 *  free_sol_est()
 *
 * Arguments: 
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: funçao vazia, memoria desalocada noutro local
 *
 *****************************************************************************/


void free_sol_est(){

}

