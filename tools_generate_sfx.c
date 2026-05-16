#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#define SAMPLE_RATE 44100
#define AUDIO_DIR   "assets/audio"

static void escrever_wav(const char *caminho, const float *amostras, int n_amostras) {
    FILE *f = fopen(caminho, "wb");
    if (!f) { fprintf(stderr, "Erro ao criar: %s\n", caminho); return; }

    int32_t tamanho_dados = n_amostras * 2;       
    int32_t tamanho_riff  = 36 + tamanho_dados;

    fwrite("RIFF",           1, 4, f);
    fwrite(&tamanho_riff,    4, 1, f);
    fwrite("WAVE",           1, 4, f);

    int32_t tamanho_fmt    = 16;
    int16_t formato_audio  = 1;         
    int16_t n_canais       = 1;          
    int32_t taxa_amostra   = SAMPLE_RATE;
    int32_t taxa_bytes     = SAMPLE_RATE * 2;
    int16_t alinhamento    = 2;
    int16_t bits_amostra   = 16;

    fwrite("fmt ",          1, 4, f);
    fwrite(&tamanho_fmt,    4, 1, f);
    fwrite(&formato_audio,  2, 1, f);
    fwrite(&n_canais,       2, 1, f);
    fwrite(&taxa_amostra,   4, 1, f);
    fwrite(&taxa_bytes,     4, 1, f);
    fwrite(&alinhamento,    2, 1, f);
    fwrite(&bits_amostra,   2, 1, f);
    fwrite("data",          1, 4, f);
    fwrite(&tamanho_dados,  4, 1, f);

    for (int i = 0; i < n_amostras; i++) {
        float s = amostras[i];
        if (s >  1.0f) s =  1.0f;
        if (s < -1.0f) s = -1.0f;
        int16_t amostra_int = (int16_t)(s * 32767.0f);
        fwrite(&amostra_int, 2, 1, f);
    }

    fclose(f);
}
static float envelope(float t, float dur, float ataque, float decaimento) {
    if (t < ataque)           return t / ataque;
    if (t > dur - decaimento) { float v = (dur - t) / decaimento; return v < 0.0f ? 0.0f : v; }
    return 1.0f;
}
static float onda_quadrada(float freq, float t) {
    return sinf(2.0f * (float)M_PI * freq * t) >= 0.0f ? 1.0f : -1.0f;
}
static float onda_seno(float freq, float t) {
    return sinf(2.0f * (float)M_PI * freq * t);
}
static int ruido(int semente, float *valor_out) {
    semente = (1103515245 * semente + 12345) & 0x7fffffff;
    *valor_out = (semente / (float)0x7fffffff) * 2.0f - 1.0f;
    return semente;
}
static void gerar_menu(void) {
    float dur = 0.32f;
    float notas[] = {880.0f, 1174.66f, 1318.51f};
    int   n_notas = 3;
    int   n_amostras = (int)(SAMPLE_RATE * dur);
    float *buf = malloc(n_amostras * sizeof(float));

    for (int i = 0; i < n_amostras; i++) {
        float t     = (float)i / SAMPLE_RATE;
        int   idx   = (int)(t / (dur / n_notas));
        if (idx >= n_notas) idx = n_notas - 1;
        float local = t - idx * (dur / n_notas);
        float amp   = envelope(local, dur / n_notas, 0.005f, 0.04f);
        float freq  = notas[idx];
        buf[i] = 0.26f * amp * (0.65f * onda_quadrada(freq, t) + 0.35f * onda_seno(freq * 2.0f, t));
    }

    escrever_wav(AUDIO_DIR "/menu.wav", buf, n_amostras);
    free(buf);
    printf("Gerado: menu.wav\n");
}

static void gerar_score(void) {
    float dur = 0.22f;
    int   n_amostras = (int)(SAMPLE_RATE * dur);
    float *buf = malloc(n_amostras * sizeof(float));

    for (int i = 0; i < n_amostras; i++) {
        float t    = (float)i / SAMPLE_RATE;
        float freq = 900.0f + 900.0f * (t / dur);
        float amp  = envelope(t, dur, 0.005f, 0.05f);
        buf[i] = 0.28f * amp * (0.55f * onda_quadrada(freq, t) + 0.45f * onda_seno(freq * 1.5f, t));
    }

    escrever_wav(AUDIO_DIR "/score.wav", buf, n_amostras);
    free(buf);
    printf("Gerado: score.wav\n");
}

static void gerar_collision(void) {
    float dur = 0.45f;
    int   n_amostras = (int)(SAMPLE_RATE * dur);
    float *buf = malloc(n_amostras * sizeof(float));
    int   semente = 1234;

    for (int i = 0; i < n_amostras; i++) {
        float t    = (float)i / SAMPLE_RATE;
        float n_val;
        semente    = ruido(semente, &n_val);
        float freq = 180.0f - 90.0f * (t / dur);
        float amp  = envelope(t, dur, 0.002f, 0.25f);
        float tom  = 0.45f * onda_quadrada(freq, t) + 0.55f * n_val;
        buf[i] = 0.35f * amp * tom;
    }

    escrever_wav(AUDIO_DIR "/collision.wav", buf, n_amostras);
    free(buf);
    printf("Gerado: collision.wav\n");
}

static void gerar_jump(void) {
    float dur = 0.25f;
    int   n_amostras = (int)(SAMPLE_RATE * dur);
    float *buf = malloc(n_amostras * sizeof(float));

    for (int i = 0; i < n_amostras; i++) {
        float t    = (float)i / SAMPLE_RATE;
        float freq = 360.0f + 620.0f * (t / dur);
        float amp  = envelope(t, dur, 0.005f, 0.07f);
        buf[i] = 0.22f * amp * onda_seno(freq, t);
    }

    escrever_wav(AUDIO_DIR "/jump.wav", buf, n_amostras);
    free(buf);
    printf("Gerado: jump.wav\n");
}
int main(void) {
    gerar_menu();
    gerar_score();
    gerar_collision();
    gerar_jump();
    printf("Efeitos sonoros gerados em %s\n", AUDIO_DIR);
    return 0;
}