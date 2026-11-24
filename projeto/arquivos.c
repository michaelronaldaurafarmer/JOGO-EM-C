#include <stdio.h>

void mostrarHistoria() {
    FILE *arquivo;
    char texto[200];

    arquivo = fopen("historia.txt", "r");

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir a historia.\n");
        return;
    }

    printf("\n===== HISTORIA =====\n");

    while (fgets(texto, 200, arquivo) != NULL) {
        printf("%s", texto);
    }

    fclose(arquivo);
}
