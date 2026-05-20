#include "telas.h"
#include "ranking.h"

#include <string.h>

#define FPS            60
#define TAM_NOME_INPUT 24

static void reiniciarJogo(Jogador *jogador, Obstaculo **lista, float *pontuacao,
                           float *tempoGeracao, float *tempoJogo, float *deslocamentoFundo,
                           int *ultimoMarco, char nome[]) {
    inicializarJogador(jogador);
    liberarObstaculos(lista);
    *pontuacao = *tempoGeracao = *tempoJogo = *deslocamentoFundo = 0.0f;
    *ultimoMarco = 0;
    nome[0] = '\0';
}

int main(void) {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Frevo Runner");
    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(FPS);

    Recursos res = carregarRecursos();
    PlayMusicStream(res.musica);
    SetMusicVolume(res.musica,       0.45f);
    SetSoundVolume(res.somMenu,      0.35f);
    SetSoundVolume(res.somPulo,      0.40f);
    SetSoundVolume(res.somColisao,   0.30f);
    SetSoundVolume(res.somPontuacao, 0.25f);

    Tela     telaAtual          = TELA_MENU;
    int      opcaoMenu          = 0;
    Jogador  jogador;
    Obstaculo *listaObstaculos  = NULL;
    float    pontuacao          = 0.0f;
    float    tempoGeracao       = 0.0f;
    float    tempoJogo          = 0.0f;
    float    deslocamentoFundo  = 0.0f;
    int      ultimoMarcoPontuacao = 0;
    bool     pontuacaoSalva     = false;
    char     nomeJogador[TAM_NOME_INPUT] = "";

    inicializarJogador(&jogador);

    bool rodando = true;
    while (!WindowShouldClose() && rodando) {
        float delta = GetFrameTime();
        UpdateMusicStream(res.musica);

        switch (telaAtual) {
        case TELA_MENU:
            if (IsKeyPressed(KEY_DOWN))  { opcaoMenu = (opcaoMenu + 1) % 4; PlaySound(res.somMenu); }
            if (IsKeyPressed(KEY_UP))    { opcaoMenu = (opcaoMenu + 3) % 4; PlaySound(res.somMenu); }
            if (IsKeyPressed(KEY_ENTER)) {
                PlaySound(res.somMenu);
                if      (opcaoMenu == 0) {
                    reiniciarJogo(&jogador, &listaObstaculos, &pontuacao, &tempoGeracao,
                                  &tempoJogo, &deslocamentoFundo, &ultimoMarcoPontuacao, nomeJogador);
                    pontuacaoSalva = false;
                    telaAtual = TELA_JOGO;
                }
            
            }
        }
    }
}