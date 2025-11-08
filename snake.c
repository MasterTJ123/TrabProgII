#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "raylib.h"
#include "snake.h"
#include "ListaDinamicaEncadeada.h"

int main() {
    Jogo jogo;
    int gameOver = 1;

    InitWindow(LARGURA, ALTURA, "Snake Game");
    SetTargetFPS(60);
    srand(time(NULL));

    IniciaJogo(&jogo);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (gameOver) {
            DesenhaJogo(&jogo);
            AtualizaRodada(&jogo);
            if (ColisaoFood(&jogo)) {
                const Elemento *cauda = *jogo.body.snake;
                while (cauda->prox != NULL) {
                    cauda = cauda->prox;
                }
                insere_lista_final(jogo.body.snake, cauda->pos);
                IniciaFood(&jogo);
            }
            if (ColisaoSnake(&jogo) || ColisaoBorda(&jogo)) {
                gameOver = 0;
            }
        } else {
            DrawText("GAME OVER!", 200, 200, 40, RED);
            DrawText("Continue", 265, 400, 30, WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                IniciaJogo(&jogo);
                gameOver = 1;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    libera_lista(jogo.body.snake);
    return 0;
}

void IniciaBody(Jogo *j) {
    j->body.snake = cria_lista();
    const Rectangle pos = {LARGURA / 2.0f - STD_SIZE_X, ALTURA - STD_SIZE_Y - 10, STD_SIZE_X, STD_SIZE_Y};
    insere_lista_final(j->body.snake, pos);
    j->body.direcao = 0;
    j->body.color = SNAKE_COLOR;
}

void IniciaBordas(Jogo *j) {
    j->bordas[0].pos = (Rectangle){0, 0, LARGURA, 10};
    j->bordas[1].pos = (Rectangle){LARGURA - 10, 0, 10, ALTURA};
    j->bordas[2].pos = (Rectangle){0, ALTURA - 10, LARGURA, 10};
    j->bordas[3].pos = (Rectangle){0, 0, 10, ALTURA};
}

void IniciaFood(Jogo *j) {
    Rectangle pos;
    int colisao = 0;
    do {
        colisao = 0;
        const float x_temp = rand() % ((ALTURA - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10;
        const float y_temp = rand() % ((ALTURA - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10;
        pos = (Rectangle){x_temp, y_temp, STD_SIZE_X, STD_SIZE_Y};
        if (busca_lista_pos(j->body.snake, pos)) {
            colisao = 1;
        }
    } while (colisao);
    j->food.pos = pos;
    j->food.color = FOOD_COLOR;
}

void IniciaJogo(Jogo *j) {
    IniciaBordas(j);
    IniciaBody(j);
    IniciaFood(j);
    j->tempo = GetTime();
}

void DesenhaBody(const Jogo *j) {
    const Elemento *no = *j->body.snake;
    while (no != NULL) {
        DrawRectangleRec(no->pos, j->body.color);
        no = no->prox;
    }
}

void DesenhaFood(const Jogo *j) {
    DrawRectangleRec(j->food.pos, j->food.color);
}

void DesenhaBordas(const Jogo *j) {
    for (int i = 0; i < 4; i++) {
        DrawRectangleRec(j->bordas[i].pos, LIGHTGRAY);
    }
}

void DesenhaJogo(const Jogo *j) {
    DesenhaBordas(j);
    DesenhaBody(j);
    DesenhaFood(j);
}

void AtualizaDirecao(Jogo *j) {
    if (IsKeyDown(KEY_UP) && j->body.direcao != 2 && GetTime() - j->cooldown > COOLDOWN) {
        j->body.direcao = 0;
        j->cooldown = GetTime();
    }
    if (IsKeyDown(KEY_RIGHT) && j->body.direcao != 3 && GetTime() - j->cooldown > COOLDOWN) {
        j->body.direcao = 1;
        j->cooldown = GetTime();
    }
    if (IsKeyDown(KEY_DOWN) && j->body.direcao != 0 && GetTime() - j->cooldown > COOLDOWN) {
        j->body.direcao = 2;
        j->cooldown = GetTime();
    }
    if (IsKeyDown(KEY_LEFT) && j->body.direcao != 1 && GetTime() - j->cooldown > COOLDOWN) {
        j->body.direcao = 3;
        j->cooldown = GetTime();
    }
}

void AtualizaPosBody(const Jogo *j) {
    if (j == NULL || j->body.snake == NULL) return;

    Elemento *atual = *j->body.snake;
    Rectangle posAnterior = atual->pos;

    if (j->body.direcao == 0) {
        atual->pos.y -= STD_SIZE_Y;
    }
    if (j->body.direcao == 1) {
        atual->pos.x += STD_SIZE_X;
    }
    if (j->body.direcao == 2) {
        atual->pos.y += STD_SIZE_Y;
    }
    if (j->body.direcao == 3) {
        atual->pos.x -= STD_SIZE_X;
    }

    atual = atual->prox;
    while (atual != NULL) {
        const Rectangle pos = atual->pos;
        atual->pos = posAnterior;
        posAnterior = pos;
        atual = atual->prox;
    }
}

void AtualizaRodada(Jogo *j) {
    AtualizaDirecao(j);
    if (GetTime() - j->tempo > TEMPO) {
        AtualizaPosBody(j);
        j->tempo = GetTime();
        j->cooldown = COOLDOWN;
    }
}

int ColisaoFood(const Jogo *j) {
    if (CheckCollisionRecs((*(j->body.snake))->pos, j->food.pos)) {
        return 1;
    }
    return 0;
}

int ColisaoBorda(const Jogo *j) {
    const int bordaCima = (*j->body.snake)->pos.y < 10;
    const int bordaDireita = (*j->body.snake)->pos.x > 610;
    const int bordaBaixo = (*j->body.snake)->pos.y > 610;
    const int bordaEsquerda = (*j->body.snake)->pos.x < 10;
    if (bordaCima || bordaDireita || bordaBaixo || bordaEsquerda) {
        return 1;
    }
    return 0;
}

int ColisaoSnake(const Jogo *j) {
    Lista li = *j->body.snake;
    const Rectangle cabeca = li->pos;

    if (li->prox != NULL) {
        li = li->prox;
    }
    while (li->prox != NULL) {
        li = li->prox;
        if (li->pos.x == cabeca.x && li->pos.y == cabeca.y) {
            return 1;
        }
    }

    return 0;
}
