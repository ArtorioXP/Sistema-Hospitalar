#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

#define EMERGENCIA 1
#define URGENCIA   2
#define NORMAL     3

#define IDADE_MIN 1
#define IDADE_MAX 150
#define ID_MIN 1
#define PRIORIDADE_INVALIDA -1

// estrutura paciente
typedef struct {
    int id;
    char nome[100];
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

/* Funções auxiliares de validação */
int validarPrioridade(int prioridade) {
    return (prioridade >= EMERGENCIA && prioridade <= NORMAL);
}

int validarIdade(int idade) {
    return (idade >= IDADE_MIN && idade <= IDADE_MAX);
}

int validarID(int id) {
    return (id >= ID_MIN);
}

const char* obterNomePrioridade(int prioridade) {
    switch (prioridade) {
        case EMERGENCIA: return "Emergência";
        case URGENCIA:   return "Urgência";
        case NORMAL:     return "Normal";
        default:         return "Desconhecida";
    }
}

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
	printf("IDADE: %d anos\n", p.idade);
	printf("PRIORIDADE: %s (%d)\n", obterNomePrioridade(p.prioridade), p.prioridade);
	printf("------ --------- ------\n");
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

void limparTela(){
	#ifdef _WIN32
		system("cls");
	#elif __linux__
		system("clear");
	#endif
}

/* Funções para manipulação da Fila */
// Inserir respeitando prioridade (fila de prioridade)
void inserirFila(Fila* fila, Paciente paciente) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("ERRO: Falha na alocação de memória para novo paciente.\n");
        return;
    }

    novo->dados = paciente;
    novo->prox = NULL;

    // Se a fila estiver vazia
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
        printf("Paciente %s inserido na fila (primeira posição).\n", paciente.nome);
        return;
    }

    // Percorre a fila para encontrar a posição correta baseada na prioridade
    // Pacientes com prioridade menor (1=emergência) vêm antes
    if (paciente.prioridade < fila->inicio->dados.prioridade) {
        // Inserir no início
        novo->prox = fila->inicio;
        fila->inicio = novo;
        printf("Paciente %s inserido na fila (início - alta prioridade).\n", paciente.nome);
        return;
    }

    No* atual = fila->inicio;
    while (atual->prox != NULL && atual->prox->dados.prioridade <= paciente.prioridade) {
        atual = atual->prox;
    }

    // Inserir após 'atual'
    novo->prox = atual->prox;
    atual->prox = novo;

    if (novo->prox == NULL) {
        fila->fim = novo;
    }

    printf("Paciente %s inserido na fila.\n", paciente.nome);
}

// remover fila (sempre remove o primeiro, que é o de maior prioridade)
Paciente removerFila(Fila* fila) {
    Paciente vazio = {-1, "", 0, PRIORIDADE_INVALIDA};
    // fila vazia
    if (fila->inicio == NULL) {
        printf("ERRO: Fila vazia. Nenhum paciente para atender.\n");
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

/* Funções de limpeza (liberar memória) */
void destruirFila(Fila* fila) {
    if (fila == NULL) return;

    No* atual = fila->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

void destruirPilha(Pilha* p) {
    if (p == NULL) return;

    NoPilha* atual = p->topo;
    while (atual != NULL) {
        NoPilha* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(p);
}

// FUNÇÕES DE BUSCA
Paciente buscarPacientePorID(Fila* fila, int id) {
    Paciente vazio = {-1, "", 0, PRIORIDADE_INVALIDA};

    No* atual = fila->inicio;
    while (atual) {
        if (atual->dados.id == id)
            return atual->dados;
        atual = atual->prox;
    }

    return vazio;
}

void buscarPaciente(Fila* fila) {
    int id;
    printf("\nID do paciente: ");
    scanf("%d", &id);
    getchar();

    Paciente p = buscarPacientePorID(fila, id);
    if (p.id == -1)
        printf("Paciente não encontrado.\n");
    else
        imprimirPaciente(p);
}

void menu() {
    printf("\n===== SISTEMA HOSPITALAR =====\n");
    printf("1 - Inserir paciente na fila\n");
    printf("2 - Atender paciente\n");
    printf("3 - Desfazer atendimento\n");
    printf("4 - Buscar paciente por ID\n");
    printf("5 - Mostrar fila de espera\n");
    printf("6 - Mostrar histórico de atendimentos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// Função auxiliar para ler entrada de forma segura
int lerInteiro(int minimo) {
    int valor;
    int resultado = scanf("%d", &valor);

    // Limpa buffer de entrada
    while (getchar() != '\n');

    if (resultado != 1) {
        printf("ERRO: Entrada inválida. Digite um número inteiro.\n");
        return -1;
    }

    if (valor < minimo) {
        printf("ERRO: Valor deve ser >= %d.\n", minimo);
        return -1;
    }

    return valor;
}

// Função para ler string de forma segura
void lerString(char* buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
        while (getchar() != '\n'); // Limpa buffer
    }
}

// Função para cadastrar um novo paciente
void cadastrarPaciente(Fila* fila) {
    Paciente p;

    printf("\n=== CADASTRO DE PACIENTE ===\n");

    // Ler ID
    printf("ID do paciente: ");
    p.id = lerInteiro(ID_MIN);
    if (p.id == -1) return;

    // Ler nome
    printf("Nome do paciente: ");
    lerString(p.nome, 100);
    if (strlen(p.nome) == 0) {
        printf("ERRO: Nome não pode ser vazio.\n");
        return;
    }

    // Ler idade
    printf("Idade do paciente: ");
    p.idade = lerInteiro(IDADE_MIN);
    if (p.idade == -1 || !validarIdade(p.idade)) {
        printf("ERRO: Idade deve estar entre %d e %d anos.\n", IDADE_MIN, IDADE_MAX);
        return;
    }

    // Ler prioridade
    printf("Prioridade (1-Emergência, 2-Urgência, 3-Normal): ");
    p.prioridade = lerInteiro(EMERGENCIA);
    if (p.prioridade == -1 || !validarPrioridade(p.prioridade)) {
        printf("ERRO: Prioridade deve ser 1, 2 ou 3.\n");
        return;
    }

    inserirFila(fila, p);
}

int desfazerAtendimento(Fila* fila, Pilha* historico) {

    if (historico == NULL || historico->topo == NULL) {
        printf("Nao ha atendimentos para desfazer.\n");
        return 0;
    }

    Paciente pacienteDesfeito;

    if (!pop(historico, &pacienteDesfeito)) {
        return 0;
    }

    inserirFila(fila, pacienteDesfeito);

    printf("Atendimento de %s desfeito com sucesso.\n", pacienteDesfeito.nome);

    return 1;
}


// main

int main() {

	setlocale(LC_ALL, "pt_BR.UTF-8");

    Fila fila;
    inicializaFila(&fila);

    Pilha* pilha = inicializaPilha();
    if (pilha == NULL) {
        printf("ERRO: Falha ao inicializar a pilha de histórico.\n");
        return 1;
    }

    int op;

    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO SISTEMA HOSPITALAR    ║\n");
    printf("╚════════════════════════════════════════╝\n");

    do {
        menu();
        op = lerInteiro(0);
        if (op == -1) {
            printf("Digite uma opção válida (0-4).\n");
            continue;
        }

        switch (op) {
            case 1:
				limparTela();
                cadastrarPaciente(&fila);
                break;

            case 2: {
				limparTela();
                Paciente atendido = removerFila(&fila);
                if (atendido.id != -1) {
                    push(pilha, atendido);
                    printf("\n✓ PACIENTE ATENDIDO:\n");
                    imprimirPaciente(atendido);
                }
                break;
            }

            case 3:
				limparTela();
				desfazerAtendimento(&fila,pilha);
				break;

            case 4:
                limparTela();
                buscarPaciente(&fila);
                break;

            case 5:
				limparTela();
                imprimirFila(&fila);
                break;

            case 6:
				limparTela();
                imprimirPilha(pilha);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                printf("Limpando memória...\n");
                destruirFila(&fila);
                destruirPilha(pilha);
                printf("Sistema encerrado com sucesso.\n\n");
                break;

            default:
                printf("ERRO: Opção inválida. Escolha entre 0 e 4.\n");
        }

    } while (op != 0);

    return 0;
}
