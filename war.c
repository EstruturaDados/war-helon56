#include <stdio.h>
#include <string.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5
#define MISSORANDOM 2

// Struct do Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções 
void inicializarTerritorios(Territorio *mapa, int total) {
    const char *nomes[TOTAL_TERRITORIOS] = {"Norte", "Sul", "Leste", "Oeste", "Central"};
    const char *cores[TOTAL_TERRITORIOS] = {"Vermelho", "Azul", "Verde", "Amarelo", "Roxo"};
    int tropasIni[TOTAL_TERRITORIOS] = {5, 5, 5, 5, 5};

    for(int i = 0; i < total; i++){
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropasIni[i];
    }
}

// Exibe o mapa atual
void exibirMapa(const Territorio *mapa, int total) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    for (int i = 0; i < total; i++) {
        printf("Territorio %d: %s | Exército: %s | Tropas: %d\n", 
            i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("---------------------------\n");
}

// Função de batalha
void batalha(Territorio *atacante, Territorio *defensor) {
    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("%s (%d tropas) -> Dado: %d\n", atacante->nome, atacante->tropas, dadoAtq);
    printf("%s (%d tropas) -> Dado: %d\n", defensor->nome, defensor->tropas, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas -= 1;
        printf("%s vence a rodada!\n", atacante->nome);
        if (defensor->tropas <= 0) {
            printf("%s foi conquistado por %s!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
    } else {
        printf("%s defende com sucesso!\n", defensor->nome);
    }
}

// Função para escolher territórios e atacar
void realizarAtaque(Territorio *mapa, int total) {
    int atq, def;
    printf("\nEscolha o territorio atacante (1-%d): ", total);
    while (scanf("%d", &atq) != 1 || atq < 1 || atq > total) {
        printf("Escolha invalida. Digite um numero entre 1 e %d: ", total);
        while(getchar() != '\n');
    }
    printf("Escolha o territorio defensor (1-%d): ", total);
    while (scanf("%d", &def) != 1 || def < 1 || def > total || def == atq) {
        printf("Escolha invalida. Digite um numero valido: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    batalha(&mapa[atq - 1], &mapa[def - 1]);
}

// Missão aleatória
void verificarMissao(const Territorio *mapa, int total, int missao) {
    switch(missao) {
        case 0:
            for(int i=0;i<total;i++){
                if(strcmp(mapa[i].cor,"Verde")==0 && mapa[i].tropas>0){
                    printf("\nMissão não concluída! Ainda há exército Verde.\n");
                    return;
                }
            }
            printf("\nParabéns! Missão concluída: Destruir exército Verde!\n");
            break;
        case 1:
            {
                int conquistados = 0;
                for(int i=0;i<total;i++){
                    if(strcmp(mapa[i].cor,"Vermelho")==0)
                        conquistados++;
                }
                if(conquistados >=3)
                    printf("\nParabéns! Missão concluída!\n");
                else
                    printf("\nMissão não concluída! Conquistados %d/3\n", conquistados);
            }
            break;
    }
}

// Função principal
void menu(Territorio *mapa, int total) {
    char opcao;
    int missao = rand() % MISSORANDOM;
    do {
        printf("\n=== MENU ===\n");
        printf("Atacar\nVerificar Missao\nSair\nEscolha: ");
        scanf(" %c", &opcao);
        while(getchar() != '\n');

        switch(opcao){
            case '1':
                realizarAtaque(mapa, total);
                exibirMapa(mapa, total);
                break;
            case '2':
                verificarMissao(mapa, total, missao);
                break;
            case '0':
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("A opção não é válida!\n");
        }
    } while(opcao != '0');
}

int main() {
    srand(time(NULL));

    Territorio *mapa = (Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if(!mapa){
        printf("Erro de alocação!\n");
        return 1;
    }

    printf("WAR MESTRE\n");
    inicializarTerritorios(mapa, TOTAL_TERRITORIOS);
    exibirMapa(mapa, TOTAL_TERRITORIOS);

    menu(mapa, TOTAL_TERRITORIOS);

    free(mapa);
    printf("Fim de jogo!\n");
    return 0;
}