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