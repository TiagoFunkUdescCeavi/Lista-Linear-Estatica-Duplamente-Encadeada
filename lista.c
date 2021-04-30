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
    ll->posicoes_ocupadas = malloc( tamanho * tamanho_elemento );
    for( int i = 0; i < tamanho; i++ ){
        ll->posicoes_ocupadas[ i ] = FALSE;
    }

    ll->posicao_primeiro_elemento = EMPTY;
    ll->posicao_ultimo_elemento = EMPTY;
    ll->elementos = malloc( tamanho * sizeof( Lista ) );
}

int destruirLista( lLista l ){
    free( l->posicoes_ocupadas );
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        free( l->elementos[ i ] );
    }
    free( l->elementos );
    free( l );
}

int reiniciarLista( lLista l ){
    l->tamanho_atual = 0;
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        l->posicoes_ocupadas[ i ] = FALSE;
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
    l->posicoes_ocupadas[ posicao ] = TRUE;

    l->elementos[ posicao ] = (Elemento *) malloc( sizeof( Elemento ) );
    l->elementos[ posicao ]->dado = malloc( sizeof( Elemento ) );
    memcpy( l->elementos[ posicao ]->dado, elemento, l->tamanho_elemento );
    return TRUE;
}

int procurarVazio( lLista l ){
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        if( l->posicoes_ocupadas[ i ] == FALSE ){
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

    l->elementos[ l->posicao_primeiro_elemento ]->posicao_anterior = pos;

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

    l->elementos[ l->posicao_ultimo_elemento ]->posicao_proximo = pos;

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

int inserirNaPosicao( lLista l, void * elemento, int posicao){
    int pos = procurarVazio( l );
    if( pos == EMPTY ) return FALSE;

    escrever( l, elemento, pos );

    int cont = 0;
    Elemento * el = l->elementos[ l->posicao_primeiro_elemento ];
    int p = l->posicao_primeiro_elemento;
    while( cont != posicao ){
        p = el->posicao_proximo;
        el = l->elementos[ el->posicao_proximo ];
        cont++;
    }
    l->elementos[ pos ]->posicao_anterior = el->posicao_anterior;
    l->elementos[ pos ]->posicao_proximo = p;
    l->elementos[ l->elementos[ p ]->posicao_anterior ]->posicao_proximo = pos;
    l->elementos[ p ]->posicao_anterior = pos;
    return TRUE;
}

int inserirPos( lLista l, void * elemento, int posicao ){
    if( posicao < 0 || posicao >= l->tamanho_atual ){
        return FALSE;
    } else if( posicao == 0 ){
        return inserirInicio( l, elemento );
    }else if(posicao == l->tamanho_atual-1 ) {
        return inserirFim( l, elemento );
    }
    return inserirNaPosicao( l, elemento, posicao );
}

void mostrarLista( lLista l ){
    printf("TAMANHO_TOTAL_LISTA: %d\n", l->tamanho_total_lista );
    printf("TAMANHO_ELEMENTO: %d\n", l->tamanho_elemento );
    printf("TAMANHO_ATUAL: %d\n", l->tamanho_atual );
    printf("POSICOES_OCUPADAS: ");
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        printf("%d, ", l->posicoes_ocupadas[ i ] );
    }
    printf("\n");
    printf("POSICAO_PRIMEIRO_ELEMENTO: %d\n", l->posicao_primeiro_elemento );
    printf("POSICAO_ULTIMO_ELEMENTO: %d\n", l->posicao_ultimo_elemento );
    printf("ELEMENTOS NA LISTA:\n");
    for( int i = 0; i < l->tamanho_total_lista; i++ ){
        mostrarElemento( l->elementos[ i ], i );
    }
    printf("POSICOES EM ORDEM: ");
    int a = l->posicao_primeiro_elemento;
    Elemento * el = l->elementos[ l->posicao_primeiro_elemento ];
    while( el != 0 ){
        printf("%d, ",a);
        if( el->posicao_proximo == EMPTY ) break;
        a = el->posicao_proximo;
        el = l->elementos[ el->posicao_proximo ];
    }
    printf("\n");
    printf("ELEMENTOS EM ORDEM: ");
    int * d = 0;
    el = l->elementos[ l->posicao_primeiro_elemento ];
    while( el != 0 ){
        d = el->dado;
        printf("%d, ",*d);
        if( el->posicao_proximo == EMPTY ) break;
        el = l->elementos[ el->posicao_proximo ];
    }
    printf("\n");
    // Ajuda a depurar ;)
    printf("ELEMENTOS EM ORDEM CONTRÁRIA: ");
    d = 0;
    el = l->elementos[ l->posicao_ultimo_elemento ];
    while( el != 0 ){
        d = el->dado;
        printf("%d, ",*d);
        if( el->posicao_anterior == EMPTY ) break;
        el = l->elementos[ el->posicao_anterior ];
    }
    printf("\n");
}

void mostrarElemento( Elemento * el, int posicao ){
    printf("%d:",posicao);
    if( el == 0 ){
        printf("Vazio\n");
        return ;
    }
    int * d = el->dado;
    printf("\tDADO: %d\n", *d );
    printf("\tPOSICAO_ANTERIOR: %d\n", el->posicao_anterior );
    printf("\tPOSICAO_PROXIMO: %d\n", el->posicao_proximo );
}