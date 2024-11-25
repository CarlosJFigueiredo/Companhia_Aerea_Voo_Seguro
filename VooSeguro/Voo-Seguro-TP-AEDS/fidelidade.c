#include "fidelidade.h"
#include "utils.h"
#include "voos.h"

#include <stdio.h>

// Função para adicionar pontos de fidelidade a um passageiro
void adicionarPontosFidelidade(int codigoPassageiro, int pontos) {
    Passageiro passageiro;
    FILE *file = fopen("passageiros.dat", "rb+");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    while (fread(&passageiro, sizeof(Passageiro), 1, file)) {
        if (passageiro.codigo == codigoPassageiro) {
            passageiro.pontosFidelidade += pontos;
            fseek(file, -sizeof(Passageiro), SEEK_CUR);
            fwrite(&passageiro, sizeof(Passageiro), 1, file);
            printf("Pontos adicionados ao passageiro %s\n", passageiro.nome);
            fclose(file);
            return;
        }
    }

    printf("Passageiro não encontrado.\n");
    fclose(file);
}

// Função para consultar os pontos de fidelidade de um passageiro
void consultarPontosFidelidade(int codigoPassageiro) {
    Passageiro passageiro;
    FILE *file = fopen("passageiros.dat", "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    while (fread(&passageiro, sizeof(Passageiro), 1, file)) {
        if (passageiro.codigo == codigoPassageiro) {
            printf("Passageiro: %s - Pontos: %d\n", passageiro.nome, passageiro.pontosFidelidade);
            fclose(file);
            return;
        }
    }

    printf("Passageiro não encontrado.\n");
    fclose(file);
}

void registrarVoo(int codigoVoo, int codigoPassageiro) {
    if (!vooExiste(codigoVoo)) {
        printf("Erro: O voo com código %d não existe.\n", codigoVoo);
        return;
    }

    adicionarPontosFidelidade(codigoPassageiro, 10);
    printf("Voo %d registrado para o passageiro %d.\n", codigoVoo, codigoPassageiro);
}

