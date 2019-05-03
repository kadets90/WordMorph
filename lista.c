
#include<stdio.h>
#include<stdlib.h>

#include"wordmorph.h"
#include"lista.h"


/*estrutura da lista*/
typedef struct lista{

  Item est;
  struct lista* next;

}lista;


/******************************************************************************
 * criaNovoNo ()
 *
 * Arguments: (void)
 * Returns: ponteiro para o no criado
 * Side-Effects: aloca memoria para um no
 *
 * Description: aloca um no e inicializa op ponteiro para o proximo a null
 *
 *****************************************************************************/


Item criaNovoNo (void){
  
  lista* no=(lista*)malloc(sizeof(lista));
  if(no==NULL){
    printf("Erro na criacao da lista!\n");
    exit(1);
  }

  no->next=NULL;

  return no;
}


/******************************************************************************
 * adicionar_elemento()
 *
 * Arguments: head - ponteiro para a cabeça da lista
 *            novo_no - ponteiro para o no a adicionar à lista
 * Returns: ponteiro para a cabeça da lista
 * Side-Effects: none
 *
 * Description: adiciona um no previamente criada ao fim de uma lista ja
 *              existente
 *
 *****************************************************************************/


Item adicionar_elemento(Item head, Item novo_no){

  lista* aux=(lista*)head;

  if(head!=NULL){
    /*procura pelo ultimo no da lista*/
    while(aux->next!=NULL)
      aux=aux->next;

    aux->next=(lista*)novo_no;
  }
  else{
    head=novo_no;
  }

  return head;
}


/******************************************************************************
 * cria_lista()
 *
 * Arguments: head - ponteiro para a cabeça da lista
 *            size - numero de nos a acrescentar a lista
 * Returns: ponteiro para a cabeça da lista
 * Side-Effects: alocaçao de memoria para os nos criados
 *
 * Description: cria\aumenta uma lista com\em "size" nos
 *
 *****************************************************************************/

 
Item criar_lista(Item head, int size){

  int i;
  lista* aux=NULL;
  lista* aux2=head;

  for(i=0; i<size; ++i){
    aux=(lista*)criaNovoNo();
    if(head==NULL){
     head=aux;
     aux2=aux;
    }
    else{
     aux2->next=aux;
     aux2=aux;
    }
  }

  return head;
}


/******************************************************************************
 *  cont_ele()
 *
 * Arguments: prob - ponteiro para a cabeça da lista
 * Returns: numero de elementos da lsta
 * Side-Effects: none
 *
 * Description: conta os elementos de uma lista e devolve o valor
 *
 *****************************************************************************/


int cont_ele(Item prob){

  int count=0;
  lista* aux=(lista*)prob;

  while(aux!=NULL){
    ++count;
    aux=aux->next;
  }

  return count;
}


/******************************************************************************
 *  get_next()
 *
 * Arguments: aux - ponteiro para um no
 * Returns: ponteiro para o proximo no
 * Side-Effects: none
 *
 * Description: recebe um elemneto de uma lista como argumento e retorna o
 *              elemento seguinte
 *
 *****************************************************************************/


Item get_next(Item aux){

  aux=(*(lista*)aux).next;

  return aux;
}


/******************************************************************************
 *  get_est()
 *
 * Arguments: aux - ponteiro para um no
 * Returns: ponteiro para a estrutura com os dados desse no
 * Side-Effects: none
 *
 * Description: recebe um elemneto de uma lista como argumento e retorna a
 *              estrutura com os dados desse no
 *
 *****************************************************************************/


Item get_est(Item aux){

  if(aux==NULL)
    return NULL;

  return (*(lista*)aux).est;
}


/******************************************************************************
 *  insert_est()
 *
 * Arguments: aux - ponteiro para um no
 *            est - ponteiro para a estrutura
 * Returns: none
 * Side-Effects: none
 *
 * Description: liga uma estrutura ao respetivo no
 *
 *****************************************************************************/


void insert_est(Item aux, Item est){

  (*(lista*)aux).est=est;

}


/******************************************************************************
 *  free_lista()
 *
 * Arguments: head - priemrio elemento da lista
 *            free_item - funçao de libertaçao da memoria da estrutura que
 *                        constitui a lista
 * Returns: (void)
 * Side-Effects: libertaçao da memoria alocada para a lista
 *
 * Description: liberta a memoria alocada para a lista e respetivos campos
 *              constituintes
 *
 *****************************************************************************/


void free_lista(Item head, void (*free_item)(Item)){

  lista* aux1=head;
  lista* aux2=aux1;

  while(aux1!=NULL){

    aux2=aux2->next;
    (*free_item)(aux1->est);
    free(aux1);
    aux1=aux2;

  }

}
