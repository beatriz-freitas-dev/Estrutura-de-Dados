#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h"

/*-------------CRIA A LISTA-------------*/
Lista *cria_lista(){
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if(lista != NULL){
        lista->inicio = NULL;
        lista->fim = NULL;
    }
    return lista;
}

/*-------------VERIFICA SE A LISTA ESTÁ VAZIA-------------*/
int lista_vazia(Lista *lista){
    return (lista == NULL) || (lista->inicio == NULL);
}

/*-------------INSERIR NO INICIO-------------*/
int inserir_inicio(Lista *lista, int valor){
    if(lista == NULL) return 0;

    NO *novo = (NO*)malloc(sizeof(NO));
    if(novo == NULL) return 0;

    novo->informacao = valor;
    novo->ant = NULL;
    novo->prox = lista->inicio;

    if(lista_vazia(lista)){
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->inicio->ant = novo;
        lista->inicio = novo;
    }
    return 1;
}

/*-------------INSERIR NO FINAL-------------*/
int inserir_final(Lista *lista, int valor){
    if(lista == NULL) return 0;

    NO *novo = (NO*)malloc(sizeof(NO));
    if(novo == NULL) return 0;

    novo->informacao = valor;
    novo->prox = NULL;
    novo->ant = lista->fim;

    if(lista_vazia(lista)){
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    return 1;
}

/*-------------REMOVER ELEMENTO NO INICIO DA LISTA-------------*/
int remover_inicio(Lista *lista){
    if(lista == NULL || lista->inicio == NULL){
        printf("\nLISTA VAZIA\n");
        return 0;
    }

    NO *rem = lista->inicio;
    lista->inicio = rem->prox;

    if(lista->inicio != NULL)
        lista->inicio->ant = NULL;
    else
        lista->fim = NULL;

    free(rem);
    return 1;
}

/*-------------REMOVER ELEMENTO NO FINAL DA LISTA-------------*/
int remover_final(Lista *lista){
    if(lista == NULL || lista->inicio == NULL){
        printf("\nLISTA VAZIA\n");
        return 0;
    }

    NO *rem = lista->fim;

    if(rem->ant != NULL)
        rem->ant->prox = NULL;
    else
        lista->inicio = NULL; /* unico elemento */

    lista->fim = rem->ant;
    free(rem);
    return 1;
}

/*-------------APAGAR A LISTA-------------*/
void apagar_lista(Lista **lista){
    if(lista == NULL || *lista == NULL) return;

    NO *p = (*lista)->inicio;
    while(p != NULL){
        NO *tmp = p->prox;
        free(p);
        p = tmp;
    }
    free(*lista);
    *lista = NULL;
}

/*-------------IMPRIMIR A LISTA-------------*/
void imprimir_lista(Lista *lista){
    if(lista == NULL || lista_vazia(lista)){
        printf("\nLISTA VAZIA\n");
        return;
    }

    NO *p = lista->inicio;
    printf("\nLista -> [");
    while(p != NULL){
        printf("%d\t", p->informacao);
        p = p->prox;
    }
    printf("NULL]\n");
}

/*------------ENCONTRAR ELEMENTO A PARTIR DE UM VALOR------------*/
int encontrar_valor(Lista *lista, int valor){
    if(lista == NULL){
        printf("\nELEMENTO NAO ENCONTRADO\n");
        return 0;
    }

    NO *p = lista->inicio;
    int pos = 1;
    while(p != NULL){
        if(p->informacao == valor){
            printf("Valor %d encontrado na posicao %d\n", valor, pos);
            return 1;
        }
        p = p->prox;
        pos++;
    }
    printf("\nELEMENTO NAO ENCONTRADO\n");
    return 0;
}

/*------------ENCONTRAR ELEMENTO A PARTIR DE UMA POSIÇÃO------------*/

int encontrar_posicao(Lista *lista, int posicao){
    if(lista == NULL || posicao <= 0){
        printf("\nELEMENTO NAO ENCONTRADO\n");
        return 0;
    }

    NO *p = lista->inicio;
    int i = 1;
    while(p != NULL && i < posicao){
        p = p->prox;
        i++;
    }
    if(p == NULL){
        printf("\nELEMENTO NAO ENCONTRADO\n");
        return 0;
    } else {
        printf("Posicao %d -> %d\n", posicao, p->informacao);
        return 1;
    }
}

/*------------------------MENU------------------------*/
void menu(Lista *li){
    if(li == NULL) return;

    int op = -1, op2, valor, pos;
    while(op != 0){
        printf("\n=========ESCOLHA UMA OPCAO=========\n"
               "1 - Inserir elemento\n"
               "2 - Remover elemento\n"
               "3 - Encontrar elemento\n"
               "4 - Destruir lista\n"
               "5 - Imprimir lista\n"
               "0 - Sair\n\nOpcao escolhida: ");
        if(scanf("%d", &op) != 1) {
            int c; while((c=getchar())!='\n' && c!=EOF);
            op = -1;
            continue;
        }

        switch(op){
            case 1:
                printf("\n1 - Inicio\n2 - Fim\nOpcao: ");
                scanf("%d", &op2);
                printf("Digite o numero que sera inserido: ");
                scanf("%d", &valor);

                if(op2 == 1)
                    inserir_inicio(li, valor);
                else
                    inserir_final(li, valor);
                break;

            case 2:
                printf("\n1 - Remover do Inicio\n2 - Remover do Fim\nOpcao: ");
                scanf("%d", &op2);
                if(op2 == 1)
                    remover_inicio(li);
                else
                    remover_final(li);
                break;

            case 3:
                printf("\n1 - Buscar por Valor\n2 - Buscar por Posicao\nOpcao: ");
                scanf("%d", &op2);
                if(op2 == 1){
                    printf("Valor a buscar: ");
                    scanf("%d", &valor);
                    encontrar_valor(li, valor);
                } else {
                    printf("Posicao a buscar (comeca em 1): ");
                    scanf("%d", &pos);
                    encontrar_posicao(li, pos);
                }
                break;

            case 4:
                apagar_lista(&li);
                printf("Lista destruida.\n");
                
                li = cria_lista();
                break;

            case 5:
                imprimir_lista(li);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}