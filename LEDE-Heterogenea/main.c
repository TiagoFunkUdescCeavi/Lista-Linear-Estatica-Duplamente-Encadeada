#include <stdio.h>

#include "Lista_publica.h"

#define ORDEM 1000
#define N_INSERE 10 * ORDEM
#define N_REMOVE 3 * ORDEM

void inserir10000Elementos(pLista ll) {
  int r = 0;
  int value = 3;
  for (int i = 0; i < N_INSERE; i++) {
    inserir_inicio(ll, &value, sizeof(int), &r);
    printf("Inserindo, i: %d, r: %d\n", i, r);
  }
}

void remover3000Elementos(pLista ll) {
  int *r = malloc(sizeof(int));
  for (int i = 0; i < N_REMOVE; i++) {
    remover_inicio(ll, r);
    printf("Removendo, i: %d, r: %d\n", i, *r);
  }
}

int main() {
  int resultado;
  // char elemento1[] = {'a', 'b', 'c', '\0'};
  // char *retorno;

  pLista ll = criar_lista(sizeof(int), &resultado);

  inserir10000Elementos(ll);
  printf("Contador pulos: %d\n", get_count());

  remover3000Elementos(ll);
  printf("Contador pulos: %d\n", get_count());


  // inserir_inicio(lista, elemento1, 4*sizeof(char), &resultado);
  // printf("resultado: %i\n", resultado);
  // retorno = buscar_inicio(lista, &resultado);
  // printf("resultado: %i\n", resultado);
  // printf("retorno: %s\n", (char *)retorno);

  // char elemento2[] = {'c', 'd', 'e', '\0'};
  // inserir_fim(lista, elemento2, 4*sizeof(char), &resultado);
  // printf("resultado: %i\n", resultado);
  // retorno = buscar_fim(lista, &resultado);
  // printf("resultado: %i\n", resultado);
  // printf("retorno: %s\n", (char *)retorno);

  // int elemento3 = 15;
  // inserir_pos(lista, 2, &elemento3, sizeof(int), &resultado);
  // printf("resultado: %i\n", resultado);
  // retorno = buscar_pos(lista, 2, &resultado);
  // printf("resultado: %i\n", resultado);
  // printf("retorno: %i\n", *(int *)retorno);

  // remover_pos(lista, 2, &resultado);
  // printf("resultado: %i\n", resultado);
  // retorno = buscar_pos(lista, 2, &resultado);
  // printf("resultado: %i\n", resultado);
  // printf("retorno: %i\n", (int *)retorno);

  // reiniciar_lista(lista, &resultado);
  // printf("resultado: %i\n", resultado);
  // retorno = buscar_fim(lista, &resultado);
  // printf("resultado: %i\n", resultado);
  // printf("retorno: %s\n", (char *)retorno);

  // destruir_lista(lista, &resultado);
  // printf("resultado: %i\n", resultado);

  return 0;
}
