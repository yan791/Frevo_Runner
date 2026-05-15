#ifndef TELAS_H
#define TELAS_H

#include "raylib.h"
#include "recursos.h"

#define LARGURA_TELA 900
#define ALTURA_TELA  600

typedef enum Tela {
    TELA_MENU,
    TELA_JOGO,
    TELA_RANKING,
    TELA_CREDITOS,
    TELA_GAME_OVER
} Tela;

void desenharFundo(Texture2D fundo, float deslocamento, int pistaAtiva);
void desenharMenu(Texture2D logo, Texture2D icone, int opcao);
void desenharRanking(void);
void desenharCreditos(void);
void desenharTelaJogo(Recursos res, Obstaculo *lista, Jogador jogador, float pontuacao, float tempoJogo, float deslocamento);
void desenharTelaGameOver(Recursos res, Obstaculo *lista, Jogador jogador, float pontuacao, float deslocamento, const char *nomeJogador, bool pontuacaoSalva);

#endif
