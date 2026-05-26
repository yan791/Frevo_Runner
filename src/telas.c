#include "telas.h"
#include "ranking.h"
#include <math.h>
#include <string.h>

static void desenharBotao(Rectangle rect, const char *texto, bool selecionado) {
    Color corFundo;
    if (selecionado)
        corFundo = (Color){255, 198, 46, 255};
    else
        corFundo = (Color){ 28,  96, 169, 230};

    Color corBorda;
    if (selecionado)
        corBorda = ORANGE;
    else
        corBorda = (Color){255, 255, 255, 210};

    DrawRectangleRounded(rect, 0.22f, 12, corFundo);
    DrawRectangleRoundedLines(rect, 0.22f, 12, corBorda);

    int larguraTexto = MeasureText(texto, 30);
    int posX = (int)(rect.x + rect.width  / 2 - larguraTexto / 2);
    int posY = (int)(rect.y + 13);

    Color corTexto;
    if (selecionado)
        corTexto = MAROON;
    else
        corTexto = WHITE;
    DrawText(texto, posX, posY, 30, corTexto);
}

void desenharFundo(Texture2D fundo, float deslocamento, int pistaAtiva) {
    DrawTexturePro(
        fundo,
        (Rectangle){0, 0, (float)fundo.width, (float)fundo.height},
        (Rectangle){0, 0, (float)LARGURA_TELA, (float)ALTURA_TELA},
        (Vector2){0, 0}, 0.0f, WHITE
    );

    for (int i = 0; i < TOTAL_PISTAS; i++) {
        float y     = obterYDaPista(i);
        bool  ativa = (i == pistaAtiva);

        Color corPista;
        if (ativa)
            corPista = (Color){110, 78, 55, 215};
        else
            corPista = (Color){ 75, 54, 44, 190};
        DrawRectangle(0, (int)y - 8, LARGURA_TELA, 20, corPista);

        if (ativa)
            DrawRectangle(0, (int)y - 9, LARGURA_TELA, 2, (Color){255, 220, 80, 160});

        for (int x = -80; x < LARGURA_TELA + 80; x += 80) {
            int posTracado = (int)(x - fmodf(deslocamento, 80.0f));
            DrawRectangle(posTracado, (int)y - 2, 35, 4, (Color){255, 222, 120, 210});
        }
    }
}

void desenharMenu(Texture2D logo, Texture2D icone, int opcao) {
    ClearBackground((Color){29, 38, 125, 255});
    DrawRectangleGradientV(0, 0, LARGURA_TELA, ALTURA_TELA,
                           (Color){21, 33, 125, 255},
                           (Color){239, 76,  35, 255});

    DrawCircle( 80,  80, 120, (Color){255, 205, 49, 75});
    DrawCircle(820, 520,  90, (Color){239,  76, 35, 55});

    DrawTexturePro(logo,
        (Rectangle){0, 0, (float)logo.width,  (float)logo.height},
        (Rectangle){240, 35, 420, 210},
        (Vector2){0, 0}, 0, WHITE);

    DrawTexturePro(icone,
        (Rectangle){0, 0, (float)icone.width, (float)icone.height},
        (Rectangle){ 60, 455, 90, 90},
        (Vector2){0, 0}, -15, WHITE);

    DrawTexturePro(icone,
        (Rectangle){0, 0, (float)icone.width, (float)icone.height},
        (Rectangle){750, 455, 90, 90},
        (Vector2){0, 0},  15, WHITE);

    const char *nomeOpcoes[] = {"Jogar", "Ranking", "Creditos", "Sair"};
    for (int i = 0; i < 4; i++) {
        Rectangle posicaoBotao = {330, 245.0f + i * 72, 240, 55};
        desenharBotao(posicaoBotao, nomeOpcoes[i], opcao == i);
    }

    DrawText("Use as setas para navegar e ENTER para selecionar", 190, 555, 20, RAYWHITE);
}

void desenharRanking(void) {
    EntradaRanking ranking[MAX_RANKING];
    int quantidade = carregarRanking(ranking, MAX_RANKING);

    ClearBackground((Color){22, 44, 103, 255});
    DrawRectangleGradientV(0, 0, LARGURA_TELA, ALTURA_TELA,
                           (Color){22, 44, 103, 255},
                           (Color){10, 20,  60, 255});

    DrawText("TOP 5 - RANKING", 291, 56, 42, (Color){0, 0, 0, 150});
    DrawText("TOP 5 - RANKING", 290, 55, 42, GOLD);
    DrawText("Ordenado com Bubble Sort e salvo em data/ranking.txt",
             205, 105, 20, (Color){200, 200, 200, 200});

    static const Color medalhas[] = {
        {255, 215,   0, 255},
        {192, 192, 192, 255},
        {205, 127,  50, 255},
        {220, 220, 220, 200},
        {220, 220, 220, 200},
    };

    for (int i = 0; i < 5; i++) {
        Rectangle linha = {220, 160.0f + i * 62, 460, 46};

        Color corFundo;
        if (i == 0)
            corFundo = (Color){255, 215, 0, 45};
        else
            corFundo = (Color){255, 255, 255, 28};
        DrawRectangleRounded(linha, 0.18f, 10, corFundo);
        DrawRectangleRoundedLines(linha, 0.18f, 10, (Color){255, 255, 255, 40});

        if (i < quantidade) {
            DrawText(TextFormat("%d. %-20s", i + 1, ranking[i].nome),
                     245, (int)linha.y + 11, 24, medalhas[i]);
            DrawText(TextFormat("%06d", ranking[i].pontuacao),
                     555, (int)linha.y + 11, 24, medalhas[i]);
        } else {
            DrawText(TextFormat("%d. ---", i + 1),
                     245, (int)linha.y + 11, 24, (Color){120, 120, 120, 200});
        }
    }

    DrawText("Pressione ESC para voltar", 320, 525, 24, (Color){200, 200, 200, 200});
}

void desenharCreditos(void) {
    ClearBackground((Color){74, 22, 95, 255});
    DrawRectangleGradientV(0, 0, LARGURA_TELA, ALTURA_TELA,
                           (Color){74, 22, 95, 255},
                           (Color){30, 10, 50, 255});

    DrawText("CREDITOS", 336, 71, 46, (Color){0, 0, 0, 150});
    DrawText("CREDITOS", 335, 70, 46, GOLD);

    DrawRectangleRounded((Rectangle){180, 135, 540, 280}, 0.06f, 10, (Color){255, 255, 255, 18});

    DrawText("Frevo Runner", 336, 156, 32, (Color){0, 0, 0, 120});
    DrawText("Frevo Runner", 335, 155, 32, GOLD);
    DrawText("Jogo academico em C com Raylib",                     255, 205, 22, RAYWHITE);
    DrawText("Sprites pixel art e audio gerados automaticamente",   190, 242, 21, RAYWHITE);
    DrawText("Obstaculos controlados por lista encadeada simples",  165, 278, 21, RAYWHITE);
    DrawText("Ranking persistente ordenado por Bubble Sort",        210, 314, 21, RAYWHITE);
    DrawText("Tema visual inspirado no Carnaval de Olinda",         205, 350, 21, RAYWHITE);

    DrawText("Pressione ESC para voltar", 318, 525, 24, (Color){200, 200, 200, 200});
}

void desenharTelaJogo(Recursos res, Obstaculo *lista, Jogador jogador,
                      float pontuacao, float tempoJogo, float deslocamento) {
    desenharFundo(res.fundo, deslocamento, jogador.pista);
    desenharObstaculos(lista, res.obstaculos);

    DrawEllipse(
        (int)(jogador.x + jogador.largura * 0.5f),
        (int)(obterYDaPista(jogador.pista) + 5),
        (int)(jogador.largura * 0.33f), 5,
        (Color){0, 0, 0, 65}
    );

    desenharJogador(jogador, res.jogador);

    DrawRectangle(0,  0, LARGURA_TELA, 58, (Color){17, 28, 77, 215});
    DrawRectangle(0, 57, LARGURA_TELA,  2, (Color){255, 200, 40, 180});

    const char *txtPontos = TextFormat("Pontuacao: %06d", (int)pontuacao);
    DrawText(txtPontos, 25, 19, 26, (Color){0, 0, 0, 180});
    DrawText(txtPontos, 24, 18, 26, GOLD);

    const char *txtVelocidade = TextFormat("Velocidade: %.0f", 250.0f + tempoJogo * 12.5f);
    DrawText(txtVelocidade, 651, 21, 22, (Color){0, 0, 0, 160});
    DrawText(txtVelocidade, 650, 20, 22, RAYWHITE);

    for (int i = 0; i < TOTAL_PISTAS; i++) {
        bool  ativa = (i == jogador.pista);
        int raio;
        if (ativa)
            raio = 6;
        else
            raio = 4;
        Color cor;
        if (ativa)
            cor = GOLD;
        else
            cor = (Color){255, 255, 255, 80};
        DrawCircle(415 + i * 18, 31, raio, cor);
    }
}

void desenharTelaGameOver(Recursos res, Obstaculo *lista, Jogador jogador,
                          float pontuacao, float deslocamento,
                          const char *nomeJogador, bool pontuacaoSalva) {
    desenharFundo(res.fundo, deslocamento, jogador.pista);
    desenharObstaculos(lista, res.obstaculos);
    desenharJogador(jogador, res.jogador);

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, (Color){0, 0, 0, 185});

    DrawRectangleRounded(     (Rectangle){210, 65, 480, 440}, 0.07f, 12, (Color){20, 25, 70, 215});
    DrawRectangleRoundedLines((Rectangle){210, 65, 480, 440}, 0.07f, 12, (Color){255, 200, 40, 120});

    DrawText("GAME OVER", 286, 96, 58, (Color){120, 0, 0, 255});
    DrawText("GAME OVER", 284, 94, 58, RED);

    const char *txtFinal = TextFormat("Pontuacao: %d", (int)pontuacao);
    DrawText(txtFinal, (LARGURA_TELA - MeasureText(txtFinal, 28)) / 2, 172, 28, GOLD);

    DrawText("Digite seu nome:", 355, 235, 22, (Color){200, 200, 200, 220});
    DrawRectangleRounded((Rectangle){300, 268, 300, 46}, 0.22f, 10, (Color){255, 255, 255, 235});

    bool cursor      = !pontuacaoSalva && (int)(GetTime() * 2) % 2 == 0;
    int  tamanhoNome = (int)strlen(nomeJogador);

    const char *textoNome;
    if (tamanhoNome > 0)
        textoNome = nomeJogador;
    else
        textoNome = "";
    const char *textoCursor;
    if (cursor)
        textoCursor = "|";
    else
        textoCursor = " ";
    DrawText(TextFormat("%s%s", textoNome, textoCursor), 320, 280, 26, DARKBLUE);

    if (tamanhoNome == 0 && !cursor)
        DrawText("Jogador", 320, 280, 26, (Color){150, 150, 180, 160});

    Color corStatus;
    if (pontuacaoSalva)
        corStatus = GREEN;
    else
        corStatus = (Color){200, 200, 200, 200};
    const char *textoStatus;
    if (pontuacaoSalva)
        textoStatus = "Pontuacao salva!";
    else
        textoStatus = "ENTER para salvar";
    DrawText(textoStatus, 330, 330, 22, corStatus);

    DrawRectangle(212, 385, 476, 1, (Color){255, 255, 255, 40});
    DrawText("R   - Reiniciar",      350, 395, 22, RAYWHITE);
    DrawText("M   - Voltar ao menu", 340, 422, 22, RAYWHITE);
    DrawText("ESC - Sair do jogo",   345, 449, 22, (Color){255, 100, 100, 220});
}