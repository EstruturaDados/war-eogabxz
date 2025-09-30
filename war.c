#include <stdio.h>
#include <string.h>

//struc territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    //armazenar 5 territorios
    struct Territorio territorios[5];

    //cadastro de territorios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território ");
        scanf(" %[^\n]", territorios[i].nome); //lê string com espaços

        printf("Digite a cor do exército: ");
        scanf(" %s", territorios[i].cor); //lê uma palavra (sem espaços)

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas); 
    }

    //exibir dados cadastrados
    printf("\n==== Territórios Cadastrados ====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}