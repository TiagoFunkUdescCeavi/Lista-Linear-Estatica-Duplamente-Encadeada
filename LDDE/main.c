#include <stdio.h>
#include <stdlib.h>

#include "ldde_publica.h"

#define ORDEM 1000
#define N_INSERE 10*ORDEM
#define N_REMOVE 3*ORDEM

void inserir10000Elementos( pldde ll ){
  int r = 0;
  for( int i = 0; i < N_INSERE; i++ ){
    r = InserirInicio( ll, &i );
    printf("Inserindo, i: %d, r: %d\n", i, r );
  }
}

void remover3000Elementos( pldde ll ){
  for( int i = 0; i < N_REMOVE; i++ ){
    RemoverInicio( ll );
    printf("Removendo, i: %d, r: %d\n", i );
  }
}

int main(){
    pldde lista = 0;
    
    CriarLista( &lista, sizeof(int) );

    inserir10000Elementos( lista );
    printf("Contador pulos: %d\n", get_count( lista ) );

    remover3000Elementos( lista );
    printf("Contador pulos: %d\n", get_count( lista ) );

    // int elemento = 0, i = 5;
    // pldde lista = NULL;

    // if(CriarLista(&lista, sizeof(int)) == ERRO){
    //     printf("Erro ao criar a lista!\n");
    //     exit(1);
    // }
    // InserirInicio(lista, (void *) &i);
    // i = 7;
    // InserirFim(lista, (void *) &i);
    // i = 6;
    // InserirPos(lista, (void *) &i, 0);

    // printf("elemento: %d\n", *(int *) BuscarInicio(lista));
    // printf("elemento: %d\n", *(int *) BuscarPos(lista, 1));
    // printf("elemento: %d\n", *(int *) BuscarFim(lista));

    // if(DestruirLista(&lista) == ERRO){
    //     printf("Erro ao destruir a lista!\n");
    //     exit(1);
    // }

}
