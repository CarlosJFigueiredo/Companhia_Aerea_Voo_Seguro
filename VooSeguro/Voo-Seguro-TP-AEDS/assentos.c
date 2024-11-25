#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include "voos.h"



// Função para verificar se um assento já existe no voo
bool assentoExiste(int codigoVoo, int numeroAssento) {
    Assento assento;
    FILE *file = fopen("assentos.dat", "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return false;
    }

    while (fread(&assento, sizeof(Assento), 1, file)) {
        if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Função para cadastrar um assento
void cadastrarAssento(int codigoVoo) {
    if (!vooExiste(codigoVoo)) {
        printf("Erro: O voo com código %d não existe.\n", codigoVoo);
        return;
    }

    Assento assento;
    printf("Digite o número do assento: ");
    scanf("%d", &assento.numeroAssento);

    if (assentoExiste(codigoVoo, assento.numeroAssento)) {
        printf("Erro: O assento %d já está cadastrado para o voo %d.\n", assento.numeroAssento, codigoVoo);
        return;
    }

    FILE *file = fopen("assentos.dat", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }

    assento.codigoVoo = codigoVoo;
    assento.status = 0; 

    fwrite(&assento, sizeof(Assento), 1, file);
    fclose(file);
    printf("Assento %d cadastrado com sucesso para o voo %d.\n", assento.numeroAssento, codigoVoo);
}


// Função para listar assentos de um voo
void listarAssentos(int codigoVoo) {
    Assento assento;
    FILE *file = fopen("assentos.dat", "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }

    printf("Assentos para o voo %d:\n", codigoVoo);
    bool encontrouAssentos = false;

    while (fread(&assento, sizeof(Assento), 1, file)) {
        if (assento.codigoVoo == codigoVoo) {
            printf("Assento %d - %s\n", assento.numeroAssento, assento.status == 0 ? "Livre" : "Ocupado");
            encontrouAssentos = true;
        }
    }

    if (!encontrouAssentos) {
        printf("Nenhum assento cadastrado para o voo %d.\n", codigoVoo);
    }

    fclose(file);
}
