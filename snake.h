#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include "ListaDinamicaEncadeada.h"

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define SNAKE_COLOR YELLOW
#define FOOD_COLOR BLUE

typedef struct Bordas {
    Rectangle pos;
} Bordas;

typedef struct Body {
    Lista* snake;
    Color color;
    int direcao;
} Body;

typedef struct Food {
    Rectangle pos;
    Color color;
} Food;

typedef struct Jogo {
    Body body;
    Food food;
    Bordas bordas[4];
    double tempo;
    double cooldown;
} Jogo;

void IniciaBody(Jogo *j);

void IniciaBordas(Jogo *j);

void IniciaFood(Jogo *j);

void IniciaJogo(Jogo *j);

void DesenhaBody(const Jogo *j);

void DesenhaFood(const Jogo *j);

void DesenhaBordas(const Jogo *j);

void DesenhaJogo(const Jogo *j);

void AtualizaDirecao(Jogo *j);

void AtualizaPosBody(const Jogo *j);

void AtualizaRodada(Jogo *j);

int ColisaoFood(const Jogo *j);

int ColisaoBorda(const Jogo *j);

int ColisaoSnake(const Jogo *j);

#endif
