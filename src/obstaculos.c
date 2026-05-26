#include "obstaculos.h"
#include <stdlib.h>

/* Dimensões de cada tipo de obstáculo (índice = tipo) */
static const float LARGURAS[TIPOS_OBSTACULOS] = {72.0f, 118.0f, 98.0f, 70.0f, 82.0f, 58.0f};
static const float ALTURAS[TIPOS_OBSTACULOS] = {96.0f, 72.0f, 72.0f, 78.0f, 72.0f, 94.0f};


Obstaculo *criarObstaculo(int tipo, int pista, float posX, float velocidade) {
    Obstaculo *novo = (Obstaculo *)malloc(sizeof(Obstaculo));
    if (novo == NULL) return NULL;

    novo->tipo = tipo;
    novo->pista = pista;
    novo->posX = posX;
    novo->velocidade = velocidade;
    novo->prox = NULL;
    return novo;
}

/* Percorre a lista encadeada até o fim e insere o novo nó */
void inserirObstaculo(Obstaculo **lista, Obstaculo *novo) {
    if (!novo) return;
    while (*lista) lista = &(*lista)->prox;
    *lista = novo;
}

/* Remove o primeiro nó da lista e libera sua memória */
void removerObstaculo(Obstaculo **lista) {
    if (*lista == NULL) return;

    Obstaculo *removido = *lista;
    *lista = (*lista)->prox;
    free(removido);
}

Rectangle obterRetanguloObstaculo(Obstaculo *obs) {
    float y = obterYDaPista(obs->pista) - ALTURAS[obs->tipo];
    return (Rectangle){obs->posX + 8.0f, y + 8.0f, LARGURAS[obs->tipo] - 16.0f, ALTURAS[obs->tipo] - 12.0f};
}

void atualizarObstaculos(Obstaculo **lista, float delta, float aceleracao) {
    /* Move todos os obstáculos para a esquerda conforme a velocidade e a aceleração do jogo */
    for (Obstaculo *a = *lista; a; a = a->prox)
        a->posX -= (a->velocidade + aceleracao) * delta;
    /* Remove do início da lista os obstáculos que saíram da tela */
    while (*lista && (*lista)->posX + LARGURAS[(*lista)->tipo] < -40.0f)
        removerObstaculo(lista);
}

void desenharObstaculos(Obstaculo *lista, RecursosObstaculos recursos) {
    for (Obstaculo *a = lista; a; a = a->prox) {
        Texture2D spr = recursos.sprites[a->tipo];
        float y = obterYDaPista(a->pista) - ALTURAS[a->tipo];
        DrawTexturePro(spr,
            (Rectangle){0, 0, (float)spr.width, (float)spr.height},
            (Rectangle){a->posX, y, LARGURAS[a->tipo], ALTURAS[a->tipo]},
            (Vector2){0, 0}, 0.0f, WHITE);
    }
}


bool verificarColisao(Obstaculo *lista, Jogador jogador) {
    Rectangle jr = obterRetanguloJogador(jogador);
    for (Obstaculo *a = lista; a; a = a->prox) {
        if (a->pista != jogador.pista) continue;
        Rectangle obr = obterRetanguloObstaculo(a);
        if (CheckCollisionRecs(jr, obr) && !(jogador.pulando && jogador.y + jogador.altura < obr.y + 22.0f))
            return true;
    }
    return false;
}

void liberarObstaculos(Obstaculo **lista) {
    while (*lista) removerObstaculo(lista);
}