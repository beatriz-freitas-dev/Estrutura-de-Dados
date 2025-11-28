
#ifndef LISTADUPLA_H
#define LISTADUPLA_H

typedef struct no {
    int informacao;
    struct no *ant;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    NO *fim;
} Lista;

/* criação / verificação */
Lista *cria_lista(void);
int lista_vazia(Lista *lista);

/* inserções */
int inserir_inicio(Lista *lista, int valor);
int inserir_final(Lista *lista, int valor);

/* remoções */
int remover_inicio(Lista *lista);
int remover_final(Lista *lista);

/* buscas */
int encontrar_valor(Lista *lista, int valor);     /* imprime e retorna 1 se encontrado */
int encontrar_posicao(Lista *lista, int posicao); /* posicao comecando em 1 */

/* utilitários */
void apagar_lista(Lista **lista);
void imprimir_lista(Lista *lista);

/* menu */
void menu(Lista *li);

#endif 