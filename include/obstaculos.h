#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include "raylib.h"
#include "jogador.h"

#define TIPOS_OBSTACULOS 6

typedef struct Obstaculo {
    int tipo;
    int pista;
    float posX;
    float velocidade;
    struct Obstaculo *prox;
} Obstaculo;

typedef struct RecursosObstaculos {
    Texture2D sprites[TIPOS_OBSTACULOS];
} RecursosObstaculos;

Obstaculo *criarObstaculo(int tipo, int pista, float posX, float velocidade);
void inserirObstaculo(Obstaculo **lista, Obstaculo *novo);
void removerObstaculo(Obstaculo **lista);
void atualizarObstaculos(Obstaculo **lista, float delta, float aceleracao);
void desenharObstaculos(Obstaculo *lista, RecursosObstaculos recursos);
bool verificarColisao(Obstaculo *lista, Jogador jogador);
void liberarObstaculos(Obstaculo **lista);
Rectangle obterRetanguloObstaculo(Obstaculo *obstaculo);

#endif