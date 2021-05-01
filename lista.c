#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_privada.h"

#define TRUE 0
#define FALSE 1
#define EMPTY -1

lLista criarLista(int tamanho, int tamanho_elemento) {
  if (tamanho <= 0) {
    return NULL;
  }

  lLista ll = malloc(sizeof(Lista));
  ll->tamanho_total_lista = tamanho;
  ll->tamanho_elemento = tamanho_elemento;

  ll->tamanho_atual = 0;
  ll->posicoes_ocupadas = malloc(tamanho * sizeof(int));
  for (int i = 0; i < tamanho; i++) {
    ll->posicoes_ocupadas[i] = FALSE;
  }

  ll->posicao_primeiro_elemento = EMPTY;
  ll->posicao_ultimo_elemento = EMPTY;
  ll->elementos = malloc(tamanho * sizeof(Elemento));

  return ll;
}

int destruirLista(Lista* l) {
  if (l == NULL || !l || l->tamanho_total_lista <= 0) {
    return FALSE;
  }

  for (int i = 0; i < l->tamanho_total_lista; i++) {
    if (l->posicoes_ocupadas[i] == TRUE) {
      free(l->elementos[i]->dado);
      free(l->elementos[i]);
    }
  }
  free(l->elementos);
  free(l->posicoes_ocupadas);
  free(l);

  return TRUE;
}

int reiniciarLista(lLista l) {
  l->tamanho_atual = 0;
  for (int i = 0; i < l->tamanho_total_lista; i++) {
    if (l->posicoes_ocupadas[i] == TRUE) {
      free(l->elementos[i]->dado);
      free(l->elementos[i]);
    }
    l->posicoes_ocupadas[i] = FALSE;
  }
  l->posicao_primeiro_elemento = EMPTY;
  l->posicao_ultimo_elemento = EMPTY;

  return TRUE;
}

int escrever(lLista l, void *elemento, int posicao) {
  if (posicao < 0 || posicao > l->tamanho_total_lista) {
    return FALSE;
  }
  l->tamanho_atual++;
  l->posicoes_ocupadas[posicao] = TRUE;

  l->elementos[posicao] = (Elemento *)malloc(sizeof(struct Elemento));
  l->elementos[posicao]->dado = malloc(l->tamanho_elemento);
  memcpy(l->elementos[posicao]->dado, elemento, l->tamanho_elemento);

  return TRUE;
}

int procurarVazio(lLista l) {
  for (int i = 0; i < l->tamanho_total_lista; i++) {
    if (l->posicoes_ocupadas[i] == FALSE) {
      return i;
    }
  }

  return EMPTY;
}

int inserirInicioVazio(lLista l, void *elemento) {
  escrever(l, elemento, 0);
  l->posicao_primeiro_elemento = 0;
  l->posicao_ultimo_elemento = 0;
  l->elementos[0]->posicao_anterior = EMPTY;
  l->elementos[0]->posicao_proximo = EMPTY;

  return TRUE;
}

int inserirInicioNaoVazio(lLista l, void *elemento) {
  int pos = procurarVazio(l);
  if (pos == EMPTY) return FALSE;

  escrever(l, elemento, pos);

  l->elementos[l->posicao_primeiro_elemento]->posicao_anterior = pos;

  l->elementos[pos]->posicao_anterior = l->posicao_ultimo_elemento;
  l->elementos[pos]->posicao_proximo = l->posicao_primeiro_elemento;

  if (l->posicoes_ocupadas[l->posicao_ultimo_elemento] == TRUE) {
    l->elementos[l->posicao_ultimo_elemento]->posicao_proximo = pos;
  }

  l->posicao_primeiro_elemento = pos;

  return TRUE;
}

int inserirInicio(lLista l, void *elemento) {
  if (l->posicao_primeiro_elemento == EMPTY) {
    return inserirInicioVazio(l, elemento);
  }
  return inserirInicioNaoVazio(l, elemento);
}

int inserirFimVazio(lLista l, void *elemento) {
  return inserirInicioVazio(l, elemento);
  // Se você parar para pensar, a lógica é a mesma
}

int inserirFimNaoVazio(lLista l, void *elemento) {
  if (l->tamanho_atual >= l->tamanho_total_lista) {
    return FALSE;
  }
  int pos = procurarVazio(l);
  if (pos == EMPTY) return FALSE;

  escrever(l, elemento, pos);

  l->elementos[l->posicao_ultimo_elemento]->posicao_proximo = pos;

  l->elementos[pos]->posicao_anterior = l->posicao_ultimo_elemento;
  l->elementos[pos]->posicao_proximo = l->posicao_primeiro_elemento;
  l->posicao_ultimo_elemento = pos;

  if (l->posicoes_ocupadas[l->posicao_primeiro_elemento] == TRUE) {
    l->elementos[l->posicao_primeiro_elemento]->posicao_anterior = pos;
  }
  return TRUE;
}

int inserirFim(lLista l, void *elemento) {
  if (l->posicao_ultimo_elemento == EMPTY) {
    return inserirFimVazio(l, elemento);
  }
  return inserirFimNaoVazio(l, elemento);
}

int inserirNaPosicao(lLista l, void *elemento, int posicao) {
  int pos = procurarVazio(l);
  if (pos == EMPTY) return FALSE;  // verifica se tem lugar para adicionar

  escrever(l, elemento, pos);

  int cont = 0;
  Elemento *el = l->elementos[l->posicao_primeiro_elemento];
  int p = l->posicao_primeiro_elemento;
  while (cont != posicao) {
    p = el->posicao_proximo;
    el = l->elementos[el->posicao_proximo];
    cont++;
  }
  l->elementos[pos]->posicao_anterior = el->posicao_anterior;
  l->elementos[pos]->posicao_proximo = p;
  l->elementos[l->elementos[p]->posicao_anterior]->posicao_proximo = pos;
  l->elementos[p]->posicao_anterior = pos;
  return TRUE;
}

int inserirPos(lLista l, void *elemento, int posicao) {
  if (posicao < 0 || posicao >= l->tamanho_atual) {
    return FALSE;
  } else if (posicao == 0) {
    return inserirInicio(l, elemento);
  } else if (posicao == l->tamanho_atual - 1) {
    return inserirFim(l, elemento);
  }
  return inserirNaPosicao(l, elemento, posicao);
}

// removerInicio retorna Null caso a lista esteja vazia ou retorna o elemento removido
void *removerInicio(lLista l) {
  return removerPos(l, l->posicao_primeiro_elemento);
}

void removerPrimeiroElem(lLista l, int pos) {
  if (l->posicoes_ocupadas[pos] == TRUE) {
    l->elementos[pos]->posicao_anterior = l->posicao_ultimo_elemento;
  }

  if (l->posicao_ultimo_elemento != EMPTY && l->posicoes_ocupadas[l->posicao_ultimo_elemento] == TRUE) {
    l->elementos[l->posicao_ultimo_elemento]->posicao_proximo = pos;
  }

  l->posicao_primeiro_elemento = pos;
}

void removerUltimoElem(lLista l, int pos) {
  if (l->posicoes_ocupadas[pos] == TRUE) {
    l->elementos[pos]->posicao_proximo = l->posicao_primeiro_elemento;
  }

  if (l->posicao_primeiro_elemento != EMPTY && l->posicoes_ocupadas[l->posicao_primeiro_elemento] == TRUE) {
    l->elementos[l->posicao_primeiro_elemento]->posicao_anterior = pos;
  }

  l->posicao_ultimo_elemento = pos;
}

void *removerPos(lLista l, int posicao) {
  if (l->tamanho_atual <= 0) {  // lista esta vazia
    return NULL;
  }

  if (posicao >= l->tamanho_total_lista) {  // posicao to remove maior que tamanho total lista
    return NULL;
  }

  if (l->posicoes_ocupadas[posicao] == FALSE) {
    // posicao ja esta desocupada
    return NULL;
  }

  Elemento *el = l->elementos[posicao];     // elemento na posicao
  int pos_proximo = el->posicao_proximo;    // armazena a posicao do proximo
  int pos_anterior = el->posicao_anterior;  // armazena a posicao do anterior

  // desocupa posicao
  l->posicoes_ocupadas[posicao] = FALSE;

  // copia o dado retorno
  void *dado = malloc(l->tamanho_elemento);
  memcpy(dado, el->dado, l->tamanho_elemento);

  // limpa o elemento na posicao
  free(l->elementos[posicao]->dado);
  free(l->elementos[posicao]);

  l->tamanho_atual--;

  // caso a lista fique vazia é só retornar o valor
  if (l->tamanho_atual == 0) {
    printf("\nREMOVE POS - lista vazia\n");
    l->posicao_primeiro_elemento = EMPTY;
    l->posicao_ultimo_elemento = EMPTY;
    return dado;
  }

  // esta removendo na primeira posicao
  if (l->posicao_primeiro_elemento == posicao) {
    printf("\n REMOVE PRIMEIRA POSICAO %d\n", posicao);
    removerPrimeiroElem(l, pos_proximo);
    return dado;
  }

  // esta removendo na ultima posicao
  if (l->posicao_ultimo_elemento == posicao) {
    printf("\n REMOVE ULTIMA POSICAO %d\n", posicao);
    removerUltimoElem(l, pos_anterior);
    return dado;
  }

  // caso a lista tenha mais valores, deve zerar a posicao anterior do primeiro elemento
  if (l->posicoes_ocupadas[pos_proximo] == TRUE) {
    l->elementos[pos_proximo]->posicao_anterior = pos_anterior;
  }
  if (l->posicoes_ocupadas[pos_anterior] == TRUE) {
    l->elementos[pos_anterior]->posicao_proximo = pos_proximo;
  }

  return dado;
}

void *removerFim(lLista l) {
  return removerPos(l, l->posicao_ultimo_elemento);
}

void *buscarInicio(lLista l) {
  return buscarPos(l, l->posicao_primeiro_elemento);
}

void *buscarFim(lLista l) {
  return buscarPos(l, l->posicao_ultimo_elemento);
}

void *buscarPos(lLista l, int posicao) {
  if (l->tamanho_atual <= 0) {  // lista esta vazia
    return NULL;
  }

  if (posicao >= l->tamanho_total_lista) {  // posicao maior que tamanho total lista
    return NULL;
  }

  if (l->posicoes_ocupadas[posicao] == FALSE) {
    // posicao vazia
    return NULL;
  }

  // busca o elemento para copiar o dado
  Elemento *el = l->elementos[posicao];
  void *dado = malloc(l->tamanho_elemento);
  memcpy(dado, el->dado, l->tamanho_elemento);

  return dado;
}

void mostrarListaInt(lLista l) {
  printf("TAMANHO_TOTAL_LISTA: %d\n", l->tamanho_total_lista);
  printf("TAMANHO_ELEMENTO: %d\n", l->tamanho_elemento);
  printf("TAMANHO_ATUAL: %d\n", l->tamanho_atual);

  printf("POSICOES_OCUPADAS: ");
  for (int i = 0; i < l->tamanho_total_lista; i++) {
    printf("%d, ", l->posicoes_ocupadas[i]);
  }

  printf("\n");
  printf("POSICAO_PRIMEIRO_ELEMENTO: %d\n", l->posicao_primeiro_elemento);
  printf("POSICAO_ULTIMO_ELEMENTO: %d\n", l->posicao_ultimo_elemento);
  if (l->tamanho_atual <= 0) {
    printf("\n\n");
    return;
  }
  printf("ELEMENTOS NA LISTA:\n");
  for (int i = 0; i < l->tamanho_total_lista; i++) {
    mostrarElemento(l->elementos[i], i, l->posicoes_ocupadas[i]);
  }
  printf("POSICOES EM ORDEM: ");
  int a = l->posicao_primeiro_elemento;
  Elemento *el = l->elementos[l->posicao_primeiro_elemento];
  while (el != 0 && el->posicao_proximo != l->posicao_primeiro_elemento) {
    printf("%d, ", a);
    if (el->posicao_proximo == EMPTY || el->posicao_proximo == l->posicao_primeiro_elemento) {
      break;
    }

    a = el->posicao_proximo;
    el = l->elementos[el->posicao_proximo];
  }
  printf("\n");
  printf("ELEMENTOS EM ORDEM: ");
  int *d = 0;
  el = l->elementos[l->posicao_primeiro_elemento];
  while (el != 0) {
    d = el->dado;
    printf("%d, ", *d);
    if (el->posicao_proximo == EMPTY || el->posicao_proximo == l->posicao_primeiro_elemento) break;
    el = l->elementos[el->posicao_proximo];
  }
  printf("\n");
  // Ajuda a depurar ;)
  printf("ELEMENTOS EM ORDEM CONTRÁRIA: ");
  d = 0;
  el = l->elementos[l->posicao_ultimo_elemento];
  while (el != 0) {
    d = el->dado;
    printf("%d, ", *d);
    if (el->posicao_anterior == EMPTY || el->posicao_anterior == l->posicao_ultimo_elemento) break;
    el = l->elementos[el->posicao_anterior];
  }
  printf("\n\n\n");
}

void mostrarElemento(Elemento *el, int posicao, int posicaoOcupada) {
  printf("%d:", posicao);
  if (el == 0 || posicaoOcupada == FALSE) {
    printf("Vazio\n");
    return;
  }
  int *d = el->dado;
  printf("\tDADO: %d\n", *d);
  printf("\tPOSICAO_ANTERIOR: %d\n", el->posicao_anterior);
  printf("\tPOSICAO_PROXIMO: %d\n", el->posicao_proximo);
}

void printElementosLista(lLista l) {
  printf("ELEMENTOS NA LISTA:\n");
  for (int i = 0; i < l->tamanho_total_lista; i++) {
    mostrarElemento(l->elementos[i], i, l->posicoes_ocupadas[i]);
  }
}