#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

#define TOTAL_PISTAS 3

typedef struct Jogador {
    int pista;
    float x;
    float baseY;
    float y;
    float largura;
    float altura;
    float velocidadeY;
    bool pulando;
} Jogador;

void inicializarJogador(Jogador *jogador);
void atualizarJogador(Jogador *jogador, float delta);
void desenharJogador(Jogador jogador, Texture2D sprite);
Rectangle obterRetanguloJogador(Jogador jogador);
float obterYDaPista(int pista);

#endif