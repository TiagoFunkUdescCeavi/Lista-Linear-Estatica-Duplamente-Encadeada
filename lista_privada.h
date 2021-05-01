#ifndef LISTA_PRIVADA_H
#define LISTA_PRIVADA_H

#include "lista_publica.h"

typedef struct Elemento{
    void * dado;
    int posicao_anterior;
    int posicao_proximo;
} Elemento;

typedef struct Lista{
    int tamanho_total_lista;
    int tamanho_elemento;
    int tamanho_atual;
    int * posicoes_ocupadas;
    int posicao_primeiro_elemento;
    int posicao_ultimo_elemento;
    Elemento ** elementos;
} Lista;

int escrever( lLista l, void * elemento, int posicao );
int procurarVazio( lLista l );

int inserirInicioVazio( lLista l, void * elemento );
int inserirInicioNaoVazio( lLista l, void * elemento );

int inserirFimVazio( lLista l, void * elemento );
int inserirFimNaoVazio( lLista l, void * elemento );

int inserirNaPosicao( lLista l, void * elemento, int posicao);

// retorna o mais valor entre dois elementos
int max(int v1, int v2);

void mostrarElemento( Elemento * el, int posicao , int posicaoOcupada);

#endif