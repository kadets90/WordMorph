
#include<stdio.h>
#include<stdlib.h>

#include"wordmorph.h"
#include"heap.h"


/*fila de prioridade*/
static int* pq;
/*posiçoes no acervo*/
static int* pos;
/*"contador"*/
static int N;
/*numero de palavras*/
static int size;


/******************************************************************************
 *  PQinit()
 *
 * Arguments: maxN - numero de palavras
 * Returns: none
 * Side-Effects: aloca memoria para o acervo e para o mapa dos vertices do
 *               acervo
 *
 * Description: alocaçao de espaço para o acervo e o seu mapa e inicializaçao
 *              das variaveis size e N
 *
 *****************************************************************************/


void PQinit(int maxN){ 

  pq=(int*)malloc(maxN*sizeof(int));
  if(pq==NULL){
    printf("Erro na alocacao do acervo!\n");
    exit(1);
  }

  pos=(int*)malloc(maxN*sizeof(int));
  if(pos==NULL){
    printf("Erro na alocacao das posicoes acervo!\n");
    exit(1);
  }

  N=0;
  size=maxN;
}


/******************************************************************************
 *  PQempty()
 *
 * Arguments: 
 * Returns: informaçao de sim ou nao
 * Side-Effects: none
 *
 * Description: verifica se o N é igual a 0 ou nao
 *
 *****************************************************************************/


int PQempty(void){
 
   return N==0; 
}


/******************************************************************************
 *  PQinsert()
 *
 * Arguments: v - indice do mapa do acervo para o valor N
 *            pesos - tabela com os pesos das mutaçoes
 * Returns: none
 * Side-Effects: none
 *
 * Description: insere um elemento na fila de prioridade consoante a sua
 *              prioridade
 *
 *****************************************************************************/


void PQinsert(int v, int* pesos){

  /*insere novo elemento no fim e restabelece ordenação com FixUp*/
  if(N<size){
    pq[N]=v;
    pos[v]=N;
    fixUp(pesos, N);
    ++N;
  }
}


/******************************************************************************
 *  PQdelmin()
 *
 * Arguments: pesos - tabela com os pesos das mutaçoes
 * Returns: indice do caminho mais curto dispinovel
 * Side-Effects: none
 *
 * Description: elemina o elemento de menor prioridade
 *
 *****************************************************************************/


int PQdelmin(int* pesos){

  /*troca maior elemento com último da tabela e reordena com FixDown*/
  troca(0, --N);
  fixDown(pesos, 0, N);

  /*ultimo elemento não considerado na reordenação*/
  return pq[N]; 
}


/******************************************************************************
 *  PQdec()
 *
 * Arguments: w - valor no acervo alterado
 *            pesos - tabela com o preço das mutaçoes
 * Returns: none
 * Side-Effects: none
 *
 * Description: corrige as posiçoes no acervo aquando uma alteraçao de peso
 *
 *****************************************************************************/


void PQdec(int w, int* pesos){

  fixUp(pesos, pos[w]);
}


/******************************************************************************
 *  fixUp()
 *
 * Arguments: heap - tabela com os pesos das mutaçoes
 *            k - posiçao no acervo a ser corrigida
 * Returns: none
 * Side-Effects: none
 *
 * Description: comparaçao de um menbro com o seu atecessor no acervo e em
 *              caso de a posiçao estar trocado proceder com  sua correçao
 *
 *****************************************************************************/


void fixUp(int* heap, int k){

  while(k>0&&lessPri(heap[pq[(k-1)/2]], heap[pq[k]])){
    troca(k, (k-1)/2);
    k=(k-1)/2;
  }
}


/******************************************************************************
 *  fixDown()
 *
 * Arguments: heap - tabela com os pesos das mutaçoes
 *            k - posiçao no acervo a ser corrigida
 *            x - lim de posiçao a trocar
 * Returns: none
 * Side-Effects: none
 *
 * Description: compara e faz descer pelo acervo uma posiçao que seja menos
 *              prioritaria do que outras para tras
 *
 *****************************************************************************/


void fixDown(int* heap, int k, int x){

  int j;

  /*enquanto não chegar às folhas*/
  while(2*k<x-1){

     j=2*k+1;

     /*Selecciona o maior descendente.*/
     /*Nota: se índice j é x-1, então só há um descendente */
     if(j<(x-1)&&lessPri(heap[pq[j]], heap[pq[j+1]])) j++;
     if(!lessPri(heap[pq[k]], heap[pq[j]])) break;

     troca(k, j);
     /*continua a descer a árvore*/
     k=j;
  }
}


/******************************************************************************
 *  PQrestart()
 *
 * Arguments: 
 * Returns: none
 * Side-Effects: none
 *
 * Description: renicia o contador N
 *
 *****************************************************************************/


void PQrestart(){

  N=0;
}

/******************************************************************************
 *  PQfree()
 *
 * Arguments: 
 * Returns: none
 * Side-Effects: libertaçao de memoria alocada por duas tabelas
 *
 * Description: liberta a memoria alocada pelo acervo e o respetivo mapa
 *
 *****************************************************************************/


void PQfree(){

   free(pos);
   free(pq);
}


/******************************************************************************
 *  troca()
 *
 * Arguments: x - posiçao no acervo
 *            y - posiçao no acervo
 * Returns: none
 * Side-Effects: none
 *
 * Description: troca o valor de duas posiçoes no acervo e corrige o mapa
 *
 *****************************************************************************/


void troca(int x, int y){

  exch(pq[x], pq[y]);
  pos[pq[x]]=x;
  pos[pq[y]]=y;

}
