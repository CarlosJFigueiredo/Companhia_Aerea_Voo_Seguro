#include <stdio.h>
#include <string.h>
#include "passageiros.h"

// Função para gerar o próximo código de passageiro em ordem crescente
int gerarCodigoPassageiro() {
    Passageiro passageiro;
    int ultimoCodigo = 0;
    FILE *file = fopen("passageiros.dat", "rb");

    if (!file) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return 1;
    }
    
    while (fread(&passageiro, sizeof(Passageiro), 1, file)) {
        if (passageiro.codigo > ultimoCodigo) {
            ultimoCodigo = passageiro.codigo;
        }
    }
    fclose(file);

    return ultimoCodigo + 1;
}

void cadastrarPassageiro() {
    Passageiro passageiro;
    FILE *file = fopen("passageiros.dat", "ab");

    if (!file) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    
    passageiro.codigo = gerarCodigoPassageiro();
    printf("Código do Passageiro: %d\n", passageiro.codigo);

    printf("Digite o nome do passageiro: ");
    scanf(" %[^\n]s", passageiro.nome);
    printf("Digite o endereço do passageiro: ");
    scanf(" %[^\n]s", passageiro.endereco);
    printf("Digite o telefone do passageiro: ");
    scanf(" %[^\n]s", passageiro.telefone);

    passageiro.pontosFidelidade = 0;
    printf("O passageiro é fidelidade? (1 para sim, 0 para não): ");
    scanf("%d", &passageiro.fidelidade);

    fwrite(&passageiro, sizeof(Passageiro), 1, file);
    printf("Passageiro cadastrado com sucesso!\n");

    fclose(file);
}

void buscarPassageiro(int codigo) {
    Passageiro passageiro;
    FILE *file = fopen("passageiros.dat", "rb");
    int encontrado = 0;
    char nome[100];

    if (!file) {
        printf("Arquivo de passageiros não encontrado. Cadastre pelo menos um passageiro antes de realizar a busca.\n");
        return;
    }

    if (codigo <= 0) {
        printf("Digite o nome do passageiro: ");
        scanf(" %[^\n]s", nome);
    }

    while (fread(&passageiro, sizeof(Passageiro), 1, file)) {
        if ((codigo > 0 && passageiro.codigo == codigo) ||
            (codigo <= 0 && strcmp(passageiro.nome, nome) == 0)) {
            printf("Passageiro encontrado!\n");
            printf("Código: %d\n", passageiro.codigo);
            printf("Nome: %s\n", passageiro.nome);
            printf("Endereço: %s\n", passageiro.endereco);
            printf("Telefone: %s\n", passageiro.telefone);
            printf("Pontos de Fidelidade: %d\n", passageiro.pontosFidelidade);
            printf("Fidelidade: %s\n", passageiro.fidelidade ? "Sim" : "Não");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Passageiro não encontrado.\n");
    }

    fclose(file);
}
