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

void menu() {
    printf("\n===== SISTEMA HOSPITALAR =====\n");
    printf("1 - Inserir paciente na fila\n");
    printf("2 - Atender paciente\n");
    printf("3 - Mostrar fila de espera\n");
    printf("4 - Mostrar histórico de atendimentos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// main

int main() {
    Fila fila;
    inicializaFila(&fila);

    Pilha* pilha = inicializaPilha();
    if (pilha == NULL) return 1;

    int op;
    Paciente p;

    do {
        menu();
        scanf("%d", &op);
        getchar(); // limpa buffer

        switch (op) {
            case 1:
                printf("ID: ");
                scanf("%d", &p.id);
                getchar();

                printf("Nome: ");
                fgets(p.nome, 50, stdin);
                p.nome[strcspn(p.nome, "\n")] = '\0';

                printf("Idade: ");
                scanf("%d", &p.idade);

                printf("Prioridade (1-Emergência, 2-Urgência, 3-Normal): ");
                scanf("%d", &p.prioridade);

                inserirFila(&fila, p);
                break;

            case 2: {
                Paciente atendido = removerFila(&fila);
                if (atendido.id != -1) {
                    push(pilha, atendido);
                    printf("Paciente atendido:\n");
                    imprimirPaciente(atendido);
                }
                break;
            }

            case 3:
                imprimirFila(&fila);
                break;

            case 4:
                imprimirPilha(pilha);
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (op != 0);

    return 0;
}


