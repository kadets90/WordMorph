
#ifndef heap

#define key(A) (A)
#define lessPri(i, j) (key(i)>key(j))

/*alocaçao de espaço para o acervo e o seu mapa e inicializaçao
 *das variaveis size e N*/
void PQinit(int);
/*verifica se o N é igual a 0 ou nao*/
int PQempty(void);
/*insere um elemento na fila de prioridade consoante a sua
 *prioridade*/
void PQinsert(int, int*);
/*elemina o elemento de menor prioridade*/
int PQdelmin(int*);
/*corrige as posiçoes no acervo aquando uma alteraçao de peso*/
void PQdec(int, int*);
/*comparaçao de um menbro com o seu atecessor no acervo e em
 *caso de a posiçao estar trocado proceder com  sua correçao*/
void fixUp(int*, int);
/*compara e faz descer pelo acervo uma posiçao que seja menos
 *prioritaria do que outras para tras*/
void fixDown(int*, int, int); 
/*liberta a memoria alocada pelo acervo e o respetivo mapa*/
void PQfree();
/*troca o valor de duas posiçoes no acervo e corrige o mapa*/
void troca(int, int);
/*renicia o contador N*/
void PQrestart();

#endif
