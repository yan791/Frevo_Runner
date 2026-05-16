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