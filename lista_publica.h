#ifndef LISTA_PUBLICA_H
#define LISTA_PUBLICA_H

typedef struct Lista *lLista;

lLista criarLista(int tamanho, int tamanho_elemento);
int destruirLista( lLista l );
int reiniciarLista( lLista l );

int inserirInicio( lLista l, void * elemento );
int inserirFim( lLista l, void * elemento );
int inserirPos( lLista l, void * elemento, int posicao );

void * removerInicio( lLista l );
void * removerFim( lLista l );
void * removerPos( lLista l, int posicao );

void * buscarInicio( lLista l );
void * buscarFim( lLista l );
void * buscarPos( lLista l, int posicao );

void mostrarLista( lLista l );

#endif