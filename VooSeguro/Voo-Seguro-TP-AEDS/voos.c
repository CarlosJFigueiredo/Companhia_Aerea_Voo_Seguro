#include <stdio.h>
#include <string.h>
#include "voos.h"
#include "tripulacao.h"

// Função que verifica se o voo existe no arquivo
int vooExiste(int codigoVoo) {
    Voo voo;
    FILE *file = fopen("voos.dat", "rb");

    if (!file) {
        printf("Erro ao abrir o arquivo de voos.\n");
        return 0;
    }

    while (fread(&voo, sizeof(Voo), 1, file)) {
        if (voo.codigoVoo == codigoVoo) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}

// Função para cadastrar um voo
void cadastrarVoo() {
    Voo voo;
    Tripulacao tripulacao;
    int temPiloto = 0;
    int temCopiloto = 0;
    FILE *vooFile = fopen("voos.dat", "ab");
    FILE *tripulacaoFile = fopen("tripulacao.dat", "rb");

    if (!vooFile || !tripulacaoFile) {
        printf("Erro ao abrir os arquivos de voo ou tripulação.\n");
        return;
    }

    printf("Digite o código do voo: ");
    scanf("%d", &voo.codigoVoo);
    printf("Digite a data do voo: ");
    scanf(" %[^\n]s", voo.data);
    printf("Digite a hora do voo: ");
    scanf(" %[^\n]s", voo.hora);
    printf("Digite a origem do voo: ");
    scanf(" %[^\n]s", voo.origem);
    printf("Digite o destino do voo: ");
    scanf(" %[^\n]s", voo.destino);
    printf("Digite o código do avião: ");
    scanf("%d", &voo.codigoAviao);

    printf("Digite o código do piloto: ");
    scanf("%d", &voo.codigoPiloto);
    printf("Digite o código do copiloto: ");
    scanf("%d", &voo.codigoCopiloto);
    printf("Digite o código do comissário: ");
    scanf("%d", &voo.codigoComissario);

    while (fread(&tripulacao, sizeof(Tripulacao), 1, tripulacaoFile)) {
        if (tripulacao.codigo == voo.codigoPiloto && strcmp(tripulacao.cargo, "piloto") == 0) {
            temPiloto = 1;
        }
        if (tripulacao.codigo == voo.codigoCopiloto && strcmp(tripulacao.cargo, "copiloto") == 0) {
            temCopiloto = 1;
        }
    }

    if (temPiloto && temCopiloto) {
        voo.status = 1; 
        printf("Voo marcado como ativo.\n");
    } else {
        voo.status = 0;
        printf("Voo marcado como inativo. Necessário ter um piloto e um copiloto.\n");
    }

    printf("Digite a tarifa do voo: ");
    scanf("%f", &voo.tarifa);

    fwrite(&voo, sizeof(Voo), 1, vooFile);
    printf("Voo cadastrado com sucesso!\n");

    fclose(vooFile);
    fclose(tripulacaoFile);
}

// Função para listar voos do passageiro
void listarVoosPassageiro(int codigoPassageiro) {
    Voo voo;
    Reserva reserva;
    FILE *voosFile = fopen("voos.dat", "rb");
    FILE *reservasFile = fopen("reservas.dat", "rb");

    if (!voosFile || !reservasFile) {
        printf("Erro ao abrir os arquivos de voos ou reservas.\n");
        return;
    }

    printf("\n--- Voos do Passageiro %d ---\n", codigoPassageiro);
    int encontrado = 0;

    while (fread(&reserva, sizeof(Reserva), 1, reservasFile)) {
        if (reserva.codigoPassageiro == codigoPassageiro) {

            rewind(voosFile); 
            while (fread(&voo, sizeof(Voo), 1, voosFile)) {
                if (voo.codigoVoo == reserva.codigoVoo) {
                    
                    printf("Código do Voo: %d\n", voo.codigoVoo);
                    printf("Data: %s\n", voo.data);
                    printf("Hora: %s\n", voo.hora);
                    printf("Origem: %s\n", voo.origem);
                    printf("Destino: %s\n", voo.destino);
                    printf("Tarifa: %.2f\n", voo.tarifa);
                    printf("Status: %s\n", voo.status ? "Ativo" : "Inativo");
                    printf("\n");
                    encontrado = 1;
                }
            }
        }
    }

    if (!encontrado) {
        printf("Nenhum voo encontrado para o passageiro %d.\n", codigoPassageiro);
    }

    fclose(voosFile);
    fclose(reservasFile);
}
