#include "lista_privada.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TRUE 0
#define FALSE 1
#define EMPTY -1

lLista criarLista(int tamanho, int tamanho_elemento){
    lLista ll = malloc( sizeof( Lista ) );
    ll->tamanho_total_lista = tamanho;
    ll->tamanho_elemento = tamanho_elemento;

    ll->tamanho_atual = 0;
    ll->posicao_ocupadas = malloc( tamanho * tamanho_elemento );
    for( int i = 0; i < tamanho; i++ ){
        ll->posicao_ocupadas[ i ] = FALSE;
    }

    ll->posicao_primeiro_elemento = EMPTY;
    ll->posicao_ultimo_elemento = EMPTY;
    ll->elementos = malloc( tamanho * sizeof( Lista ) );
}

int destruirLista( lLista l ){
    free( l->posicao_ocupadas );
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        free( l->elementos[ i ] );
    }
    free( l->elementos );
    free( l );
}

int reiniciarLista( lLista l ){
    l->tamanho_atual = 0;
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        l->posicao_ocupadas[ i ] = FALSE;
        free( l->elementos[ i ] );
    }
    l->posicao_primeiro_elemento = EMPTY;
    l->posicao_ultimo_elemento = EMPTY;
}

int escrever( lLista l, void * elemento, int posicao ){
    if( posicao < 0 || posicao > l->tamanho_total_lista){
        return FALSE;
    }
    l->tamanho_atual++;
    l->posicao_ocupadas[ posicao ] = TRUE;

    l->elementos[ posicao ] = (Elemento *) malloc( sizeof( Elemento ) );
    l->elementos[ posicao ]->dado = malloc( sizeof( Elemento ) );
    memcpy( l->elementos[ posicao ]->dado, elemento, l->tamanho_elemento );
    return TRUE;
}

int procurarVazio( lLista l ){
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        if( l->posicao_ocupadas[ i ] == FALSE ){
            return i;
        }
    }
    return EMPTY;
}

int inserirInicioVazio( lLista l, void * elemento ){
    escrever( l, elemento, 0 );
    l->posicao_primeiro_elemento = 0;
    l->posicao_ultimo_elemento = 0;        
    l->elementos[ 0 ]->posicao_anterior = EMPTY;
    l->elementos[ 0 ]->posicao_proximo = EMPTY;
    return TRUE;
}

int inserirInicioNaoVazio( lLista l, void * elemento ){
    int pos = procurarVazio( l );
    if( pos == EMPTY ) return FALSE;

    escrever( l, elemento, pos );

    l->elementos[ pos ]->posicao_anterior = EMPTY;
    l->elementos[ pos ]->posicao_proximo = l->posicao_primeiro_elemento;
    l->posicao_primeiro_elemento = pos;

    return TRUE;
}

int inserirInicio( lLista l, void * elemento ){
    if( l->posicao_primeiro_elemento == EMPTY ){
        return inserirInicioVazio( l, elemento );
    }
    return inserirInicioNaoVazio( l, elemento );
}

int inserirFimVazio( lLista l, void * elemento ){
    return inserirInicioVazio( l, elemento );
    // Se você parar para pensar, a lógica é a mesma
}

int inserirFimNaoVazio( lLista l, void * elemento ){
    if( l->tamanho_atual >= l->tamanho_total_lista ){
        return FALSE;
    }
    int pos = procurarVazio( l );
    if( pos == EMPTY ) return FALSE;

    escrever( l, elemento, pos );

    l->elementos[ pos ]->posicao_anterior = l->posicao_ultimo_elemento;
    l->elementos[ pos ]->posicao_proximo = EMPTY;
    l->posicao_ultimo_elemento = pos;
    return TRUE;
}

int inserirFim( lLista l, void * elemento ){
    if( l->posicao_ultimo_elemento == EMPTY ){
        return inserirFimVazio( l, elemento );
    }
    return inserirFimNaoVazio( l, elemento );
}
