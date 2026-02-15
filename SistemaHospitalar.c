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
    int prioridade; // 1 = Emergência, 2 = Urgência, 3 = Normal
} Paciente;

// lista de espera utilizando a estrutura lista encadadeada
typedef struct No {
    Paciente dados;
    struct No* prox;
} No;

// fila de atendimento, utilizando lista
typedef struct {
    No* inicio;
    No* fim;
} Fila;

// pilha de atendimentos
typedef struct NoPilha {
    Paciente dados;
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

// inicializa a fila
void inicializaFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// inicializa a pilha
Pilha* inicializaPilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro de alocação da pilha.\n");
        return NULL;
    }
    p->topo = NULL;
    return p;
}

/* Funções de impressão */
void imprimirPaciente(Paciente p){
	printf("ID: %d\n", p.id);
	printf("NOME: %s\n", p.nome);
	printf("IDADE: %d\n", p.idade);
	printf("PRIORIDADE: %d",p.prioridade);
	printf("\n------ --------- ------\n");
}

void imprimirFila(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    No* atual = fila->inicio;
    printf("\n=== FILA DE ESPERA ===\n");

    while (atual != NULL) {
        imprimirPaciente(atual->dados);
        atual = atual->prox;
    }
}

void imprimirPilha(Pilha* p) {
    if (p == NULL || p->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    NoPilha* atual = p->topo;
    printf("\n=== HISTÓRICO DE ATENDIMENTOS ===\n");

    while (atual != NULL) {
        imprimirPaciente(atual->dados);
        atual = atual->prox;
    }
}

/* Funções para manipulação da Fila */
void inserirFila(Fila* fila, Paciente paciente) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocação.\n");
        return;
    }

    novo->dados = paciente;
    novo->prox = NULL;

    // Se a fila estiver vazia

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    }
    // Se a fila já tiver elementos
    else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
}
// remover fila
Paciente removerFila(Fila* fila) {
    Paciente vazio = {-1, "", 0, 0};
    // fila vazia
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return vazio;
    }
    // copia os dados do paciente
    No* temp = fila->inicio;
    Paciente paciente = temp->dados;

    // atualiza o início da fila
    fila->inicio = temp->prox;

    // se a fila ficou vazia, atualiza o fim
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

     // Libera o nó removido
    free(temp);
    return paciente;
}

/* Funções para manipulação da Pilha */
void push(Pilha* p, Paciente paciente) {
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        printf("Erro de alocação.\n");
        return;
    }

    novo->dados = paciente;
    novo->prox = p->topo;
    p->topo = novo;
}

int pop(Pilha* p, Paciente* paciente) {
    if (p->topo == NULL) return 0;

    NoPilha* temp = p->topo;
    *paciente = temp->dados;
    p->topo = temp->prox;

    free(temp);
    return 1;
}


int main() {
    Fila fila;
    inicializaFila(&fila);

    Pilha* pilha = inicializaPilha();
    if (pilha == NULL) return 1;

    Paciente p1 = {1, "Maria", 40, EMERGENCIA};
    Paciente p2 = {2, "João", 25, URGENCIA};
    Paciente p3 = {3, "Ana", 30, NORMAL};

    inserirFila(&fila, p1);
    inserirFila(&fila, p2);
    inserirFila(&fila, p3);

    imprimirFila(&fila);

    Paciente atendido = removerFila(&fila);
    push(pilha, atendido);

    imprimirPilha(pilha);
    imprimirFila(&fila);

    return 0;
}

