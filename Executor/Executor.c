#include "Executor.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void print_memory(uint8_t *mem, size_t size, uint8_t ac, uint8_t pc, bool z, bool n) {
  printf("Final Memory State:\n");
  printf("AC: %03d  | PC: %03d\n", ac, pc);
  printf("Z : %s | N : %s\n", z ? "true" : "false", n ? "true" : "false");

  for (size_t offset = 0; offset < size; offset += 16) {
    printf("%08zx: ", offset);

    for (size_t i = 0; i < 16; i++) {
      if (offset + i < size)
        printf("%02x ", mem[offset + i]);
      else
        printf("   ");
    }

    printf("\n");
  }
}

bool verify_file_identifier(FILE *file) {
  uint8_t file_id[4];
  fread(file_id, 1, 4, file);

  const uint8_t expected_id[] = {0x03, 0x4E, 0x44, 0x52};
  if (memcmp(file_id, expected_id, 4) != 0) {
    fprintf(stderr, "Invalid file identifier! Expected 03 4E 44 52\n");
    return false;
  }

  printf("Valid file identifier detected: %02x %02x %02x %02x\n", file_id[0], file_id[1], file_id[2], file_id[3]);
  return true;
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <arquivo.mem>\n", argv[0]);
    return 1;
  }

  uint8_t ac = 0, pc = 0;
  bool z = false, n = false;

  const char *file_name = argv[1];
  FILE *file = fopen(file_name, "rb");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  if (!verify_file_identifier(file)) {
    fclose(file);
    return 1;
  }

  uint8_t mem[TOTAL_SIZE];
  fread(mem + 4, 1, 512, file);
  fclose(file);

  while (mem[pc] != HLT) {
    z = (ac == 0);
    n = (ac & 0x80) != 0;

    switch (mem[pc]) {
    case NOP:
      break;
    case STA:
      mem[mem[pc + 2] * 2 + 4] = ac;
      break;
    case LDA:
      ac = mem[mem[pc + 2] * 2 + 4];
      break;
    case ADD:
      ac += mem[mem[pc + 2] * 2 + 4];
      break;
    case OR:
      ac |= mem[mem[pc + 2] * 2 + 4];
      break;
    case AND:
      ac &= mem[mem[pc + 2] * 2 + 4];
      break;
    case NOT:
      ac = ~ac;
      pc += 2;
      continue;
    case JMP:
      pc = mem[pc + 2] * 2 + 4;
      continue;
    case JN:
      if (n) {
        pc = mem[pc + 2] * 2 + 4;
        continue;
      }
      break;
    case JZ:
      if (z) {
        pc = mem[pc + 2] * 2 + 4;
        continue;
      }
      break;
    }

    pc += 4;
  }

  print_memory(mem, TOTAL_SIZE, ac, pc, z, n);
  return 0;
}
