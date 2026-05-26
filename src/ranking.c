#include "ranking.h"
#include <stdio.h>
#include <string.h>

static const char *ARQUIVO_RANKING = "data/ranking.txt";

int carregarRanking(EntradaRanking ranking[], int maximo) {
    FILE *f = fopen(ARQUIVO_RANKING, "r");
    if (!f) return 0;
    int n = 0;
    while (n < maximo && fscanf(f, "%23s %d", ranking[n].nome, &ranking[n].pontuacao) == 2) n++;
    fclose(f);
    ordenarRankingBubbleSort(ranking, n);
    return n;
}

void salvarRanking(EntradaRanking ranking[], int quantidade) {
    FILE *f = fopen(ARQUIVO_RANKING, "w");
    if (!f) return;
    for (int i = 0; i < quantidade; i++)
        fprintf(f, "%s %d\n", ranking[i].nome, ranking[i].pontuacao);
    fclose(f);
}

void ordenarRankingBubbleSort(EntradaRanking ranking[], int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (ranking[j].pontuacao < ranking[j + 1].pontuacao) {
                EntradaRanking temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

void adicionarPontuacao(const char *nome, int pontuacao) {
    EntradaRanking ranking[MAX_RANKING + 1];
    int n = carregarRanking(ranking, MAX_RANKING);
    const char *nomeFinal;
    if (strlen(nome) > 0)
        nomeFinal = nome;
    else
        nomeFinal = "Jogador";
    strncpy(ranking[n].nome, nomeFinal, TAM_NOME - 1);
    ranking[n].nome[TAM_NOME - 1] = '\0';
    ranking[n].pontuacao = pontuacao;
    ordenarRankingBubbleSort(ranking, ++n);
    if (n > MAX_RANKING) n = MAX_RANKING;
    salvarRanking(ranking, n);
}