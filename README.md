# Sistema-Hospitalar
# Sistema de Atendimento Hospitalar – Modelagem de Dados

Este projeto faz parte do desenvolvimento de um **Sistema de Atendimento Hospitalar**, implementado em linguagem **C**, com o objetivo de demonstrar domínio em **modelagem de dados**, **uso de ponteiros**, **alocação dinâmica de memória** e **implementação manual de estruturas de dados clássicas**.

## 🧠 Justificativa das Estruturas e Técnicas Utilizadas

### 🔗 Lista Encadeada
A lista encadeada foi utilizada para representar a fila de espera dos pacientes, pois permite o **crescimento dinâmico da estrutura**, sem a necessidade de definir previamente um tamanho máximo. Cada paciente é armazenado em um nó alocado dinamicamente, possibilitando inserções e remoções eficientes e adequadas a um ambiente hospitalar, onde a quantidade de pacientes pode variar constantemente.

---

### ⏳ Fila
A estrutura de fila modela corretamente o **fluxo de atendimento hospitalar**, respeitando a ordem de chegada dos pacientes. Essa abordagem reflete o funcionamento real de sistemas de atendimento, garantindo que os pacientes sejam atendidos de forma organizada e previsível. A utilização de ponteiros para o início e o fim da fila permite operações de inserção e remoção em tempo constante (O(1)).

---

### 📚 Pilha
A pilha é utilizada para armazenar o **histórico de atendimentos realizados**, sendo adequada para operações do tipo *LIFO* (Last In, First Out). Essa característica permite implementar funcionalidades como:
- Desfazer o último atendimento realizado
- Consultar o atendimento mais recente  
Essa estrutura é especialmente útil para controle e auditoria das operações do sistema.

---

### 🧭 Ponteiros
O uso de ponteiros é essencial para a manipulação das estruturas dinâmicas do sistema. Eles permitem:
- A ligação entre os nós da lista encadeada e da pilha
- A passagem eficiente de estruturas para funções
- O controle direto da memória alocada  
O projeto explora intensivamente ponteiros, reforçando o entendimento de endereçamento e acesso indireto em linguagem C.

---

### 🧩 Alocação Dinâmica de Memória
A alocação dinâmica de memória, realizada por meio das funções `malloc` e `free`, garante um **uso eficiente da memória**, alocando espaço apenas quando necessário e liberando-o após o uso. Essa abordagem evita desperdícios, permite flexibilidade no tamanho das estruturas e é fundamental para aplicações que lidam com dados de quantidade variável, como um sistema de atendimento hospitalar.

---

Essas escolhas de estruturas e técnicas foram feitas visando alinhar o projeto com boas práticas de programação em C, além de atender aos requisitos acadêmicos de manipulação manual de memória e estruturas de dados clássicas.
