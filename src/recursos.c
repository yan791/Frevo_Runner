#include "recursos.h"

static Texture2D carregarTexturaComChroma(const char *caminho) {
    Image img = LoadImage(caminho);
    if (!img.data) {
        Image fb = GenImageColor(64, 64, MAGENTA);
        Texture2D t = LoadTextureFromImage(fb);
        UnloadImage(fb);
        return t;
    }
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Color *px = (Color *)img.data;
    for (int i = 0, n = img.width * img.height; i < n; i++)
        if (px[i].g > 150 && px[i].r < 120 && px[i].b < 120) px[i] = BLANK;
    Texture2D t = LoadTextureFromImage(img);
    SetTextureFilter(t, TEXTURE_FILTER_POINT);
    UnloadImage(img);
    return t;
}

Recursos carregarRecursos(void) {
    Recursos r;
    r.fundo = LoadTexture("assets/sprites/background_olinda.png");
    SetTextureFilter(r.fundo, TEXTURE_FILTER_POINT);
    r.jogador = carregarTexturaComChroma("assets/sprites/player_foliao.png");
    r.logo    = carregarTexturaComChroma("assets/sprites/logo_frevo_runner.png");
    r.icone   = carregarTexturaComChroma("assets/sprites/icone_sombrinha.png");

    static const char *spritesObs[TIPOS_OBSTACULOS] = {
        "assets/sprites/obstaculo_boneco_gigante.png",
        "assets/sprites/obstaculo_trio_eletrico.png",
        "assets/sprites/obstaculo_bloco.png",
        "assets/sprites/obstaculo_caixa_som.png",
        "assets/sprites/obstaculo_ambulante.png",
        "assets/sprites/obstaculo_estandarte.png",
    };
    for (int i = 0; i < TIPOS_OBSTACULOS; i++)
        r.obstaculos.sprites[i] = carregarTexturaComChroma(spritesObs[i]);

    r.musica       = LoadMusicStream("assets/audio/frevo_chiptune.mp3");
    r.somMenu      = LoadSound("assets/audio/menu.wav");
    r.somColisao   = LoadSound("assets/audio/collision.wav");
    r.somPontuacao = LoadSound("assets/audio/score.wav");
    r.somPulo      = LoadSound("assets/audio/jump.wav");
    return r;
}

void descarregarRecursos(Recursos r) {
    UnloadTexture(r.fundo);
    UnloadTexture(r.jogador);
    UnloadTexture(r.logo);
    UnloadTexture(r.icone);
    for (int i = 0; i < TIPOS_OBSTACULOS; i++)
        UnloadTexture(r.obstaculos.sprites[i]);
    UnloadMusicStream(r.musica);
    UnloadSound(r.somMenu);
    UnloadSound(r.somColisao);
    UnloadSound(r.somPontuacao);
    UnloadSound(r.somPulo);
}
