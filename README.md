# Sistema-Hospitalar
# Sistema de Atendimento Hospitalar – Modelagem de Dados

## 👥 Integrantes do Grupo

- JOSEPH ANTONY DOS SANTOS LEITE  
- JOSÉ ARTHUR CALIXTO DA ROCHA COSTA  
- THEOFILO PINTO DE CARVALHO SOARES ARAUJO  
- MARIANA DE JESUS SILVA  

---

## 📌 Descrição Geral

Este projeto faz parte do desenvolvimento de um **Sistema de Atendimento Hospitalar**, implementado em linguagem **C**, com o objetivo de demonstrar domínio em **modelagem de dados**, **uso de ponteiros**, **alocação dinâmica de memória** e **implementação manual de estruturas de dados clássicas**.

O sistema simula o funcionamento de um ambiente hospitalar, permitindo o cadastro de pacientes, organização da fila de espera por prioridade, realização de atendimentos e manutenção de um histórico que possibilita desfazer o último atendimento realizado.

---

## 🎯 Objetivos do Projeto

- Aplicar conceitos fundamentais de **Estruturas de Dados**
- Utilizar **listas encadeadas, filas e pilhas** de forma integrada
- Trabalhar com **ponteiros e memória dinâmica** em C
- Desenvolver um sistema funcional com **menu interativo**
- Garantir **organização lógica e liberação correta da memória**

---

## 🧠 Justificativa das Estruturas e Técnicas Utilizadas

### 🔗 Lista Encadeada

A lista encadeada foi utilizada para representar a **fila de espera dos pacientes**, pois permite o **crescimento dinâmico da estrutura**, sem a necessidade de definir previamente um tamanho máximo.

Cada paciente é armazenado em um nó alocado dinamicamente, possibilitando inserções e remoções eficientes, o que é essencial em um ambiente hospitalar, onde a quantidade de pacientes varia constantemente.

---

### ⏳ Fila

A estrutura de fila modela corretamente o **fluxo de atendimento hospitalar**, respeitando a ordem de chegada dos pacientes, associada ao critério de prioridade.

Características principais:
- Atendimento baseado em **prioridade** (Emergência, Urgência e Normal)
- Manutenção da ordem de chegada para pacientes com a mesma prioridade
- Operações eficientes utilizando ponteiros para o início e o fim da fila

Essa abordagem reflete fielmente o funcionamento real de sistemas de atendimento hospitalar.

---

### 📚 Pilha

A pilha é utilizada para armazenar o **histórico de atendimentos realizados**, sendo adequada para operações do tipo **LIFO (Last In, First Out)**.

Essa estrutura permite:
- Registrar cada atendimento realizado
- Desfazer o último atendimento
- Consultar rapidamente o atendimento mais recente  

A escolha da pilha é justificada pela necessidade de controle e reversão de operações recentes no sistema.

---

### 🧭 Ponteiros

O uso de ponteiros é essencial para a manipulação das estruturas dinâmicas do sistema. Eles permitem:

- A ligação entre os nós da lista encadeada e da pilha
- A passagem eficiente de estruturas para funções
- O controle direto sobre a memória alocada  

O projeto faz uso intensivo de ponteiros, reforçando conceitos fundamentais de **endereçamento, acesso indireto e manipulação de memória** em linguagem C.

---

### 🧩 Alocação Dinâmica de Memória

A alocação dinâmica de memória, realizada por meio das funções `malloc` e `free`, garante um **uso eficiente da memória**, alocando espaço apenas quando necessário e liberando-o corretamente ao final do uso.

Essa abordagem:
- Evita desperdício de memória
- Permite estruturas flexíveis
- É indispensável em aplicações com dados de tamanho variável  

O projeto também se preocupa com a **liberação completa da memória**, prevenindo vazamentos.

---

## ⚙️ Funcionalidades do Sistema

O sistema oferece um menu interativo com as seguintes opções:

- Inserir paciente na fila de espera
- Atender paciente conforme prioridade
- Desfazer o último atendimento
- Exibir a fila de espera
- Buscar paciente por ID na fila
- Exibir o histórico de atendimentos
- Encerrar o sistema liberando a memória alocada

---
## 🧩 Explicação das Funções do Sistema

Esta seção descreve detalhadamente todas as funções implementadas no sistema, explicando sua finalidade e funcionamento.

---

### 🔧 Funções de Inicialização

#### `void inicializaFila(Fila* fila)`
Inicializa a fila de espera, definindo os ponteiros `inicio` e `fim` como `NULL`.  
Essa função deve ser chamada antes de qualquer operação na fila, garantindo que ela comece vazia.

---

#### `Pilha* inicializaPilha()`
Aloca dinamicamente a estrutura da pilha de atendimentos e inicializa o ponteiro `topo` como `NULL`.  
Retorna um ponteiro para a pilha criada ou `NULL` em caso de erro de alocação.

---

### 👤 Funções de Impressão

#### `void imprimirPaciente(Paciente p)`
Exibe no terminal todas as informações de um paciente:
- ID
- Nome
- Idade
- Prioridade  

Essa função é utilizada tanto na impressão da fila quanto da pilha.

---

#### `void imprimirFila(Fila* fila)`
Percorre a fila de espera do início ao fim, imprimindo os dados de todos os pacientes cadastrados.  
Caso a fila esteja vazia, informa o usuário.

---

#### `void imprimirPilha(Pilha* p)`
Exibe o histórico de atendimentos armazenado na pilha, seguindo a ordem **LIFO** (do mais recente para o mais antigo).  
Caso a pilha esteja vazia, informa o usuário.

---

### ⏳ Funções de Manipulação da Fila

#### `void inserirFila(Fila* fila, Paciente paciente)`
Insere um novo paciente no final da fila de espera.

Funcionamento:
- Aloca dinamicamente um novo nó
- Copia os dados do paciente para o nó
- Atualiza corretamente os ponteiros `inicio` e `fim`

Essa operação possui complexidade **O(1)**.

---

#### `Paciente removerFila(Fila* fila)`
Remove o paciente do início da fila, simulando o atendimento.

Funcionamento:
- Verifica se a fila está vazia
- Remove o primeiro nó
- Atualiza o ponteiro `inicio`
- Ajusta o ponteiro `fim` caso a fila fique vazia
- Libera a memória do nó removido

Retorna os dados do paciente atendido ou um paciente inválido caso a fila esteja vazia.

---

### 📚 Funções de Manipulação da Pilha

#### `void push(Pilha* p, Paciente paciente)`
Insere um paciente no topo da pilha de histórico de atendimentos.

Essa função é utilizada logo após um paciente ser atendido, registrando o atendimento realizado.

---

#### `int pop(Pilha* p, Paciente* paciente)`
Remove o paciente do topo da pilha, permitindo desfazer o último atendimento realizado.

Funcionamento:
- Verifica se a pilha está vazia
- Remove o nó do topo
- Copia os dados para a variável recebida por referência
- Libera a memória do nó removido

Retorna:
- `1` se a operação foi bem-sucedida
- `0` se a pilha estiver vazia

---

### 🔍 Função de Busca

#### `Paciente* buscarPaciente(Fila* fila, int id)`
Realiza a busca de um paciente na fila de espera com base no **ID**.

Funcionamento:
- Percorre a lista encadeada sequencialmente
- Compara o ID informado com o ID de cada paciente
- Retorna um ponteiro para o paciente caso seja encontrado
- Retorna `NULL` caso o paciente não exista na fila

A busca possui complexidade **O(n)**, adequada para listas encadeadas.

---

### 🎛️ Função Principal

#### `int main()`
Responsável por:
- Inicializar as estruturas do sistema
- Exibir o menu interativo
- Controlar o fluxo de execução do programa
- Chamar as funções de acordo com a opção escolhida pelo usuário
- Encerrar o sistema liberando corretamente toda a memória alocada

---

Essa organização modular das funções facilita a manutenção, leitura e expansão futura do sistema.

## 🧪 Regras de Atendimento

- Prioridades:
  - **1** – Emergência  
  - **2** – Urgência  
  - **3** – Normal  

- Pacientes com maior prioridade são atendidos primeiro
- Em caso de empate na prioridade, mantém-se a ordem de chegada
- O histórico de atendimentos segue a lógica **LIFO**

---

## 🖥️ Compilação e Execução

### Compilação
```bash
gcc SistemaHospitalar.c.c -o SistemaHospitalar.c

SistemaHospitalar.exe (windows)
./SistemaHospitalar (linux)
