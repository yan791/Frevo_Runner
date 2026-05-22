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
                }else if (opcaoMenu == 1) telaAtual = TELA_RANKING;
                else if (opcaoMenu == 2) telaAtual = TELA_CREDITOS;
                else                     rodando   = false;
            }
            break;

        case TELA_JOGO: {
            bool estavaNoChao = !jogador.pulando;
            atualizarJogador(&jogador, delta);
            if (estavaNoChao && jogador.pulando) PlaySound(res.somPulo);

            tempoJogo += delta;
            pontuacao += delta * 18.0f;
            int marcoAtual = (int)pontuacao / 100;
            if (marcoAtual > ultimoMarcoPontuacao) {
                ultimoMarcoPontuacao = marcoAtual;
                PlaySound(res.somPontuacao);
            }

            float aceleracao       = tempoJogo * 7.5f;
            float intervaloGeracao = 1.25f - tempoJogo * 0.018f;
            if (intervaloGeracao < 0.47f) intervaloGeracao = 0.47f;

            tempoGeracao += delta;
            if (tempoGeracao >= intervaloGeracao) {
                inserirObstaculo(&listaObstaculos, criarObstaculo(
                    GetRandomValue(0, TIPOS_OBSTACULOS - 1),
                    GetRandomValue(0, TOTAL_PISTAS - 1),
                    LARGURA_TELA + 70.0f, 250.0f + tempoJogo * 5.0f));
                tempoGeracao = 0.0f;
            }

            atualizarObstaculos(&listaObstaculos, delta, aceleracao);
            deslocamentoFundo += (260.0f + aceleracao) * delta;

            if (verificarColisao(listaObstaculos, jogador)) {
                PlaySound(res.somColisao);
                telaAtual = TELA_GAME_OVER;
            }
            break;
        }

        case TELA_RANKING:
        case TELA_CREDITOS:
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE))
                telaAtual = TELA_MENU;
            break;

        case TELA_GAME_OVER:
            for (int tecla; (tecla = GetCharPressed()) > 0;) {
                int n = (int)strlen(nomeJogador);
                if (n < TAM_NOME_INPUT - 1 &&
                    ((tecla >= 'A' && tecla <= 'Z') ||
                     (tecla >= 'a' && tecla <= 'z') ||
                     (tecla >= '0' && tecla <= '9'))) {
                    nomeJogador[n]     = (char)tecla;
                    nomeJogador[n + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int n = (int)strlen(nomeJogador);
                if (n > 0) nomeJogador[n - 1] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && !pontuacaoSalva) {
                adicionarPontuacao(strlen(nomeJogador) > 0 ? nomeJogador : "Jogador", (int)pontuacao);
                pontuacaoSalva = true;
                PlaySound(res.somPontuacao);
            }
            if (IsKeyPressed(KEY_R)) {
                reiniciarJogo(&jogador, &listaObstaculos, &pontuacao, &tempoGeracao,
                              &tempoJogo, &deslocamentoFundo, &ultimoMarcoPontuacao, nomeJogador);
                pontuacaoSalva = false;
                telaAtual = TELA_JOGO;
            }
            if (IsKeyPressed(KEY_M)) { telaAtual = TELA_MENU; liberarObstaculos(&listaObstaculos); }
            if (IsKeyPressed(KEY_ESCAPE)) rodando = false;
            break;
        }
    }
}