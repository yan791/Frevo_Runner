#include "jogador.h"

static const float PISTAS_Y[TOTAL_PISTAS] = {330.0f, 410.0f, 490.0f};

float obterYDaPista(int pista) {
    if (pista < 0) pista = 0;
    if (pista >= TOTAL_PISTAS) pista = TOTAL_PISTAS - 1;
    return PISTAS_Y[pista];
}

void inicializarJogador(Jogador *jogador) {
    jogador->pista = 1;
    jogador->x = 120.0f;
    jogador->largura = 74.0f;
    jogador->altura = 86.0f;
    jogador->baseY = obterYDaPista(jogador->pista);
    jogador->y = jogador->baseY - jogador->altura;
    jogador->velocidadeY = 0.0f;
    jogador->pulando = false;
}

void atualizarJogador(Jogador *jogador, float delta) {
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && jogador->pista > 0) {
        jogador->pista--;
    }

    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && jogador->pista < TOTAL_PISTAS - 1) {
        jogador->pista++;
    }

    jogador->baseY = obterYDaPista(jogador->pista);

    if (IsKeyPressed(KEY_SPACE) && !jogador->pulando) {
        jogador->pulando = true;
        jogador->velocidadeY = -690.0f;
    }

    if (jogador->pulando) {
        jogador->velocidadeY += 1850.0f * delta;
        jogador->y += jogador->velocidadeY * delta;

        float chao = jogador->baseY - jogador->altura;
        if (jogador->y >= chao) {
            jogador->y = chao;
            jogador->velocidadeY = 0.0f;
            jogador->pulando = false;
        }
    } else {
        jogador->y = jogador->baseY - jogador->altura;
    }
}