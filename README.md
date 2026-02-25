# 🪙 Simulador de Exchange de Criptomoedas

Este projeto é um simulador de uma corretora (exchange) de criptomoedas baseado em linha de comandos (CLI), desenvolvido inteiramente em **C**. 

O projeto foi construído como **Trabalho Final** da disciplina de Desenvolvimento de Algoritmos no curso de Ciência da Computação na **FEI**, com o objetivo de aplicar conceitos sólidos de manipulação de memória, modularização de código, e leitura/escrita de ficheiros para persistência de dados.

## 🎯 O que o projeto faz?

O sistema simula o ecossistema completo de uma corretora, dividindo a aplicação em dois grandes módulos que partilham a mesma "base de dados" (ficheiros de texto):

### 1. Módulo do Administrador (`ProgramaAdm`)
- Cadastro e remoção de utilizadores (investidores).
- Consulta de saldo e extrato de qualquer investidor registado na plataforma.
- Sistema de login seguro exclusivo para administradores.

### 2. Módulo do Utilizador (`ProgramaUser`)
- **Carteira Fiat:** Depósito e levantamento de saldo em Reais (BRL).
- **Trading:** Compra e venda de criptomoedas (Bitcoin, Ethereum, Ripple) baseadas na cotação atual.
- **Histórico:** Consulta de saldo atualizado das carteiras e extrato completo de operações.
- Sistema de autenticação por palavra-passe e validação de fundos antes de qualquer operação.

## 🛠️ Tecnologias e Arquitetura

- **Linguagem:** C (Standard C Library)
- **Persistência de Dados:** File I/O (Manipulação de ficheiros `.txt` para armazenamento contínuo de utilizadores, cotações e histórico de extratos).
- **Arquitetura Modular:** O código foi dividido em `ProgramaAdm`, `ProgramaUser` e uma pasta `shared` (com funções e dados partilhados por ambos), evitando duplicação de código e facilitando a manutenção.

## 📁 Estrutura do Projeto

O repositório está organizado da seguinte forma:

```text
📦 Projeto4C
 ┣ 📂 ProgramaAdm         # Aplicação restrita aos administradores
 ┃ ┣ 📂 funcoesAdm        # Lógica de negócio do administrador
 ┃ ┗ 📜 mainADM.c         # Ponto de entrada do Admin
 ┣ 📂 ProgramaUser        # Aplicação dos investidores
 ┃ ┣ 📂 FuncoesUSER       # Lógica de negócio do utilizador (depósito, compra, venda)
 ┃ ┗ 📜 mainUSER.c        # Ponto de entrada do Utilizador
 ┗ 📂 shared              # Recursos partilhados
   ┣ 📂 FuncoesCompartilhadas # Funções auxiliares (extratos, cotações)
   ┗ 📜 cotacoes.txt, extrato.txt, informacoesUsu.txt # Ficheiros de Base de Dados
```
## 🚀 Como executar o projeto localmente

Pré-requisitos: Ter um compilador C instalado (como o `gcc` via MinGW no Windows ou build-essential no Linux).

1. Clone o repositório:
```bash
git clone [https://github.com/EnricoNSilva/Projeto4C.git](https://github.com/EnricoNSilva/Projeto4C.git)
```

2. Navegue até a pasta do programa que deseja executar (Admin ou User):
```bash
cd Projeto4C/Projeto4C-main/ProgramaAdm
# ou
cd Projeto4C/Projeto4C-main/ProgramaUser
```

3. Compile o código:
```bash
gcc mainADM.c funcoesAdm/*.c ../shared/FuncoesCompartilhadas/*.c -o admin_app
```

4. Execute o programa:
```bash
./admin_app
```

---
*Este projeto marca um passo importante na compreensão de estruturas de dados e desenvolvimento de software durante a minha jornada acadêmica na FEI.*
