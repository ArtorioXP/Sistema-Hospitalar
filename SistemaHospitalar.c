#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EMERGENCIA 1
#define URGENCIA   2
#define NORMAL     3

// estrutura paciente
typedef struct {
    int id;
    char nome[50];
    int idade;
    int prioridade; // 1 = Emergência,  2 = Urgência,  3 = Normal
} Paciente;


// lista de espera utilizando a estrutura lista encadadeada
typedef struct No{
    Paciente dados;
    struct No *prox;

} No;

// fila de atendimento, utilizando lista
typedef struct {
    No *inicio;
    No *fim;
} Fila;


// pilha de atendimentos
typedef struct NoPilha{
    Paciente dados;
    struct NoPilha* prox;
} NoPilha;

typedef struct{
    NoPilha* topo;
} Pilha;
