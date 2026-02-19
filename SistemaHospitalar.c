// Bibliotecas padrão do C
#include <stdlib.h>  // Alocação de memória (malloc, free)
#include <stdio.h>   // Entrada/saída padrão (printf, scanf)
#include <string.h>  // Manipulação de strings (strlen, strcpy)
#include <limits.h>  // Limites de valores inteiros
#include <locale.h>  // Configuração de localização (suporte a português)

// Constantes de prioridade: quanto menor o número, maior a prioridade
#define EMERGENCIA 1  // Máxima prioridade - atendimento imediato
#define URGENCIA   2  // Prioridade média
#define NORMAL     3  // Mínima prioridade

#define IDADE_MIN 1            // Idade mínima permitida
#define IDADE_MAX 150          // Idade máxima permitida
#define ID_MIN 1               // ID mínimo válido
#define PRIORIDADE_INVALIDA -1 // Valor sentinel para paciente inválido

// Estrutura de dados para armazenar informações de um paciente
// Esta é a estrutura fundamental do sistema
typedef struct {
    int id;              // Identificador único do paciente
    char nome[100];      // Nome
    int idade;           // Idade em anos
    int prioridade;      // 1=Emergência, 2=Urgência, 3=Normal (quanto menor o número, maior a prioridade)
} Paciente;

// Nó da lista encadeada - cada nó contém um paciente e aponta para o próximo
// Implementa a fila de espera de pacientes
typedef struct No {
    Paciente dados;      // Dados do paciente armazenado neste nó
    struct No* prox;     // Ponteiro para o próximo nó (NULL se for o último)
} No;

// Fila de atendimento - estrutura que gerencia a lista encadeada
// Mantém ponteiros para início e fim para operações eficientes
// (inserção no final em O(1), remoção do início em O(1))
typedef struct {
    No* inicio;  // Ponteiro para o primeiro paciente a atender (cabeça da lista)
    No* fim;     // Ponteiro para o último paciente inserido (cauda da lista)
} Fila;

// Nó da pilha - estrutura idêntica ao nó da fila, mas usada para histórico
// LIFO (Last In, First Out) - o último atendido é o primeiro a ser desfeito
typedef struct NoPilha {
    Paciente dados;       // Dados do paciente atendido
    struct NoPilha* prox; // Ponteiro para o próximo nó na pilha (próximo histórico)
} NoPilha;

// Pilha - estrutura que armazena o histórico de atendimentos
// Permite desfazer o último atendimento (operação pop)
typedef struct {
    NoPilha* topo;  // Ponteiro para o topo da pilha (último atendimento)
} Pilha;

// Array estático global para manter contadores do sistema
// Índices: [0]=Total cadastrados, [1]=Total atendidos, [2]=Total desfeitos
int estatisticas[3] = {0, 0, 0};

// ============= FUNÇÕES DE VALIDAÇÃO =============
// Validam os dados de entrada do usuário para garantir o correto funcionamento

// Verifica se a prioridade é válida (entre 1 e 3)
int validarPrioridade(int prioridade) {
    return (prioridade >= EMERGENCIA && prioridade <= NORMAL);
}

// Verifica se a idade está dentro do intervalo aceitável
int validarIdade(int idade) {
    return (idade >= IDADE_MIN && idade <= IDADE_MAX);
}

// Verifica se o ID é válido (deve ser positivo)
int validarID(int id) {
    return (id >= ID_MIN);
}

// Função utilitária: converte número de prioridade em texto legível
// Exemplo: 1 retorna "Emergência"
const char* obterNomePrioridade(int prioridade) {
    switch (prioridade) {
        case EMERGENCIA: return "Emergência";
        case URGENCIA:   return "Urgência";
        case NORMAL:     return "Normal";
        default:         return "Desconhecida";
    }
}

// ============= FUNÇÕES DE INICIALIZAÇÃO =============

// Inicializa uma fila vazia
void inicializaFila(Fila* fila) {
    fila->inicio = NULL;  // Sem primeiro paciente
    fila->fim = NULL;     // Sem último paciente
}

// Aloca memória e inicializa uma nova pilha para o histórico
Pilha* inicializaPilha() {
    // Aloca memória para a pilha
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro de alocação da pilha.\n");
        return NULL;
    }
    p->topo = NULL;  // Pilha começa vazia
    return p;
}

// ============= FUNÇÕES DE IMPRESSÃO =============

// Imprime os dados de um único paciente de forma formatada
void imprimirPaciente(Paciente p){
	printf("\nID: %d\n", p.id);
	printf("NOME: %s\n", p.nome);
	printf("IDADE: %d anos\n", p.idade);
	printf("PRIORIDADE: %s (%d)\n", obterNomePrioridade(p.prioridade), p.prioridade);
	printf("------ --------- ------\n");
}

// Imprime todos os pacientes em espera na fila, ordenados por prioridade
void imprimirFila(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }

    // Percorre a lista encadeada do início até o fim
    No* atual = fila->inicio;
    printf("\n=== FILA DE ESPERA ===");

    while (atual != NULL) {
        imprimirPaciente(atual->dados);
        atual = atual->prox;  // Avança para o próximo nó
    }
}

// Imprime todo o histórico de atendimentos (do mais recente para o mais antigo)
void imprimirPilha(Pilha* p) {
    if (p == NULL || p->topo == NULL) {
        printf("Pilha vazia.\n");
        return;
    }

    // Percorre a pilha do topo até a base (ordem LIFO - Last In, First Out)
    NoPilha* atual = p->topo;
    printf("\n=== HISTÓRICO DE ATENDIMENTOS ===");

    while (atual != NULL) {
        imprimirPaciente(atual->dados);
        atual = atual->prox;  // Vai para o próximo paciente do histórico
    }
}

// Exibe o relatório geral do sistema com estatísticas
void exibirRelatorio() {
    printf("RELATÓRIO DE PACIENTES\n");
    printf("Total de Pacientes Cadastrados: %d\n", estatisticas[0]);
    printf("Total de Pacientes Atendidos: %d\n", estatisticas[1]);
    printf("Total de Pacientes Desfeitos: %d\n", estatisticas[2]);
    // Calcula pacientes em espera: cadastrados - atendidos
    printf("Pacientes em Espera (Fila): %d\n", estatisticas[0] - estatisticas[1]);
}

// Limpa a tela do console de forma compatível (Windows ou Linux)
void limparTela(){
	#ifdef _WIN32
		system("cls");       // Comando Windows
	#elif __linux__
		system("clear");     // Comando Linux/macOS
	#endif
}

// ============= FUNÇÕES DE FILA =============
// CONCEITO IMPORTANTE: Este é uma fila de PRIORIDADE (Priority Queue)
// Pacientes NÃO entram na ordem de chegada, mas sim ORDENADOS por prioridade
// Prioridades: 1=Emergência (máxima) → 2=Urgência → 3=Normal (mínima)
// Quanto MENOR o número, MAIOR a prioridade de atendimento

void inserirFila(Fila* fila, Paciente paciente) {
    // PASSO 1: Aloca memória para um novo nó armazenar o paciente cadastrado
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("ERRO: Falha na alocação de memória para novo paciente.\n");
        return;
    }

    novo->dados = paciente;
    novo->prox = NULL;

    // PASSO 2: VERIFICA SE FILA ESTÁ VAZIA
    // Se a fila estiver vazia, o novo paciente é o primeiro e último
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
        printf("Paciente %s inserido na fila (primeira posição).\n", paciente.nome);
        return;
    }

    // PASSO 3: VERIFICA INSERÇÃO NO INÍCIO
    // Se o novo paciente tem prioridade MAIOR (número MENOR) que o primeiro
    // Exemplo: Novo=1(Emergência), Primeiro=3(Normal) → Novo vai para frente
    if (paciente.prioridade < fila->inicio->dados.prioridade) {
        novo->prox = fila->inicio;  // Novo aponta para quem era o primeiro
        fila->inicio = novo;        // Novo vira o novo primeiro
        printf("Paciente %s inserido na fila (início - alta prioridade).\n", paciente.nome);
        return;
    }

    // PASSO 4: ENCONTRA A POSIÇÃO CORRETA NO MEIO/FIM
    // Este loop é a PARTE MAIS COMPLEXA - ler com atenção:
    // 
    // Começamos em 'atual' no primeiro paciente
    // Enquanto houver próximo paciente (atual->prox != NULL) e
    // a prioridade do PRÓXIMO for MENOR ou IGUAL ao novo
    // continua avançando o 'atual' para encontrar o ponto de inserção
    //
    // Exemplo com fila de tamanho 3:
    // Fila atual:   [P1:prio=2] -> [P2:prio=2] -> [P3:prio=3]
    // Novo atual:   Novo paciente com prioridade=2
    // 
    // Iteração 1: atual aponta para P1
    //   - P1->prox é P2 (não é NULL)
    //   - P2->prioridade (2) <= prioridade nova (2) é VERDADEIRO
    //   - Then: atual = P2
    // Iteração 2: atual aponta para P2
    //   - P2->prox é P3 (não é NULL)
    //   - P3->prioridade (3) <= prioridade nova (2) é FALSO
    //   - Loop termina com atual em P2
    // Resultado: Novo será inserido ENTRE P2 e P3
    
    No* atual = fila->inicio;
    while (atual->prox != NULL && atual->prox->dados.prioridade <= paciente.prioridade) {
        atual = atual->prox;  // Avança para o próximo nó
    }

    // PASSO 5: REALIZA A INSERÇÃO
    // Insere o novo paciente após 'atual'
    novo->prox = atual->prox;  // Novo aponta para quem 'atual' apontava
    atual->prox = novo;        // 'atual' agora aponta para novo

    // Se o novo node não tem seguidor, é o último da fila
    if (novo->prox == NULL) {
        fila->fim = novo;
    }

    printf("Paciente %s inserido na fila.\n", paciente.nome);
}

// Remove e retorna o primeiro paciente da fila (o de maior prioridade)
// Esta é a operação de atendimento: sempre atendemos quem tem prioridade
Paciente removerFila(Fila* fila) {
    // Define um paciente "vazio" com ID=-1 como marcador de erro
    Paciente vazio = {-1, "", 0, PRIORIDADE_INVALIDA};
    
    // Verifica se fila está vazia
    if (fila->inicio == NULL) {
        printf("ERRO: Fila vazia. Nenhum paciente para atender.\n");
        return vazio;
    }
    
    // Salva referência ao primeiro nó
    No* temp = fila->inicio;
    // Copia os dados do paciente a ser removido para um campo auxiliar
    Paciente paciente = temp->dados;

    // Atualiza o início: o primeiro passa a ser o segundo
    fila->inicio = temp->prox;

    // Se a fila ficou vazia, também atualiza o fim
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);       // Libera a memória do nó que foi removido
    return paciente;  // Retorna os dados do paciente atendido
}

// ============= FUNÇÕES DE PILHA =============
// Pilha é usada para manter histórico de atendimentos (LIFO)

// Adiciona um novo atendimento ao topo da pilha
void push(Pilha* p, Paciente paciente) {
    // Aloca memória para um novo nó no histórico
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        printf("Erro de alocação.\n");
        return;
    }

    novo->dados = paciente;      // Armazena o paciente atendido
    novo->prox = p->topo;        // Novo aponta para o antigo topo
    p->topo = novo;              // Novo se torna o topo
}

// Remove e retorna o elemento do topo da pilha
// Retorna 1 se bem-sucedido, 0 se pilha vazia
int pop(Pilha* p, Paciente* paciente) {
    // Verifica se pilha está vazia
    if (p->topo == NULL) return 0;

    // Salva o topo atual
    NoPilha* temp = p->topo;
    // Copia os dados para o ponteiro fornecido
    *paciente = temp->dados;
    // Atualiza topo para o próximo nó
    p->topo = temp->prox;

    // Libera memória do nó removido
    free(temp);
    return 1;  // Sucesso
}

// ============= FUNÇÕES DE LIMPEZA (LIBERAR MEMÓRIA) =============
// Importante: evitar vazamento de memória ao encerrar o programa

// Libera toda a memória da fila
void destruirFila(Fila* fila) {
    if (fila == NULL) return;

    // Percorre toda a fila do início até o fim
    No* atual = fila->inicio;
    while (atual != NULL) {
        No* temp = atual;      // Guarda referência ao nó atual
        atual = atual->prox;   // Avança para o próximo antes de liberar
        free(temp);            // Libera a memória do nó guardado
    }
    // Limpa os ponteiros
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Libera toda a memória da pilha (histórico)
void destruirPilha(Pilha* p) {
    if (p == NULL) return;

    // Percorre toda a pilha do topo até a base
    NoPilha* atual = p->topo;
    while (atual != NULL) {
        NoPilha* temp = atual;  // Guarda referência ao nó atual
        atual = atual->prox;    // Avança para o próximo antes de liberar
        free(temp);             // Libera a memória do nó guardado
    }
    free(p);  // Libera a estrutura da pilha em si
}

// ============= FUNÇÕES DE BUSCA =============

// Busca um paciente na fila pelo ID
// Retorna os dados do paciente se encontrado, senão retorna um paciente vazio (ID=-1)
Paciente buscarPacientePorID(Fila* fila, int id) {
    // Paciente marcador para "não encontrado"
    Paciente vazio = {-1, "", 0, PRIORIDADE_INVALIDA};

    // Percorre a fila do início até encontrar ou atingir o fim
    No* atual = fila->inicio;
    while (atual) {
        // Se encontrou o ID, retorna os dados imediatamente
        if (atual->dados.id == id)
            return atual->dados;
        atual = atual->prox;  // Avança para o próximo
    }

    // Se chegou aqui, não encontrou - retorna paciente vazio
    return vazio;
}

// Interface de busca: solicita ID ao usuário e exibe o paciente
void buscarPaciente(Fila* fila) {
    int id;
    printf("\nID do paciente: ");
    scanf("%d", &id);
    getchar();  // Limpa o \n deixado por scanf (buffer)

    // Faz a busca
    Paciente p = buscarPacientePorID(fila, id);
    // Verifica se foi encontrado (ID=-1 significa não encontrado)
    if (p.id == -1)
        printf("Paciente não encontrado.\n");
    else
        imprimirPaciente(p);  // Exibe os dados do paciente encontrado
}

// Exibe o menu principal do sistema com todas as opções disponíveis
void menu() {
    printf("\n===== SISTEMA HOSPITALAR =====\n");
    printf("1 - Inserir paciente na fila\n");
    printf("2 - Atender paciente\n");
    printf("3 - Desfazer atendimento\n");
    printf("4 - Buscar paciente por ID\n");
    printf("5 - Mostrar fila de espera\n");
    printf("6 - Mostrar histórico de atendimentos\n");
    printf("7 - Exibir relatório do sistema\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

// ============= FUNÇÕES DE ENTRADA SEGURA =============
// Estas funções tratam erros de entrada prevaimente e validam os dados

// Lê um inteiro com validação de entrada e valor mínimo
// Retorna -1 se houver erro (entrada inválida ou valor abaixo do mínimo)
int lerInteiro(int minimo) {
    int valor;
    int resultado = scanf("%d", &valor);  // Tenta ler um inteiro

    // Limpa o buffer de entrada (remove caracteres indesejados como \n)
    while (getchar() != '\n');

    // Verifica se scanf conseguiu ler um inteiro com sucesso
    if (resultado != 1) {
        printf("ERRO: Entrada inválida. Digite um número inteiro.\n");
        return -1;
    }

    // Valida o valor mínimo
    if (valor < minimo) {
        printf("ERRO: Valor deve ser >= %d.\n", minimo);
        return -1;
    }

    return valor;  // Retorna o valor lido e validado
}

// Lê uma string (nome) de forma segura, evitando buffer overflow
// fgets é mais seguro que gets porque permite limitar o tamanho
void lerString(char* buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        // Remove o \n que fgets deixa no final
        // strcspn encontra a posição de \n e a substitui por \0 (terminador)
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        // Se houve erro, deixa string vazia
        buffer[0] = '\0';
        while (getchar() != '\n');  // Limpa buffer de erro
    }
}

// Coleta dados de um novo paciente via entrada do usuário e o insere na fila
void cadastrarPaciente(Fila* fila) {
    Paciente p;  // Cria estrutura local para armazenar os dados

    printf("\n=== CADASTRO DE PACIENTE ===\n");

    // ========== LER E VALIDAR ID ==========
    printf("ID do paciente: ");
    p.id = lerInteiro(ID_MIN);
    if (p.id == -1) return;  // Se houve erro, aborta o cadastro

    // ========== LER E VALIDAR NOME ==========
    printf("Nome do paciente: ");
    lerString(p.nome, 100);
    if (strlen(p.nome) == 0) {  // Valida se nome não está vazio
        printf("ERRO: Nome não pode ser vazio.\n");
        return;
    }

    // ========== LER E VALIDAR IDADE ==========
    printf("Idade do paciente: ");
    p.idade = lerInteiro(IDADE_MIN);
    if (p.idade == -1 || !validarIdade(p.idade)) {  // Valida intervalo (1-150 anos)
        printf("ERRO: Idade deve estar entre %d e %d anos.\n", IDADE_MIN, IDADE_MAX);
        return;
    }

    // ========== LER E VALIDAR PRIORIDADE ==========
    printf("Prioridade (1-Emergência, 2-Urgência, 3-Normal): ");
    p.prioridade = lerInteiro(EMERGENCIA);
    if (p.prioridade == -1 || !validarPrioridade(p.prioridade)) {  // Valida se está entre 1-3
        printf("ERRO: Prioridade deve ser 1, 2 ou 3.\n");
        return;
    }

    // ========== INSERIR NA FILA COM PRIORIDADE ==========
    inserirFila(fila, p);  // Inser­ção respeita ordem de prioridade automática
    
    // Incrementa counter global de pacientes cadastrados
    estatisticas[0]++;
}

// Desfaz o último atendimento: remove da pilha e reinsere na fila
// Útil quando houver engano no atendimento
int desfazerAtendimento(Fila* fila, Pilha* historico) {
    // Valida se há algo para desfazer (histórico vazio)
    if (historico == NULL || historico->topo == NULL) {
        printf("Nao ha atendimentos para desfazer.\n");
        return 0;
    }

    Paciente pacienteDesfeito;

    // Remove o último atendimento da pilha (operação pop)
    if (!pop(historico, &pacienteDesfeito)) {
        return 0;
    }

    // Reinsere o paciente na fila, respeitando sua prioridade
    inserirFila(fila, pacienteDesfeito);

    printf("Atendimento de %s desfeito com sucesso.\n", pacienteDesfeito.nome);

    // Atualiza os contadores do sistema
    estatisticas[1]--;  // Decrementa contador de atendidos
    estatisticas[2]++;  // Incrementa contador de desfeitos

    return 1;  // Sucesso
}


// ============= FUNÇÃO PRINCIPAL =============

int main() {
    // Configura o locale para português (permite acentuação nos caracteres)
	setlocale(LC_ALL, "pt_BR.UTF-8");

    // ========== INICIALIZAÇÃO DO SISTEMA ==========
    // Cria a fila de espera de pacientes
    Fila fila;
    inicializaFila(&fila);

    // Cria a pilha para manter histórico de atendimentos
    Pilha* pilha = inicializaPilha();
    // Verifica se a pilha foi criada com sucesso
    if (pilha == NULL) {
        printf("ERRO: Falha ao inicializar a pilha de histórico.\n");
        return 1;  // Encerra com código de erro
    }

    int op;  // Variável para armazenar a opção do menu escolhida

    // Exibe mensagem de boas-vindas
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║     BEM-VINDO AO SISTEMA HOSPITALAR    ║\n");
    printf("╚════════════════════════════════════════╝\n");

    // ========== LOOP PRINCIPAL ==========
    // Executa enquanto o usuário não escolher sair (op != 0)
    do {
        menu();  // Exibe as opções disponíveis
        op = lerInteiro(0);  // Lê e valida a escolha do usuário
        if (op == -1) {
            printf("Digite uma opção válida (0-7).\n");
            continue;  // Volta ao inicío do loop se entrada foi inválida
        }

        // Processa a opção escolhida
        switch (op) {
            // ========== CASO 1: INSERIR PACIENTE ==========
            case 1:
				limparTela();
                cadastrarPaciente(&fila);  // Abre interface de cadastro
                break;

            // ========== CASO 2: ATENDER PACIENTE ==========
            case 2: {
				limparTela();
                // Remove o primeiro paciente (maior prioridade) da fila
                Paciente atendido = removerFila(&fila);
                // Verifica se conseguiu remover (ID != -1 significa sucesso)
                if (atendido.id != -1) {
                    // Adiciona ao histórico (pilha) para permitir desfazer
                    push(pilha, atendido);
                    printf("\n✓ PACIENTE ATENDIDO:\n");
                    imprimirPaciente(atendido);
                    
                    // Incrementa contador global de atendidos
                    estatisticas[1]++;
                }
                break;
            }
            // ========== CASO 3: DESFAZER ATENDIMENTO ==========
            case 3:
				limparTela();
				desfazerAtendimento(&fila, pilha);  // Remove do histórico e reinsere na fila
				break;

            // ========== CASO 4: BUSCAR PACIENTE ==========
            case 4:
                limparTela();
                buscarPaciente(&fila);  // Solicita ID e exibe dados
                break;

            // ========== CASO 5: VISUALIZAR FILA ==========
            case 5:
				limparTela();
                imprimirFila(&fila);  // Exibe todos em espera, ordenados por prioridade
                break;

            // ========== CASO 6: VISUALIZAR HISTÓRICO ==========
            case 6:
				limparTela();
                imprimirPilha(pilha);  // Exibe últimos atendimentos
                break;

            // ========== CASO 7: EXIBIR RELATÓRIO ==========
            case 7:
                limparTela();
                exibirRelatorio();  // Mostra estatísticas do sistema
                break;

            // ========== CASO 0: SAIR ==========
            case 0:
                printf("\nEncerrando sistema...\n");
                printf("Limpando memória...\n");
                // Libera TODA a memória alocada dinamicamente
                destruirFila(&fila);    // Libera fila
                destruirPilha(pilha);   // Libera pilha
                printf("Sistema encerrado com sucesso.\n\n");
                break;

            // ========== OPÇÃO INVÁLIDA ==========
            default:
                printf("ERRO: Opção inválida. Escolha entre 0 e 7.\n");
        }

    } while (op != 0);  // Continua até usuário escolher sair

    return 0;  // Encerra o programa
}