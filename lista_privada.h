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

// logica remover o primeiro elemento
void removerPrimeiroElem(lLista l, int pos);

// logica remover o ultimo elemento
void removerUltimoElem(lLista l, int pos);

// printa todo o elemento
void mostrarElemento( Elemento * el, int posicao , int posicaoOcupada);

// printa todos os elementos da lista
void printElementosLista(lLista l);

#endif