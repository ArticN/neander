#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define TOTAL_SIZE 516

#define NOP 0x00
#define STA 0x10
#define LDA 0x20
#define ADD 0x30
#define OR 0x40
#define AND 0x50
#define NOT 0x60
#define JMP 0x80
#define JN 0x90
#define JZ 0xA0
#define HLT 0xF0

void print_memory(uint8_t *bytes, int size, uint8_t ac, uint8_t pc);
bool flagZero(const int AC);
bool flagNeg(const int AC);
