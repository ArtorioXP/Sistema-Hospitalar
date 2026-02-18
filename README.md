# Sistema-Hospitalar
# Sistema de Atendimento Hospitalar – Modelagem de Dados

## 👥 Integrantes do Grupo

- **JOSEPH ANTONY DOS SANTOS LEITE**  
- **JOSÉ ARTHUR CALIXTO DA ROCHA COSTA**  
- **THEOFILO PINTO DE CARVALHO SOARES ARAUJO**  
- **MARIANA DE JESUS SILVA**

---

## 📌 Descrição Geral

Este projeto consiste no desenvolvimento de um **Sistema de Atendimento Hospitalar**, implementado em linguagem **C**, com o objetivo de aplicar e consolidar conhecimentos em **Estruturas de Dados**, **ponteiros**, **alocação dinâmica de memória** e **controle de fluxo por menu interativo**.

O sistema simula o funcionamento básico de um hospital, permitindo o cadastro de pacientes, o gerenciamento da fila de espera, a realização de atendimentos, o controle de histórico e a busca por pacientes.

---

## 🎯 Objetivos do Projeto

- Aplicar conceitos fundamentais de **Estruturas de Dados**
- Utilizar **listas encadeadas, filas e pilhas**
- Trabalhar com **ponteiros e alocação dinâmica** em C
- Implementar um **menu interativo com switch-case**
- Garantir **organização lógica e liberação correta da memória**
- Simular um sistema real de atendimento hospitalar

---

## 🧠 Justificativa das Estruturas e Técnicas Utilizadas

### 🔗 Lista Encadeada

A **lista encadeada** foi utilizada para representar a **fila de espera dos pacientes**, pois permite **crescimento dinâmico**, sem necessidade de tamanho pré-definido.

Vantagens:
- Inserções e remoções eficientes
- Uso ideal para dados que variam de quantidade
- Adequada para sistemas reais como hospitais

Cada paciente é armazenado em um nó alocado dinamicamente.

---

### ⏳ Fila

A **fila** modela corretamente o **fluxo de atendimento hospitalar**, respeitando a ordem de chegada (**FIFO**).

Características:
- O primeiro paciente da fila é o primeiro a ser atendido
- Uso de ponteiros para início e fim
- Remoção sempre no início da fila

Essa estrutura reflete fielmente o funcionamento de atendimentos reais.

---

### 📚 Pilha

A **pilha** é utilizada para armazenar o **histórico de atendimentos**, sendo adequada para operações do tipo **LIFO (Last In, First Out)**.

Permite:
- Registrar cada atendimento realizado
- Desfazer o último atendimento
- Acesso rápido ao atendimento mais recente

---

### 🧭 Ponteiros

Os **ponteiros** são essenciais para:
- Ligar os nós das estruturas dinâmicas
- Passar estruturas para funções
- Manipular diretamente a memória

O projeto reforça conceitos fundamentais como **endereçamento**, **acesso indireto** e **estruturação dinâmica**.

---

### 🧩 Alocação Dinâmica de Memória

A alocação dinâmica, feita com `malloc` e `free`, garante:
- Uso eficiente da memória
- Estruturas flexíveis
- Evita desperdício de espaço

Todo nó alocado é corretamente liberado, prevenindo **vazamentos de memória**.

---

### 📊 Array (Relatórios e Estatísticas)

O **array** é utilizado de forma **estática**, exclusivamente para **controle estatístico**, como por exemplo:
- Quantidade de pacientes atendidos
- Total de atendimentos realizados
- Relatórios simples do sistema

👉 O array **não é usado para armazenar pacientes**, pois isso não faria sentido em um sistema dinâmico como este.

---

## ⚙️ Funcionalidades do Sistema

O sistema oferece um menu interativo com as seguintes opções:

- Inserir paciente na fila de espera
- Atender paciente
- Desfazer o último atendimento
- Exibir fila de espera
- Buscar paciente por ID
- Exibir histórico de atendimentos
- Exibir relatório do sistema
- Encerrar o sistema liberando a memória

---

## 🧩 Explicação das Funções do Sistema

### 🔧 Funções de Inicialização

#### `void inicializaFila(Fila* fila)`
Inicializa a fila definindo `inicio` e `fim` como `NULL`.

---

#### `Pilha* inicializaPilha()`
Aloca dinamicamente a pilha e inicializa o topo como `NULL`.

---

### 👤 Funções de Impressão

#### `void imprimirPaciente(Paciente p)`
Imprime todas as informações de um paciente.

---

#### `void imprimirFila(Fila* fila)`
Percorre a fila do início ao fim e exibe os pacientes.

---

#### `void imprimirPilha(Pilha* p)`
Exibe o histórico de atendimentos seguindo a ordem **LIFO**.

---

### ⏳ Funções da Fila

#### `void inserirFila(Fila* fila, Paciente paciente)`
Insere um paciente no final da fila.

Complexidade: **O(1)**

---

#### `Paciente removerFila(Fila* fila)`
Remove o paciente do início da fila (atendimento).

- Atualiza os ponteiros
- Libera a memória do nó removido

---

### 📚 Funções da Pilha

#### `void push(Pilha* p, Paciente paciente)`
Registra um atendimento no topo da pilha.

---

#### `int pop(Pilha* p, Paciente* paciente)`
Remove o último atendimento realizado.

Retorna:
- `1` → sucesso  
- `0` → pilha vazia  

---

### 🔍 Função de Busca

#### `Paciente* buscarPaciente(Fila* fila, int id)`
Busca um paciente na fila pelo **ID**.

- Retorna o ponteiro do paciente se encontrado
- Retorna `NULL` caso não exista

Complexidade: **O(n)**

---

### 🎛️ Função Principal

#### `int main()`
Responsável por:
- Inicializar estruturas
- Controlar o menu com `switch-case`
- Chamar as funções do sistema
- Encerrar o programa corretamente

---

## 🧪 Regras de Atendimento

- Atendimento segue **FIFO**
- Primeiro a chegar é o primeiro a ser atendido
- Histórico segue **LIFO**
- Busca feita por **ID único**

---

## 🖥️ Compilação e Execução

### Compilação
```bash
gcc SistemaHospitalar.c -o SistemaHospitalar

SistemaHospitalar.exe (windows)

./SistemaHospitalar (linux/mac)

