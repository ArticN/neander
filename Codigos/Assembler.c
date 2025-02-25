#include "Assembler.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool linha_vazia(char *line) {
    if (line == '\n' || *line == '\0') {
        return true;
    }
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return false;
        }
        line++;
    }
    return true;
}

bool mneumon_valido(char *mneumon){
    char *cmds_allowed[] = {"STA", "LDA", "ADD", "OR", "AND","NOT", "JMP", "JN",  "JZ",  "HLT", "NOP"};

    for(int i = 1; i <= 11; i++){
        if(strcmp(mneumon, cmds_allowed[i]) == 0){
            return true;
        }
    }
    return false;
}

bool final_bloco(char *line){
char *token = strtok(line, " \t\n\r");

while (token != NULL && strcmp(token, " ") == 0) {
    token = strtok(NULL, " \t\n\r");
}

// Verifica se o token é "END"
return strcmp(token, "END");
}

void instrucao_simples(char *mneumon, uint8_t *memory_posit);
void instrucao_composta(char *mneumon, uint8_t value, uint8_t *mneumon_mem_posit, uint8_t *value_mem_posit);
void escrever(uint8_t mem[256]);

int buscar(char *line, char *w[10]);
int executar(void);
