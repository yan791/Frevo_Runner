#ifndef RANKING_H
#define RANKING_H

#define MAX_RANKING 50
#define TAM_NOME    24

typedef struct EntradaRanking {
    char nome[TAM_NOME];
    int pontuacao;
} EntradaRanking;

int carregarRanking(EntradaRanking ranking[], int maximo);
void salvarRanking(EntradaRanking ranking[], int quantidade);
void ordenarRankingBubbleSort(EntradaRanking ranking[], int quantidade);
void adicionarPontuacao(const char *nome, int pontuacao);

#endif