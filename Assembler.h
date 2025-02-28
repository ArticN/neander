#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// De padrão estamos usando valores em hexadecimal por isso o uint8_t
//

bool linha_vazia(char *line);
bool mneumon_valido(char *mneumon);
bool final_bloco(char *line);

void instrucao_simples(char *mneumon, uint8_t *memory_posit);
void instrucao_composta(char *mneumon, uint8_t value, uint8_t *mneumon_mem_posit, uint8_t *value_mem_posit);
void escrever(uint8_t mem[516]);

int buscar(char *line, char *w[10]);
int executar(void);





