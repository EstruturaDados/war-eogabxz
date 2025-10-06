#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para exibir o mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("============\n");
}

// Função para cadastrar territórios pelo usuário
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função de ataque simulando rolagem de dados
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Não é possível atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Ataque bem-sucedido! %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
        if (atacante->tropas < 0) atacante->tropas = 0;
    } else {
        printf("Ataque fracassado! %s perdeu uma tropa.\n", atacante->nome);
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }
}

// Sorteio e atribuição de missão ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão do jogador
void exibirMissao(const char* missao) {
    printf("Sua missão: %s\n", missao);
}

// Verifica se a missão foi cumprida (lógica simples inicial)
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    if (strcmp(missao, "Conquistar 2 territorios") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) count++;
        }
        return count >= 2;
    }
    if (strcmp(missao, "Conquistar todos os territorios") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Eliminar cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) return 0;
        }
        return 1;
    }
    return 0;
}

// Libera a memória alocada
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int totalJogadores) {
    free(mapa);
    for (int i = 0; i < totalJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

int main() {
    srand(time(NULL));

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    // Cadastro pelo usuário
    cadastrarTerritorios(mapa, n);

    // Missões predefinidas
    char* missoes[] = {
        "Conquistar 2 territorios",
        "Conquistar todos os territorios",
        "Eliminar cor vermelha",
        "Sobreviver com pelo menos 1 territorio",
        "Manter pelo menos 5 tropas em um territorio"
    };
    int totalMissoes = 5;

    int totalJogadores = 2;
    char** missoesJogadores = (char**) malloc(totalJogadores * sizeof(char*));
    char* coresJogadores[2];

    // Definindo cores dos jogadores (primeiros dois territórios cadastrados)
    for (int i = 0; i < totalJogadores; i++) {
        coresJogadores[i] = mapa[i].cor;
    }

    // Atribuindo missões dinamicamente
    for (int i = 0; i < totalJogadores; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        printf("\nJogador %d (%s): ", i+1, coresJogadores[i]);
        exibirMissao(missoesJogadores[i]);
    }

    int vencedor = -1;
    int turno = 1;

    while (vencedor == -1) {
        printf("\n=== Turno %d ===\n", turno);
        exibirMapa(mapa, n);

        // Solicitar ataque do usuário
        int idxAtacante, idxDefensor;
        printf("Escolha o índice do território atacante: ");
        scanf("%d", &idxAtacante);
        printf("Escolha o índice do território defensor: ");
        scanf("%d", &idxDefensor);

        if (idxAtacante >= 0 && idxAtacante < n && idxDefensor >= 0 && idxDefensor < n) {
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
        } else {
            printf("Índices inválidos!\n");
        }

        // Verificação das missões
        for (int i = 0; i < totalJogadores; i++) {
            if (verificarMissao(missoesJogadores[i], mapa, n, coresJogadores[i])) {
                vencedor = i;
                break;
            }
        }

        turno++;
        if (turno > 50) break; // Limite de turnos
    }

    if (vencedor != -1) {
        printf("\nJogador %d (%s) venceu cumprindo a missão: %s\n", 
               vencedor+1, coresJogadores[vencedor], missoesJogadores[vencedor]);
    } else {
        printf("\nNenhum jogador venceu dentro do limite de turnos.\n");
    }

    liberarMemoria(mapa, missoesJogadores, totalJogadores);

    return 0;
}