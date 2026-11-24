#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10

struct Coordenada {
    int linha;
    int coluna;
};

struct Lider {
    char nome[30];
    char letra;
    int tamanho;
    int capturado;
    int vertical;
    struct Coordenada posicao;
};

void montarMapa(char mapa[TAM][TAM]) {
    int i, j;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            mapa[i][j] = '~';
        }
    }
}

void montarVisao(char mapa[TAM][TAM]) {
    int i, j;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            mapa[i][j] = '?';
        }
    }
}

void mostrarMapa(char mapa[TAM][TAM]) {
    int i, j;

    printf("\n   ");
    for (j = 0; j < TAM; j++) {
        printf("%2d ", j + 1);
    }
    printf("\n");

    for (i = 0; i < TAM; i++) {
        printf("%2d ", i + 1);

        for (j = 0; j < TAM; j++) {
            printf(" %c ", mapa[i][j]);
        }

        printf("\n");
    }

    printf("\n? = lugar nao tentado | X = acerto | O = nada\n");
}

int podeColocar(char mapa[TAM][TAM], int linha, int coluna,
                int tamanho, int vertical) {
    int i;

    for (i = 0; i < tamanho; i++) {
        int l = linha;
        int c = coluna;

        if (vertical == 1) {
            l = linha + i;
        }
        else {
            c = coluna + i;
        }

        if (l >= TAM || c >= TAM || mapa[l][c] != '~') {
            return 0;
        }
    }

    return 1;
}

void colocarLideres(char mapa[TAM][TAM], struct Lider lideres[]) {
    int i, j;

    for (i = 0; i < 3; i++) {
        int linha, coluna, vertical;

        do {
            linha = rand() % TAM;
            coluna = rand() % TAM;
            vertical = rand() % 2;
        } while (podeColocar(mapa, linha, coluna,
                             lideres[i].tamanho, vertical) == 0);

        lideres[i].posicao.linha = linha;
        lideres[i].posicao.coluna = coluna;
        lideres[i].vertical = vertical;
        lideres[i].capturado = 0;

        for (j = 0; j < lideres[i].tamanho; j++) {
            int l = linha;
            int c = coluna;

            if (vertical == 1) {
                l = linha + j;
            }
            else {
                c = coluna + j;
            }

            mapa[l][c] = lideres[i].letra;
        }
    }
}

int liderFoiCapturado(char visao[TAM][TAM], struct Lider lider) {
    int i;

    for (i = 0; i < lider.tamanho; i++) {
        int l = lider.posicao.linha;
        int c = lider.posicao.coluna;

        if (lider.vertical == 1) {
            l = l + i;
        }
        else {
            c = c + i;
        }

        if (visao[l][c] != 'X') {
            return 0;
        }
    }

    return 1;
}

int jogar(char nome[], int *tentativas) {
    char mapa[TAM][TAM];
    char visao[TAM][TAM];

    struct Lider lideres[3] = {
        {"Lampiao", 'L', 4, 0, 0, {0, 0}},
        {"Corisco", 'C', 3, 0, 0, {0, 0}},
        {"Dada", 'D', 2, 0, 0, {0, 0}}
    };

    int capturados = 0;
    int linha, coluna;
    int i;

    srand(time(NULL));

    montarMapa(mapa);
    montarVisao(visao);
    colocarLideres(mapa, lideres);

    *tentativas = 0;

    printf("\nBoa sorte, %s\n", nome);
    printf("Encontre os tres acampamentos escondidos.\n");

    while (capturados < 3) {
        mostrarMapa(visao);

        printf("Digite a linha (1 a 10): ");
        if (scanf("%d", &linha) != 1) {
            printf("Digite apenas numeros.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Digite a coluna (1 a 10): ");
        if (scanf("%d", &coluna) != 1) {
            printf("Digite apenas numeros.\n");
            while (getchar() != '\n');
            continue;
        }

        linha--;
        coluna--;

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Essa posicao nao existe no mapa.\n");
            continue;
        }

        if (visao[linha][coluna] != '?') {
            printf("Voce ja tentou esse lugar!\n");
            continue;
        }

        *tentativas = *tentativas + 1;

        if (mapa[linha][coluna] == '~') {
            visao[linha][coluna] = 'O';
            printf("Errou.\n");
        }
        else {
            visao[linha][coluna] = 'X';
            printf("Acertou uma parte de um acampamento.\n");

            for (i = 0; i < 3; i++) {
                if (lideres[i].capturado == 0 &&
                    liderFoiCapturado(visao, lideres[i]) == 1) {
                    lideres[i].capturado = 1;
                    capturados++;
                    printf("Voce capturou o acampamento de %s.\n",
                           lideres[i].nome);
                }
            }
        }

        printf("Acampamentos encontrados: %d de 3\n", capturados);
    }

    mostrarMapa(visao);
    return 1;
}
