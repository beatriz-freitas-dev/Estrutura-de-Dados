#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h"

int main(void){
    Lista *lista = cria_lista();
    if(lista == NULL){
        fprintf(stderr, "Falha ao criar lista\n");
        return 1;
    }

    menu(lista);

    /* garantia: apagar antes de sair */
    apagar_lista(&lista);
    return 0;
}