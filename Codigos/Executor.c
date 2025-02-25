#include "Executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
//
// colocado para servir de modelo até escrever um próprio
//
void print_memory(uint8_t *bytes, int size, uint8_t ac, uint8_t pc) {
  size_t offset = 0;

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  printf("AC: %d \nPC: %d\n", ac, pc);

  while (offset < size) {
    printf("%08zx: ", offset);

    for (size_t i = 0; i < 16; i++) {
      if (offset + i < size)
        printf("%02x ", bytes[offset + i]);
      else
        printf("   ");
    }

    printf("\n");
    offset += 16;
  }

  offset += 16;
}

bool flagZero(const int AC) {
    return AC == 0x00;
}

bool flagNeg(const int AC) {
    return AC & 0x80;
}

int main(void)
{
    int AC = 0;
    int PC = 0x04;
    //
    //ageitar onde ele pega o arquivo, devido a reorganização em pastas
    //
    FILE *file = fopen("../Arquivos/SomaAssembly.mem", "rb");

    if(file == NULL){
        printf("Não foi possivel ler o arquivo!");
        return 0;
    }

    uint8_t *memory = (uint8_t *)malloc(sizeof(uint8_t)* TOTAL_SIZE);
    fread(memory, 1, TOTAL_SIZE, file);
    fclose(file);

    memory[0x80] = 0x05;
    memory[0x81] = 0x03;
    memory[0x83] = 0x02;
    memory[0x84] = 0x01;
    memory[0x86] = 0x06;
    memory[0x87] = 0x03;
    memory[0x89] = 0xFC;
    memory[0x8A] = 0x03;

    int posicao = 0;

    do {
        printf("AC: %x PC: %x FZ: %i FN: %i INSTRUCAO: %x CONTEUDO: %x\n", AC & 0xFF, PC, flagZero(AC), flagNeg(AC), memory[PC], memory[PC+2]);

        switch (memory[PC]) {
            case STA:
                PC += 2;
                posicao = memory[PC];
                memory[posicao] = AC;
                PC += 2;
                break;
            case LDA:
                PC += 2;
                posicao = memory[PC];
                AC = memory[posicao];
                PC += 2;
                break;
            case ADD:
                PC += 2;
                posicao = memory[PC];
                AC += memory[posicao];
                PC += 2;
                break;
            case OR:
                PC += 2;
                posicao = memory[PC];
                AC = AC | memory[posicao];
                PC += 2;
                break;
            case AND:
                PC += 2;
                posicao = memory[PC];
                AC = AC & memory[posicao];
                PC += 2;
                break;
            case NOT:
                AC = ~AC;
                PC += 2;
                break;
            case JMP:
                PC += 2;
                PC = memory[PC] * 2 + 4;
                break;
            case JN:
                PC += 2;
                if (flagNeg(AC)) {
                    PC = memory[PC] * 2 + 4;
                } else {
                    PC += 2;
                }
                break;
            case JZ:
                PC += 2;
                if (flagZero(AC)) {
                    PC = memory[PC] * 2 + 4;
                } else {
                    PC += 2;
                }
                break;
            default:
                PC += 2;
                break;
        }
    } while (memory[PC] != HLT && PC <= 0xFF);


    print_memory(memory, TOTAL_SIZE, AC, PC);

    free(memory);
    return 0;
}
