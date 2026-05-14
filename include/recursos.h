#ifndef RECURSOS_H
#define RECURSOS_H

#include "raylib.h"
#include "obstaculos.h"

typedef struct Recursos {
    Texture2D fundo;
    Texture2D jogador;
    Texture2D logo;
    Texture2D icone;
    RecursosObstaculos obstaculos;
    Music musica;
    Sound somMenu;
    Sound somColisao;
    Sound somPontuacao;
    Sound somPulo;
} Recursos;

Recursos carregarRecursos(void);
void descarregarRecursos(Recursos r);

#endif