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
- Exibir o histórico de atendimentos
- Encerrar o sistema liberando a memória alocada

---

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
gcc sistema_hospitalar.c -o sistema_hospitalar

sistema_hospitalar.exe (windows)
./sistema_hospitalar (linux)
