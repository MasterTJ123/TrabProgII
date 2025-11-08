#ifndef LISTA_DINAMICA_ENCADEADA_H
#define LISTA_DINAMICA_ENCADEADA_H

#include "raylib.h"

struct elemento {
    Rectangle pos;
    struct elemento *prox;
};

typedef struct elemento Elemento;

typedef Elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, Rectangle pos);
int busca_lista_pos(const Lista* li, Rectangle pos);

int remove_lista_final(Lista* li);
int tamanho_lista(const Lista* li);
int lista_vazia(const Lista* li);
int lista_cheia(Lista* li);

#endif