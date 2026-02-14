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

// inicializa a fila
void InicializaFila(Fila* fila){
    fila -> inicio = NULL;
    fila -> fim = NULL;
}
// inicializa a pilha
void InicializaPilha(Pilha* pilha){
    pilha -> topo = NULL;
}

void insercaoFila(Fila* fila, Paciente pessoa) {
    No* novoPaciente = (No*) malloc(sizeof(No));

    if (novoPaciente == NULL) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    novoPaciente->dados = pessoa;
    novoPaciente->prox = NULL;

    // Se a fila estiver vazia
    if (fila->fim == NULL) {
        fila->inicio = novoPaciente;
        fila->fim = novoPaciente;
    }
    // Se a fila já tiver elementos
    else {
        fila->fim->prox = novoPaciente;
        fila->fim = novoPaciente;
    }
}


// remover fila
Paciente removerFila(Fila* fila) {
    No* auxiliar = fila->inicio;
    Paciente pessoa;

    // fila vazia
    if (auxiliar == NULL) {
        printf("Fila vazia\n");
        pessoa.id = -1;
        return pessoa;
    }

    // copia os dados do paciente
    pessoa = auxiliar->dados;

    // atualiza o início da fila
    fila->inicio = auxiliar->prox;

    // se a fila ficou vazia, atualiza o fim
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    // Libera o nó removido
    free(auxiliar);

    return pessoa;
}
