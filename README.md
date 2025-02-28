# neander

---

# Assembler

Este projeto é um simples montador (assembler) que lê um arquivo de texto contendo instruções de montagem e dados, processa essas instruções e dados, e escreve o resultado em um arquivo binário de memória. O código está escrito em C.

## Estrutura do Código

### Funções

1. **linha_vazia**
   - Verifica se uma linha está vazia ou contém apenas espaços em branco.
   - **Parâmetro:** `char *linha` - a linha a ser verificada.
   - **Retorno:** `bool` - `true` se a linha estiver vazia, `false` caso contrário.

2. **mneumon_valido**
   - Verifica se um mnemônico é válido.
   - **Parâmetro:** `char *mnemonico` - o mnemônico a ser verificado.
   - **Retorno:** `bool` - `true` se o mnemônico for válido, `false` caso contrário.

3. **final_bloco**
   - Verifica se uma linha contém o comando "END", indicando o fim de um bloco.
   - **Parâmetro:** `char *linha` - a linha a ser verificada.
   - **Retorno:** `bool` - `true` se a linha contém "END", `false` caso contrário.

4. **instrucao_simples**
   - Escreve uma instrução simples na memória.
   - **Parâmetros:**
     - `char *mnemonico` - o mnemônico da instrução.
     - `uint8_t *memoria` - o endereço na memória onde a instrução será escrita.

5. **instrucao_composta**
   - Escreve uma instrução composta na memória.
   - **Parâmetros:**
     - `char *mnemonico` - o mnemônico da instrução.
     - `uint8_t valor` - o valor associado à instrução.
     - `uint8_t *memoria_codigo` - o endereço na memória onde o código da instrução será escrito.
     - `uint8_t *memoria_valor` - o endereço na memória onde o valor será escrito.

6. **escrever**
   - Escreve a memória em um arquivo binário.
   - **Parâmetro:** `uint8_t *memoria` - a memória a ser escrita no arquivo.

7. **processar_bloco_dados**
   - Processa o bloco de dados do arquivo de entrada.
   - **Parâmetros:**
     - `FILE *arquivo` - o arquivo de entrada.
     - `uint8_t *memoria` - a memória onde os dados serão armazenados.

8. **processar_bloco_codigo**
   - Processa o bloco de código do arquivo de entrada.
   - **Parâmetros:**
     - `FILE *arquivo` - o arquivo de entrada.
     - `uint8_t *memoria` - a memória onde as instruções serão armazenadas.
     - `int *posicao_memoria` - a posição atual na memória.

9. **executar**
   - Função principal do assembler. Lê o arquivo de entrada, processa os blocos de dados e código, e escreve a memória resultante em um arquivo binário.

10. **main**
    - Função principal do programa. Chama a função `executar`.


