#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//struct territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//função de cadastro automático de territórios
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

//exibir territórios cadastrados
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== Territórios no Mapa =====\n");
    for (int i = 0; i < n; i++)
    {
        printf("\n[%d] Nome: %s\n", i, mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

//simulação de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if(strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n O ATACANTE E O DEFENSOR POSSUEM A MESMA COR. ATAQUE INVÁLIDO.");
        return;
    }

    printf("\n Rolando os dados...\n");
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("%s (atacante) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor)
    {
        printf("\n O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor); //mudar a cor, caso vitória do atacante
        defensor->tropas = atacante->tropas / 2; //metade das tropas do atacante ocupa
        printf("%s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);  
    } else {
        printf("\n O defensor resisitiu! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas > 0)
        {
            atacante->tropas -= 1;
        }
    }
}

//função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\n Memória liberada com sucesso!\n");
}

int main() {
    srand(time(NULL));

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    //alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL)
    {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa,n);

    int idxAtacante, idxDefensor;
    printf("\nEscolha o índice do território atacante: ");
    scanf("%d", &idxAtacante);

    printf("Escolha o índice do território defensor: ");
    scanf("%d", &idxDefensor);

    if (idxAtacante >= 0 && idxAtacante < n && idxDefensor < n)
    {
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
    } else {
        printf("\n Índices inválidos!\n");
    }
    
    ////exibe o resultado final dos territórios
    exibirTerritorios(mapa,n);

    liberarMemoria(mapa);
    return 0;
}