#include <stdio.h>

#include "lista_publica.h"

void testRemoverInicio(lLista ll) {
  void* resultNull = removerInicio(ll);
  printf("value of result Null %s \n", (char *) resultNull);
  mostrarListaInt(ll);

  int a = 2;
  inserirInicio(ll, &a);
  mostrarListaInt(ll);

  int* valueRemoved = removerInicio(ll);
  printf("valor removido do inicio %d \n\n", *valueRemoved);
  mostrarListaInt(ll);

  inserirInicio(ll, &a);
  mostrarListaInt(ll);

  int b = 3;
  inserirInicio(ll, &b);
  mostrarListaInt(ll);

  int* valueRemoved2 = removerInicio(ll);
  printf("valor removido do inicio %d \n\n", *valueRemoved2);
  mostrarListaInt(ll);

  int valor2 = 12;
  inserirInicio(ll, &valor2);
  int valor3 = 13;
  inserirInicio(ll, &valor3);
  int valor4 = 14;
  inserirInicio(ll, &valor4);
  int valor5 = 15;
  inserirInicio(ll, &valor5);
  inserirInicio(ll, &valor5);
  mostrarListaInt(ll);
  removerInicio(ll);
  mostrarListaInt(ll);
}

int main(int argc, char* argv[]) {
  lLista ll = criarLista(5, sizeof(int));

  if (ll == 0) return 1;

  testRemoverInicio(ll);
  // int r;
  // int a = 2;
  // r = inserirInicio( ll, &a );
  // mostrarListaInt( ll );

  // a = 3;
  // r = inserirInicio( ll, &a );
  // mostrarListaInt( ll );

  // a = 11;
  // r = inserirFim( ll, &a );
  // mostrarListaInt( ll );

  // a = 22;
  // r = inserirPos( ll, &a, 1 );
  // mostrarListaInt( ll );

  // r = destruirLista( ll );

  // printf("\n result %d", r);

  return 0;
}