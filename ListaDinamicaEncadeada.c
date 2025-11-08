#include <stdio.h>
#include <stdlib.h>
#include "ListaDinamicaEncadeada.h"

Lista* cria_lista() {
    Lista* li = malloc(sizeof(Lista));
    if (li != NULL) {
        *li = NULL;
    }
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        while (*li != NULL) {
            Elemento *no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, const Rectangle pos) {
    if (li == NULL) {
        return 0;
    }
    Elemento *no = malloc(sizeof(Elemento));
    if (no == NULL) {
        return 0;
    }
    no->pos = pos;
    no->prox = NULL;
    if (*li == NULL) {
        *li = no;
    } else {
        Elemento *aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int busca_lista_pos(const Lista* li, const Rectangle pos) {
    if (li == NULL) {
        return 0;
    }
    const Elemento *no = *li;
    while (no != NULL && no->pos.x != pos.x && no->pos.y != pos.y) {
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    }
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) {
        return 0;
    }
    if (*li == NULL) {
        return 0;
    }
    Elemento *ant, *no = *li;
    while (no->prox != NULL) {
        ant = no;
        no = no->prox;
    }
    if (no == *li) {
        *li = no->prox;
    } else {
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}

int tamanho_lista(const Lista* li) {
    if (li == NULL) {
        return 0;
    }
    int tamanho = 0;
    const Elemento* no = *li;
    while (no != NULL) {
        tamanho++;
        no = no->prox;
    }
    return tamanho;
}

int lista_vazia(const Lista* li) {
    if (li == NULL) {
        return 1;
    }
    if (*li == NULL) {
        return 1;
    }
    return 0;
}

int lista_cheia(Lista* li) {
    return 0;
}