#include <stdio.h>
#include "passageiros.h"
#include "tripulacao.h"
#include "voos.h"
#include "assentos.h"
#include "reservas.h"
#include "fidelidade.h"

void menu() {
    int opcao;

    do {
        printf("\n     VOO SEGURO    \n");
        printf("\n--- Menu Principal ---\n");
        printf("1. Cadastrar Passageiro\n");
        printf("2. Cadastrar Tripulação\n");
        printf("3. Cadastrar Voo\n");
        printf("4. Cadastrar Assento\n");
        printf("5. Criar Reserva\n");
        printf("6. Dar baixa em Reserva\n");
        printf("7. Consultar Fidelidade\n");
        printf("8. Buscar Passageiro\n");
        printf("9. Buscar Tripulação\n");
        printf("10. Listar Voos de Passageiro\n");
        printf("11. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarPassageiro();
                break;
            case 2:
                cadastrarTripulacao();
                break;
            case 3:
                cadastrarVoo();
                break;
            case 4: {
                int codigoVoo;
                printf("Digite o código do voo: ");
                scanf("%d", &codigoVoo);
                cadastrarAssento(codigoVoo);
                break;
            }
            case 5:
                criarReserva();
                break;
            case 6:
                darBaixaReserva(); 
                break;
            case 7: {
                int codigoPassageiro;
                printf("Digite o código do passageiro: ");
                scanf("%d", &codigoPassageiro);
                consultarPontosFidelidade(codigoPassageiro);
                break;
            }
            case 8: {
                int codigo;
                printf("Digite o código do passageiro (ou 0 para buscar pelo nome): ");
                scanf("%d", &codigo);
                buscarPassageiro(codigo);
                break;
            }
            case 9: {
                int codigo;
                printf("Digite o código do tripulante (ou 0 para buscar pelo nome): ");
                scanf("%d", &codigo);
                buscarTripulacao(codigo);
                break;
            }
            case 10: {
                int codigoPassageiro;
                printf("Digite o código do passageiro: ");
                scanf("%d", &codigoPassageiro);
                listarVoosPassageiro(codigoPassageiro);
                break;
            }
            case 11:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 11);
}

int main() {
    menu();
    return 0;
}
