
#ifndef lista

/*aloca um no e inicializa op ponteiro para o proximo a null*/
Item criaNovoNo (void);
/*adiciona um no previamente criada ao fim de uma lista ja
 *existente*/
Item adicionar_elemento(Item, Item);
/*cria\aumenta uma lista com\em "size" nos*/
Item criar_lista(Item, int);
/*conta os elementos de uma lista e devolve o valor*/
int cont_ele(Item prob);
/*recebe um elemneto de uma lista como argumento e retorna o
 *elemento seguinte*/
Item get_next(Item);
/*recebe um elemneto de uma lista como argumento e retorna a
 *estrutura com os dados desse no*/
Item get_est(Item);
/*liga uma estrutura ao respetivo no*/
void insert_est(Item, Item);
/*liberta a memoria alocada para a lista e respetivos campos
 *constituintes*/
void free_lista(Item, void (*free_item)(Item));

#endif
