#include "reservas.h"
#include "voos.h"
#include "assentos.h"
#include "fidelidade.h"

#include <stdio.h>




void criarReserva() {
    Reserva reserva;
    FILE *reservasFile = fopen("reservas.dat", "ab");
    FILE *voosFile = fopen("voos.dat", "rb");
    FILE *assentosFile = fopen("assentos.dat", "rb+");

    if (!reservasFile || !voosFile || !assentosFile) {
        printf("Erro ao abrir os arquivos necessários para criar a reserva.\n");
        if (reservasFile) fclose(reservasFile);
        if (voosFile) fclose(voosFile);
        if (assentosFile) fclose(assentosFile);
        return;
    }

    printf("Digite o código do voo: ");
    scanf("%d", &reserva.codigoVoo);
    printf("Digite o número do assento: ");
    scanf("%d", &reserva.numeroAssento);
    printf("Digite o código do passageiro: ");
    scanf("%d", &reserva.codigoPassageiro);

    Voo voo;
    Assento assento;
    int vooExiste = 0;
    int assentoDisponivel = 0;



    while (fread(&voo, sizeof(Voo), 1, voosFile)) {
        if (voo.codigoVoo == reserva.codigoVoo) {
            vooExiste = 1;
            break;
        }
    }
    
    rewind(assentosFile);
    while (fread(&assento, sizeof(Assento), 1, assentosFile)) {
        if (assento.codigoVoo == reserva.codigoVoo && assento.numeroAssento == reserva.numeroAssento) {
            if (assento.status == 0) {
                assentoDisponivel = 1;
            }
            break;
        }
    }

    if (vooExiste && assentoDisponivel) {
        fwrite(&reserva, sizeof(Reserva), 1, reservasFile);

        assento.status = 1;
        fseek(assentosFile, -sizeof(Assento), SEEK_CUR);
        fwrite(&assento, sizeof(Assento), 1, assentosFile);

        printf("Reserva realizada com sucesso para o passageiro %d no voo %d, assento %d.\n",
               reserva.codigoPassageiro, reserva.codigoVoo, reserva.numeroAssento);
    } else {
        if (!vooExiste) {
            printf("Erro: Voo com código %d não encontrado.\n", reserva.codigoVoo);
        }
        if (!assentoDisponivel) {
            printf("Erro: Assento %d no voo %d não está disponível ou não existe.\n",
                   reserva.numeroAssento, reserva.codigoVoo);
        }
    }
    
    adicionarPontosFidelidade(reserva.codigoPassageiro, 10);
    printf("10 pontos de fidelidade adicionados ao passageiro %d.\n", reserva.codigoPassageiro);


    fclose(reservasFile);
    fclose(voosFile);
    fclose(assentosFile);
}


void darBaixaReserva() {
    Reserva reserva;
    Assento assento;
    FILE *reservasFile = fopen("reservas.dat", "rb");
    FILE *assentosFile = fopen("assentos.dat", "rb+");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (!reservasFile || !assentosFile || !tempFile) {
        printf("Erro ao abrir os arquivos necessários para dar baixa na reserva.\n");
        if (reservasFile) fclose(reservasFile);
        if (assentosFile) fclose(assentosFile);
        if (tempFile) fclose(tempFile);
        return;
    }

    int codigoVoo, numeroAssento;
    printf("Digite o código do voo: ");
    scanf("%d", &codigoVoo);
    printf("Digite o número do assento: ");
    scanf("%d", &numeroAssento);

    int reservaEncontrada = 0;

    while (fread(&reserva, sizeof(Reserva), 1, reservasFile)) {
        if (reserva.codigoVoo == codigoVoo && reserva.numeroAssento == numeroAssento) {
            reservaEncontrada = 1;

            rewind(assentosFile);
            while (fread(&assento, sizeof(Assento), 1, assentosFile)) {
                if (assento.codigoVoo == codigoVoo && assento.numeroAssento == numeroAssento) {
                    assento.status = 0; 
                    fseek(assentosFile, -sizeof(Assento), SEEK_CUR);
                    fwrite(&assento, sizeof(Assento), 1, assentosFile);
                    break;
                }
            }
        } else {
            fwrite(&reserva, sizeof(Reserva), 1, tempFile);
        }
    }

    if (reservaEncontrada) {
        printf("Reserva para o voo %d, assento %d removida com sucesso.\n", codigoVoo, numeroAssento);
    } else {
        printf("Erro: Reserva não encontrada para o voo %d e assento %d.\n", codigoVoo, numeroAssento);
    }

    fclose(reservasFile);
    fclose(assentosFile);
    fclose(tempFile);

    remove("reservas.dat");
    rename("temp.dat", "reservas.dat");
}
