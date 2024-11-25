#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char endereco[MAX_NOME];
    char telefone[15];
    int fidelidade; 
    int pontosFidelidade;
} Passageiro;

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char telefone[15];
    char cargo[15]; 
} Tripulacao;

typedef struct {
    int codigoVoo;
    char data[11];
    char hora[6];
    char origem[MAX_NOME];
    char destino[MAX_NOME];
    int codigoAviao;
    int codigoPiloto;
    int codigoCopiloto;
    int codigoComissario;
    int status; 
    float tarifa;
} Voo;

typedef struct {
    int numeroAssento;
    int codigoVoo;
    int status; 
} Assento;

typedef struct {
    int codigoVoo;
    int numeroAssento;
    int codigoPassageiro;
} Reserva;

#endif
