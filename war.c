#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5

// Struct do Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[TOTAL_TERRITORIOS];

    printf("=== Cadastro de Territorios ===\n\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Nome do territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n
        
        printf("Cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa

        printf("\n");
    }

    // Exibição do cadastro
    printf("\n=== MAPA ===\n");
    for (int i = 0; i <TOTAL_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Numero de tropas: %d\n", mapa[i].tropas);
        printf("----------------------------\n");
    }

    return 0;
}