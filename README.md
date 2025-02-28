---

# Neander Assembler and Executor

Este repositório tem como objetivo explicar diferentes códigos que, em conjunto, representam o funcionamento do Neander, um modelo didático de processador. O Neander é utilizado para fins educacionais, ajudando a entender os conceitos básicos de arquitetura de computadores e montagem.

## Arquivos

### assembler.c

Este arquivo contém o código de um montador (assembler) que lê um arquivo de texto contendo instruções de montagem e dados, processa essas instruções e dados, e escreve o resultado em um arquivo binário de memória.

#### Ideia Central

- **Leitura do Arquivo:** O montador lê um arquivo de texto (`Txt/Assemblyzinho.txt`) linha por linha.
- **Processamento de Dados:** As linhas são analisadas para identificar blocos de dados e código.
- **Instruções:** As instruções são convertidas em códigos de máquina e armazenadas na memória.
- **Escrita na Memória:** A memória resultante é escrita em um arquivo binário (`../Mems/memoria_gerada.mem`).
- **Exibição da Memória:** A memória é exibida no terminal em blocos de 16 bytes.

### executor.c

Este arquivo contém o código de um executor que simula a execução das instruções armazenadas na memória.

#### Ideia Central

- **Leitura do Arquivo de Memória:** O executor lê um arquivo binário de memória (`../Arquivos/SomaAssembly.mem`).
- **Simulação de Execução:** As instruções são executadas uma a uma, modificando o acumulador (AC) e o contador de programa (PC).
- **Instruções Suportadas:** O executor suporta várias instruções, como `STA`, `LDA`, `ADD`, `OR`, `AND`, `NOT`, `JMP`, `JN`, `JZ`, e `HLT`.
- **Exibição da Memória:** A memória é exibida no terminal após a execução, mostrando o estado final do acumulador e do contador de programa.

#### Funções Principais

- **print_memory:** Exibe a memória em blocos de 16 bytes, mostrando o estado do acumulador (AC) e do contador de programa (PC).
- **flagZero:** Verifica se o acumulador é zero.
- **flagNeg:** Verifica se o acumulador é negativo.
- **main:** Função principal que lê o arquivo de memória, executa as instruções e exibe a memória final.

---
