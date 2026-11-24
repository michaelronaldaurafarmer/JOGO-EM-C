#include <stdio.h>

void salvarRanking(char nome[], int tentativas) {
    FILE *arquivo;

    arquivo = fopen("ranking.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao salvar o ranking.\n");
        return;
    }

    fprintf(arquivo, "%s;%d\n", nome, tentativas);
    fclose(arquivo);

    printf("Seu resultado foi salvo!\n");
}

void mostrarRanking() {
    FILE *arquivo;
    char nome[50];
    int tentativas;
    int achou = 0;

    arquivo = fopen("ranking.txt", "r");

    if (arquivo == NULL) {
        printf("\nAinda nao tem resultados no ranking.\n");
        return;
    }

    printf("\n===== RANKING =====\n");

    while (fscanf(arquivo, "%49[^;];%d\n", nome, &tentativas) == 2) {
        printf("%s - %d tentativas\n", nome, tentativas);
        achou = 1;
    }

    if (achou == 0) {
        printf("Ranking vazio.\n");
    }

    fclose(arquivo);
}
