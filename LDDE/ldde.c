#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ldde_privada.h"

int contador_pulos = 0;

int CriarLista(pldde *lista, int tamanho_dados){

    /* Aloca o espa�o e verifica o sucesso */
    pldde tmp_lista = (pldde) malloc(sizeof(ldde));
    if(tmp_lista == NULL){
        printf("Erro: Aloca��o de mem�ria para cria��o da lista falhou!\n");
        return ERRO;
    }

    /* Inicializa os ponteiros da lista */
    tmp_lista->tamanho_dados = tamanho_dados;
    tmp_lista->inicio = tmp_lista->fim = NULL;
    tmp_lista->quantidade_nos = 0;

    /* Atualiza o ponteiro externo */
    *lista = tmp_lista;
    return SUCESSO;
}

int ReiniciarLista(pldde lista){
    /* Caso a lista n�o exista, informa o erro */
    if(lista == NULL){
        printf("Erro: Ponteiro para lista nulo, lista j� destru�da ou n�o iniciada!\n");
        return ERRO;
    }
    
    /* Percorre a lista removendo os n�s */
    noLdde * no = NULL; 
    while(lista->inicio != NULL){
        no = lista->inicio;
        lista->inicio = lista->inicio->prox;
        free(no->dados);
        free(no);
    }
    return SUCESSO;
}

int DestruirLista(pldde *lista){
    /* Chama a Reinicializa��o da lista para limpar todos os n�s */
    if(ReiniciarLista(*lista) == ERRO)
        return ERRO;

    /* Dest�i o descritor da lista */
    free(*lista);
    *lista = NULL;
    return SUCESSO; 
}

/* Fun��o wrapper para inser��o no in�cio utilizando a InserirPos */
int InserirInicio(pldde lista, void * elemento){
    return InserirPos(lista, elemento, 0);
}

/* Fun��o wrapper para inser��o no final utilizando a InserirPos */
int InserirFim(pldde lista, void * elemento){
    return InserirPos(lista, elemento, lista->quantidade_nos);
}

int InserirPos(pldde lista, void * elemento, int posicao){
    int i = 0;
    noLdde * atual = NULL;
    
    /* Se a posi��o informada for maior que a quantidade de n�s, retorna erro */
    if(posicao > lista->quantidade_nos){
        printf("Erro: Posi��o inexistente!\n");
        return ERRO;
    }

    /* Aloca o espa�o para o novo n� e verifica sucesso */
    noLdde * novo_no = (noLdde *) malloc(sizeof(noLdde));
    if(novo_no == NULL){
        printf("Erro: Aloca��o de mem�ria para cria��o de n� falhou!\n");
        return ERRO;
    }

    /* Inicializa os ponteiros do novo n� */
    novo_no->prox = novo_no->ant = NULL;
    contador_pulos++;
    contador_pulos++;

    /* Aloca o espa�o para os dados e verifica sucesso */ 
    novo_no->dados = (void *) malloc(lista->tamanho_dados);
    if(novo_no->dados == NULL){
        printf("Erro: Aloca��o de mem�ria para o dado falhou!\n");
        return ERRO;
    }

    /* Copia o novo elemento para o n� */
    memcpy(novo_no->dados, elemento, lista->tamanho_dados);

    /* Percorre a lista para encontrar o elemento na posi��o especificada */
    atual = lista->inicio;
    contador_pulos++;
    for(i = 0; i < posicao; i++)
        atual = atual->prox;
        contador_pulos++;

    /* Caso o valor do n� seja nulo, ent�o a inser��o deve ser no final ou n�o h� elementos na lista */
    if(atual == NULL){
        /* Atualiza os ponteiros de acordo com o caso espec�fico */
        if(posicao == 0){
            lista->inicio = lista->fim = novo_no;
            contador_pulos++;
            contador_pulos++;
        }else{
            novo_no->ant = lista->fim;
            contador_pulos++;
            contador_pulos++;
            lista->fim->prox = novo_no;
            contador_pulos++;
            contador_pulos++;
            lista->fim = novo_no;
            contador_pulos++;
        }
        lista->quantidade_nos++;
        return SUCESSO;
    }

    /* Atualiza os ponteiros caso a inser��o seja de fato no meio da lista */
    novo_no->prox = atual;
    contador_pulos++;
    novo_no->ant = atual->ant;
    contador_pulos++;
    contador_pulos++;
    atual->ant = novo_no;
    contador_pulos++;

    /* Se o elemento foi inserido no in�cio (para o caso em que j� haviam elementos na lista), o */
    /* ponteiro da lista deve ser atualizado */
    if(posicao == 0)
        lista->inicio = novo_no; contador_pulos++;

    lista->quantidade_nos++;

    return SUCESSO; 
}

/* Fun��o wrapper para buscar no in�cio utilizando a BuscarPos */
void * BuscarInicio(pldde lista){
    return lista->inicio->dados;
}

/* Fun��o wrapper para buscar no fim utilizando a BuscarPos */
void * BuscarFim(pldde lista){
    return lista->fim->dados;
}

void * BuscarPos(pldde lista, int posicao){
    int i = 0;
    noLdde * atual = NULL;

    /* Percorre a lista buscando pelo n� na posi��o informada */
    atual = lista->inicio;
    contador_pulos++;
    for(i = 0; i < posicao && atual->prox != NULL; i++){
        atual = atual->prox;
        contador_pulos++;
        contador_pulos++;
    }
    contador_pulos++;

    /* Caso o n� seja nulo, ent�o a posi��o informada n�o existe */
    if(atual == NULL){
        printf("Erro: Posi��o inexistente!\n");
        return NULL;
    }

    return atual->dados;
}

/* Fun��o wrapper para remover do in�cio utilizando a RemoverPos */
int RemoverInicio(pldde lista){
    return RemoverPos(lista, 0);
}

/* Fun��o wrapper para remover do fim utilizando a RemoverPos */
int RemoverFim(pldde lista){
    return RemoverPos(lista, lista->quantidade_nos - 1);
}

int RemoverPos(pldde lista, int posicao){
    int i = 0;
    noLdde * atual = NULL;

    /* Caso a posi��o informada seja maior ou igual � quantidade de n�s, retorna erro */
    if(posicao >= lista->quantidade_nos){
        printf("Erro: Posi��o inexistente!\n");
        return ERRO;
    }

    /* Percorre a lista procurando pelo elemento na posi��o informada */
    atual = lista->inicio;
    contador_pulos++;
    for(i = 0; i < posicao; i++)
        atual = atual->prox; contador_pulos++;

    /* Atualiza os ponteiros de acordo com o caso espec�fico (in�cio, fim ou meio) */
    if(posicao == 0){
        lista->inicio = atual->prox;
        contador_pulos++;
        contador_pulos++;

        lista->inicio->ant = NULL;
        contador_pulos++;
        contador_pulos++;

    }else if(posicao == lista->quantidade_nos - 1){
        lista->fim = atual->ant;
        contador_pulos++;
        contador_pulos++;
        lista->fim->prox = NULL;
        contador_pulos++;contador_pulos++;
    }else{
        noLdde * aux = atual->prox;
        contador_pulos++;
        atual->ant->prox = aux;
        contador_pulos++;contador_pulos++;
        atual->prox->ant = atual->ant;
        contador_pulos++;contador_pulos++;contador_pulos++;
    }

    free(atual->dados);
    free(atual);
    
    lista->quantidade_nos--;
    return SUCESSO;
}

int get_count( pldde ll ){
  return contador_pulos;
}