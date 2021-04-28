#ifndef LISTA_PRIVADA_H
#define LISTA_PRIVADA_H

#include "lista_publica.h"

typedef struct Elemento{
    void * dado;
    int posicao_anterior;
    int posicao_proximo;
};

typedef struct Lista{
    int tamanho_lista;
    int tamanho_elemento;
    int * posicao_ocupadas;
    int posicao_primeiro_elemento;
    int posicao_ultimo_elemento;
    struct Elemento * elementos;
};



#endif