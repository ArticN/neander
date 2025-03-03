#include "Assembler.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Verifica se a linha está vazia
bool linha_vazia(char *linha) {
    while (*linha) {
        if (!isspace((unsigned char)*linha)) {
            return false;
        }
        linha++;
    }
    return true;
}

// Verifica se o mnemônico é válido
bool mneumon_valido(char *mnemonico) {
    char *mnemonicos_permitidos[] = {"STA", "LDA", "ADD", "OR", "AND", "NOT", "JMP", "JN", "JZ", "HLT", "NOP"};
    for (int i = 0; i < sizeof(mnemonicos_permitidos) / sizeof(mnemonicos_permitidos[0]); i++) {
        if (strcmp(mnemonico, mnemonicos_permitidos[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Verifica se a linha contém o comando "END"
bool final_bloco(char *linha) {
    char linha_copia[100];
    strncpy(linha_copia, linha, sizeof(linha_copia));
    char *token = strtok(linha_copia, " \t\n\r");
    while (token != NULL) {
        if (strcmp(token, "END") == 0) {
            return true;
        }
        token = strtok(NULL, " \t\n\r");
    }
    return false;
}

// Escreve uma instrução simples na memória
void instrucao_simples(char *mnemonico, uint8_t *memoria) {
    char *mnemonicos_simples[] = {"NOP", "NOT", "HLT"};
    uint8_t codigos[] = {0x00, 0x60, 0xF0};

    for (int i = 0; i < sizeof(mnemonicos_simples) / sizeof(mnemonicos_simples[0]); i++) {
        if (strcmp(mnemonico, mnemonicos_simples[i]) == 0) {
            *memoria = codigos[i];
            printf("Instrução simples: %s -> %#02x\n", mnemonico, codigos[i]);
            return;
        }
    }
}

// Escreve uma instrução composta na memória
void instrucao_composta(char *mnemonico, uint8_t valor, uint8_t *memoria_codigo, uint8_t *memoria_valor) {
    char *mnemonicos_compostos[] = {"STA", "LDA", "ADD", "OR", "AND", "JMP", "JN", "JZ"};
    uint8_t codigos[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x80, 0x90, 0xA0};

    for (int i = 0; i < sizeof(mnemonicos_compostos) / sizeof(mnemonicos_compostos[0]); i++) {
        if (strcmp(mnemonico, mnemonicos_compostos[i]) == 0) {
            *memoria_codigo = codigos[i];
            *memoria_valor = valor;
            printf("Instrução composta: %s %d -> %#02x %#02x\n", mnemonico, valor, codigos[i], valor);
            return;
        }
    }
}

// Escreve a memória em um arquivo binário
void escrever(uint8_t *memoria) {
    FILE *arquivo = fopen("../Mems/memoria_gerada.mem", "wb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    fwrite(memoria, sizeof(uint8_t), 516, arquivo);
    fclose(arquivo);
    printf("Memória salva no arquivo.");
}


void processar_bloco_dados(FILE *arquivo, uint8_t *memoria) {
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (final_bloco(linha)) {
            printf("Fim do bloco de dados.\n");
            break;
        }

        int posicao, valor;
        if (sscanf(linha, "%d %d", &posicao, &valor) == 2) {
            if (posicao >= 0 && posicao < 516 && valor >= 0 && valor <= 255) {
                memoria[posicao] = (uint8_t)valor;
                printf("Variável armazenada: posição %d = %d\n", posicao, valor);
            } else {
                printf("Erro: Posição ou valor inválido.\n");
            }
        }
    }
}

void processar_bloco_codigo(FILE *arquivo, uint8_t *memoria, int *posicao_memoria) {
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (final_bloco(linha)) {
            printf("Fim do bloco de código.\n");
            break;
        }

        char mnemonico[10];
        int valor = 0;
        if (sscanf(linha, "%s %d", mnemonico, &valor) >= 1) {
            if (mneumon_valido(mnemonico)) {
                if (valor == 0) {
                    instrucao_simples(mnemonico, &memoria[*posicao_memoria]);
                    (*posicao_memoria)++;
                } else {
                    instrucao_composta(mnemonico, (uint8_t)valor, &memoria[*posicao_memoria], &memoria[*posicao_memoria + 1]);
                    (*posicao_memoria) += 2;
                }
            } else {
                printf("Erro: Mnemônico inválido.\n");
            }
        }
    }
}


int executar(void) {
    FILE *arquivo = fopen("Txt/Assemblyzinho.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo assembly.txt.\n");
        return 1;
    }

    uint8_t memoria[516] = {0}; // Memória de 516 posições
    int posicao_memoria = 0;    // Posição atual na memória
    char linha[100];            // Buffer para ler cada linha do arquivo

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("Linha lida: %s", linha);

        if (linha_vazia(linha) || linha[0] == '/') {
            printf("Ignorando linha vazia ou comentário.\n");
            continue;
        }

        linha[strcspn(linha, "\n")] = '\0';

        if (final_bloco(linha)) {
            printf("Fim do bloco encontrado.\n");
            continue;
        }

        char *tokens[10];
        int num_tokens = 0;
        char *token = strtok(linha, " \t");
        while (token != NULL && num_tokens < 10) {
            tokens[num_tokens++] = token;
            token = strtok(NULL, " \t");
        }

        if (num_tokens == 0) {
            continue;
        }

        if (strcmp(tokens[0], "DATA") == 0) {
            printf("Início do bloco de dados.\n");
            processar_bloco_dados(arquivo, memoria);
        } else if (strcmp(tokens[0], "CODE") == 0) {
            printf("Início do bloco de código.\n");
            processar_bloco_codigo(arquivo, memoria, &posicao_memoria);
        }
    }

    fclose(arquivo);

    // Exibe a memória em blocos de 16 bytes
    printf("Estado final da memória:\n");
    for (int i = 0; i < 516; i++) {
        if (i % 16 == 0) {
            printf("\n%03X: ", i);
        }
        printf("%02X ", memoria[i]);
    }
    printf("\n");

    escrever(memoria);

    return 0;
}


int main(int argc, char *argv[]) {
    return executar();
}