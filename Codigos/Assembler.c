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

    for(int i = 0; i < 11; i++){
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

void instrucao_simples(char *mneumon, uint8_t *memory_posit){
    char *simple_mneumon[] = {"NOP", "NOT", "HLT"};
    uint8_t codes[] = {0x00,0x60,0xF0};

    for (int i = 0; i < 4; i++){
        
        if(strcmp(mneumon, simple_mneumon[i] == 0) ) {
            *memory_posit = codes[i];
            printf("Mneumonico %s // Codigo %#x ==> Armazenado na memoria", mneumon, codes[i]);
            return;
        }
    }
}
void instrucao_composta (char *mneumon, uint8_t value, 
                        uint8_t *mneumon_mem_posit, 
                        uint8_t *value_mem_posit){
    char *compst_mneumon[] = {"STA", "LDA", "ADD", "OR", "AND", "JMP", "JN", "JZ"};
    uint8_t codes[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x80, 0x90, 0xA0};

    for(int i = 0; i < 8; i++){
        if (strcmp(mneumon, compst_mneumon[i]) == 0) {
            *mneumon_mem_posit = codes[i];
            *value_mem_posit = value;
            printf("Mneumonico %s // Codigo %#x // Valor ==> %#x Armazenado na memoria", mneumon, codes[i] ,value);
            return;
          }
    }
}

