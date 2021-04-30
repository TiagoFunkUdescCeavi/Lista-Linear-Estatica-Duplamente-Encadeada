#include <stdio.h>

#include "lista_publica.h"

int main( int argc, char * argv[] ){
    printf("vai\n");
    lLista ll = criarLista( 5, sizeof( int ) );
    int a = 2;

    if( ll == 0 ) return 1;

    printf("vai\n");
    inserirInicio( ll, &a );

    inserirFim( ll, &a );

    // destruirLista( ll );
    return 0;
}