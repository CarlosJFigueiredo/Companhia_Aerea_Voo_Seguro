#include "tripulacao.h"
#include <stdio.h>
#include <string.h>

void cadastrarTripulacao() {
    Tripulacao t;
    FILE *file = fopen("tripulacao.dat", "ab+");
    int maiorCodigo = 0;

    printf("Digite o nome: ");
    scanf(" %[^\n]s", t.nome);
    printf("Digite o telefone: ");
    scanf(" %[^\n]s", t.telefone);
    printf("Digite o cargo (piloto, copiloto, comissário): ");
    scanf(" %[^\n]s", t.cargo);

    rewind(file);


    Tripulacao temp;
    while (fread(&temp, sizeof(Tripulacao), 1, file) == 1) {
        if (strcmp(temp.cargo, t.cargo) == 0 && temp.codigo > maiorCodigo) {
            maiorCodigo = temp.codigo;
        }
    }

    t.codigo = maiorCodigo + 1;

    fseek(file, 0, SEEK_END);
    fwrite(&t, sizeof(Tripulacao), 1, file);
    fclose(file);

    printf("Tripulante cadastrado com sucesso! Código: %d\n", t.codigo);
}

void buscarTripulacao(int codigo) {
    Tripulacao tripulante;
    FILE *file = fopen("tripulacao.dat", "rb");
    int encontrado = 0;
    char nome[100];

    if (!file) {
        printf("Erro ao abrir o arquivo de tripulação.\n");
        return;
    }

    if (codigo <= 0) {
        printf("Digite o nome do tripulante: ");
        scanf(" %[^\n]s", nome);
    }

    while (fread(&tripulante, sizeof(Tripulacao), 1, file)) {
        if ((codigo > 0 && tripulante.codigo == codigo) ||
            (codigo <= 0 && strcmp(tripulante.nome, nome) == 0)) {
            printf("Tripulante encontrado!\n");
            printf("Código: %d\n", tripulante.codigo);
            printf("Nome: %s\n", tripulante.nome);
            printf("Telefone: %s\n", tripulante.telefone);
            printf("Cargo: %s\n", tripulante.cargo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Tripulante não encontrado.\n");
    }

    fclose(file);
}
