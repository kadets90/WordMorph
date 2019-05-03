
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"wordmorph.h"
#include"ficheiros.h"
#include"lista.h"


/******************************************************************************
 * verifica_inputs()
 *
 * Arguments: index - identificaçao do ficheiro de entrada
 *            argv - tabela com os nomes dos ficheiros de entada
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: verifica se os ficheiros de input sao do formato pretendido
 *
 *****************************************************************************/


void verifica_inputs(int index, char **argv){

  char *vext;
  int i;
  char* ext;
  int size;

  /*tamanho do nome do ficheiro sem a extensao*/
  size=strlen(argv[index])-INPUT_EXTENSION;

  /*alocaçao de memoria para string com a extensao*/  
  ext=(char*)malloc(sizeof(char)*(INPUT_EXTENSION+1));
  if(ext==NULL) 
    exit(1);

  /*copia da extensao*/
  for(i=0; i<=INPUT_EXTENSION; ++i)
    ext[i]=argv[index][i+size];

  /*selecionar a extensao do ficheiro*/
  sele_str(&vext, index);

  /*verificar se esta correto*/
  if(strcmp(ext, vext)!=0)
    exit(1);

  free(ext);

}


/******************************************************************************
 *  sele_str()
 *
 * Arguments: vext - extensao pertendida
 *            msg_erro - palavra para mostrar em caso de erro
 *            index - seleçao do que é prentendido
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: funçao que seleciona qual a extensao pretendida e mensagem de
 *              erro a ser mostrada em caso de erro
 *
 *****************************************************************************/


void sele_str(char **vext, int index){

  if(index==1){
    *vext=".dic";
  }
  else if(index==2){
    *vext=".pal";
  }
  else{
    exit(1);
  }

}


/******************************************************************************
 *  numero_pal()
 *
 * Arguments: fp - ficheiro do tipo dicionario
 *            num_pal - tabela com o numero de palavras de cada tamanho
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: contagem de palavras por tamanhos
 *
 *****************************************************************************/


void numero_pal(FILE *fp, int* num_pal){

  char aux_str[STR_SIZE];
  
  /*contagem das palavras segundo tamanhos*/
  while(fscanf(fp, "%s", aux_str)==1){
    ++num_pal[strlen(aux_str)];
  }

}


/******************************************************************************
 * abre_ficheiro()
 *
 * Arguments: nome - nome do ficheiro a abrir
 *            mode - se é para escrever ou ler
 * Returns: (FILE*) ponteiro para o ficheiro aberto
 * Side-Effects: none
 *
 * Description: Abre um ficheiro
 *
 *****************************************************************************/


FILE* abre_ficheiro(char* nome, char* mode){

  FILE *fp;
  fp=fopen (nome, mode);
  if(fp==NULL){
    printf("Erro nao foi possivel abrir o ficheiro %s!\n", nome);
    exit(1);
  }

  return fp;
}


/******************************************************************************
 * cria_ficheiro()
 *
 * Arguments: ficheiro - nome do ficheiro de problemas 
 * Returns: (FILE*) ponteiro para o ficheiro de saida
 * Side-Effects: cria um ficheiro de extensao ".stat"
 *
 * Description: criaçao de um ficheiro com extensao ".stat" onde serao
 *              escritos os resultados
 *
 *****************************************************************************/


FILE* cria_ficheiro(char* ficheiro){

  char* nome=NULL;
  FILE* fpout;
  int q;

  /*alocaçao de memoria para o nome do ficheiro*/
  nome=(char*)malloc(((q=(strlen(ficheiro))+2))*sizeof(char));
  if(nome==NULL){
    printf("Erro na criacao do nome do ficheiro!\n");
    exit(1);
  }

  /*fica com o nome do ficheiro de problemas com a extensao ".stat"*/
  strcpy(nome, ficheiro);
  *(nome+q-5)='p';
  *(nome+q-4)='a';
  *(nome+q-3)='t';
  *(nome+q-2)='h';
  *(nome+q-1)='\0';

  fpout=abre_ficheiro(nome, "w");

  free(nome);

  return fpout;
}


/******************************************************************************
 * escreve_ficheiro()
 *
 * Arguments: fpout - ficheiro de extensao ".stat"
 *            pos1 - posiçao da palavra de origem
 *            pos2 - posiçao da palavra de destino
 *            caminho - vetor com o caminho a percorrer para chegar à raiz
 *            pesos - pesos das arestas
 *            palavras - palavras do tamanho do problema
 *
 * Returns: (void)
 * Side-Effects: escrita no ficheiro de saida
 *
 * Description: escreve as respostas aos problemas num ficheiro de saida
 *
 *****************************************************************************/


void escreve_ficheiro(solucao* sol, int num_sol, char* nome){

  Item aux;
  int i;
  FILE* fpout;

  /*abertura do ficheiro onde serao escritos os resultados*/
  fpout=cria_ficheiro(nome);

  for(i=0; i<num_sol; ++i){

    aux=sol[i].caminho;

    /*escrita da palavra de origem e o preço pago no caminho*/
    fprintf(fpout, "%s %i\n", (char*)get_est(aux), sol[i].custo);

    while((aux=get_next(aux))!=NULL){

      /*escrita do caminho efetuado*/
      fprintf(fpout, "%s\n", (char*)get_est(aux));

    }

    fprintf(fpout, "\n");
  }

  fclose(fpout);

}

