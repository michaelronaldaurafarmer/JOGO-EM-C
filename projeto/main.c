#include <stdio.h>
#include <string.h>

/* Funcoes que estao nos outros arquivos */
int jogar(char nome[], int *tentativas);
void salvarRanking(char nome[], int tentativas);
void mostrarRanking();
void mostrarHistoria();

int main() {
    int opcao;
    char nome[50];
    int tentativas;
    int ganhou;

    do {
        printf("\n===== BATALHA NAVAL DO CANGACO =====\n");
        printf("1 - Jogar\n");
        printf("2 - Ver historia\n");
        printf("3 - Ver ranking\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Digite seu nome: ");
            scanf(" %49[^\n]", nome);

            ganhou = jogar(nome, &tentativas);

            if (ganhou == 1) {
                printf("\nVoce venceu em %d tentativas\n", tentativas);
                salvarRanking(nome, tentativas);
            }
        }
        else if (opcao == 2) {
            mostrarHistoria();
        }
        else if (opcao == 3) {
            mostrarRanking();
        }
        else if (opcao == 0) {
            printf("Saindo do jogo...\n");
        }
        else {
            printf("Opcao invalida\n");
        }

    } while (opcao != 0);

    return 0;
}
