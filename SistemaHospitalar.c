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
Pilha* InicizalizarPilha(){
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro de alocação!\n");
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

void imprimirPilha(Pilha* p) {
	
    printf("--- PILHA DE ATENDIMENTOS ---\n");
	
    if (p == NULL || p->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    NoPilha* atual = p->topo;

    while (atual != NULL) {
        imprimirPaciente(atual->dados);
        atual = atual->prox;
    }

    printf("\n--- -------------------- ---\n");
}

/* Funções para manipulação da Fila */

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

/* Funções para manipulação da Pilha */

void push(Pilha* p, Paciente pessoa) {					
    NoPilha* novoNo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novoNo == NULL) {
        printf("Erro de alocação!\n");
        return;
    }

    novoNo->dados = pessoa;
    novoNo->prox = p->topo;
    p->topo = novoNo;
}

int pop(Pilha* p, Paciente* pessoa) {
    if (p->topo == NULL) {
        return 0;
    }

    NoPilha* temp = p->topo;
    *pessoa = temp->dados;
    p->topo = temp->prox;

    free(temp);
    return 1;
}

int main(){
	
    Pilha* pilha = InicizalizarPilha(&pilha);
    return 0;
}
