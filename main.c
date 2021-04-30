#include <stdio.h>

#include "lista_publica.h"

int main( int argc, char * argv[] ){
    int r = -1;
    lLista ll = criarLista( 5, sizeof( int ) );

    if( ll == 0 ) return 1;

    int a = 2;
    r = inserirInicio( ll, &a );

    a = 3;
    r = inserirInicio( ll, &a );

    a = 11;
    r = inserirFim( ll, &a );
    mostrarLista( ll );

    a = 22;
    r = inserirPos( ll, &a, 1 );
    mostrarLista( ll );

    r = destruirLista( ll );

    return 0;
}