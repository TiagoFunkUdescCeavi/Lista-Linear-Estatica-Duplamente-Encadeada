#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista_publico.h"
#include<time.h>

#define ORDEM 1000
#define N_INSERE 10*ORDEM
#define N_REMOVE 3*ORDEM

void inserir10000Elementos( pLista lista ){
  for( int i = 0; i < N_INSERE; i++ ){
    
    int result;
    int* valorInserido = malloc(sizeof(int*));
    inserirInicio(lista, &i, valorInserido, &result);
    printf("Inserindo, i: %d \n", i);
  }
}

void remover3000Elementos( pLista lista ){
  for( int i = 0; i < N_REMOVE; i++ ){
    int result;
    int* valorRemovido = malloc(sizeof(int*));
    removerInicio(lista, valorRemovido, &result);
    printf("Removendo, i: %d\n", i);
  }
}

int main(void)
{
    int resultado, resultado2;

    //criar lista
    pLista lista = criarLista(sizeof(int *), &resultado);

    inserir10000Elementos(lista);
    printf("Contador pulos: %d\n", get_count(lista) );

    remover3000Elementos(lista);
    printf("Contador pulos: %d\n", get_count(lista));



   /*

    int* valorInserido = malloc(sizeof(int*));
    int* valorRemovido = malloc(sizeof(int*));
    int* valorBuscado = malloc(sizeof(int*));

    // insercao
    int valor = 1;
    int valor2 = 2;
    int valor3 = 3;
    int valor4 = 4;

    inserirInicio(lista, &valor, valorInserido, &resultado);
    printf("Valor inserido: %d \n", *valorInserido);

    inserirInicio(lista, &valor2, valorInserido, &resultado);
    printf("Valor inserido: %d \n", *valorInserido);

    inserirFim(lista, &valor3, valorInserido, &resultado);
    printf("Valor inserido: %d \n", *valorInserido);

    // inserirPos(lista, &valor4, valorInserido, 2, &resultado);
    // printf("Valor inserido: %d \n", *valorInserido);

    // printf("\n------------------------------------\n");

    // valorBuscado = buscarInicio(lista, &resultado);
    // printf("Valor buscado: %d \n", *valorBuscado);

    // valorBuscado = buscarFim(lista, &resultado);
    // printf("Valor buscado: %d \n", *valorBuscado);

    // valorBuscado = buscarPos(lista,1, &resultado);
    // printf("Valor buscado: %d \n", *valorBuscado);

    // printf("\n------------------------------------\n");

    /*removerInicio(lista, valorRemovido, &resultado2);
    printf("Valor removido: %d \n", *valorRemovido);

    removerInicio(lista, valorRemovido, &resultado2);
    printf("Valor removido: %d \n", *valorRemovido);

    removerInicio(lista, valorRemovido, &resultado2);
    printf("Valor removido: %d \n", *valorRemovido);

    removerFim(lista, valorRemovido, &resultado2);
    printf("Valor removido: %d \n", *valorRemovido);

    ///removerPos(lista, valorRemovido, 1, &resultado2);
    //printf("Valor removido: %d \n", *valorRemovido);

    // // destruir lista
    // destruirLista(lista, &resultado);
    // if(resultado == 0) {
    //     printf("Lista destru??da!\n");
    // }

    /*
    //TESTE CHAR

    char* valorInserido = malloc(sizeof(char*));
    char* valorRemovido = malloc(sizeof(char*));
    char* valorBuscado = malloc(sizeof(char*));

    char nomea[] = "Fulano";
    inserirFim(lista,nomea , valorInserido, &resultado);
    printf("Valor inserido: %s \n", valorInserido);

    char nomeb[] = "kkk";
    inserirFim(lista,nomeb , valorInserido, &resultado);
    printf("Valor inserido: %s \n", valorInserido);

    char nomec[] = "aaaaa";
    inserirPos(lista, nomec , valorInserido, 0, &resultado);
    printf("Valor inserido: %s \n", valorInserido);

    imprimir(lista);

    printf("\n------------------------------------\n");

    valorBuscado = buscarInicio(lista, &resultado);
    printf("Valor buscado: %s \n", valorBuscado);

    valorBuscado = buscarFim(lista, &resultado);
    printf("Valor buscado: %s \n", valorBuscado);

    valorBuscado = buscarPos(lista,1, &resultado);
    printf("Valor buscado: %s \n", valorBuscado);

    printf("\n------------------------------------\n");

    imprimir(lista);
    removerInicio(lista, valorRemovido, &resultado2);
    printf("Valor removido: %s \n", valorRemovido);

    removerFim(lista, valorRemovido, &resultado2);
    printf("Valor removido: %s \n", valorRemovido);

    imprimir(lista);

    removerPos(lista, valorRemovido, 0, &resultado2);
    printf("Valor removido: %s \n", valorRemovido);

    // destruir lista
    destruirLista(lista, &resultado);
    if(resultado == 0) {
        printf("\nLista destru??da!\n");
    }
    */


    return 0;
}
