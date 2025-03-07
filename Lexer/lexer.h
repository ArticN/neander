#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

typedef enum {
    TOKEN_DADO,      // Token para a diretiva .DATA
    TOKEN_CODIGO,    // Token para a diretiva .CODE
    TOKEN_FIM,       // Token para a diretiva END
    TOKEN_NUMERO,    // Token para números (ex: 10, 0xA, 25)
    TOKEN_COMANDO,   // Token para comandos (ex: NOP, LDA, ADD, STA, HLT)
    TOKEN_COMENTARIO,// Token para comentários (ex: ; teste de comentário)
    TOKEN_VARIAVEL,  // Token para nomes de variáveis (ex: VAR1, VAR2)
    TOKEN_DB,        // Token para DB (Define Byte)
    TOKEN_DS,        // Token para DS (Define Space)
    TOKEN_DESCONHECIDO // Token para símbolos não reconhecidos
} TokenTipo;

typedef struct {
    TokenTipo tipo;
    char lex[32];
} Token;

typedef struct {
    const char *mnem;
    uint8_t op;
} Comando;

static const Comando cmds_comp[] = {
    {"STA", 0x10}, {"LDA", 0x20}, {"ADD", 0x30}, {"OR", 0x40},
    {"AND", 0x50}, {"JMP", 0x80}, {"JN", 0x90}, {"JZ", 0xA0}
};

static const Comando cmds_simp[] = {
    {"NOP", 0x00}, {"NOT", 0x60}, {"HLT", 0xF0}
};

static const size_t n_cmds_comp = sizeof(cmds_comp) / sizeof(cmds_comp[0]);
static const size_t n_cmds_simp = sizeof(cmds_simp) / sizeof(cmds_simp[0]);

static const char *p_chave[] = {".DATA", ".CODE", "END"};
static const size_t n_p_chave = sizeof(p_chave) / sizeof(p_chave[0]);

void tokenizar(const char *src);

#endif