#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

#define MAX_TK 256 // Máximo de tokens abreviado

Token tk[MAX_TK]; // Tokens
int cnt_tk = 0;   // Contador de tokens

// Função para converter TokenTipo em string
const char *nome_do_tipo(TokenTipo tipo) {
    switch (tipo) {
        case TOKEN_DADO:        return "TOKEN_DADO";
        case TOKEN_CODIGO:      return "TOKEN_CODIGO";
        case TOKEN_FIM:         return "TOKEN_FIM";
        case TOKEN_NUMERO:      return "TOKEN_NUMERO";
        case TOKEN_COMANDO:     return "TOKEN_COMANDO";
        case TOKEN_COMENTARIO:  return "TOKEN_COMENTARIO";
        case TOKEN_VARIAVEL:    return "TOKEN_VARIAVEL";
        case TOKEN_DB:          return "TOKEN_DB";
        case TOKEN_DS:          return "TOKEN_DS";
        default:                return "TOKEN_DESCONHECIDO";
    }
}

void adicionar_token(TokenTipo tipo, const char *lex) {
    if (cnt_tk >= MAX_TK) return;
    tk[cnt_tk].tipo = tipo;
    strncpy(tk[cnt_tk].lex, lex, 31);
    cnt_tk++;
}

int eh_p_chave(const char *pal) {
    for (size_t i = 0; i < n_p_chave; i++) {
        if (strcmp(pal, p_chave[i]) == 0) return 1;
    }
    return 0;
}

int eh_cmd(const char *pal) {
    for (size_t i = 0; i < n_cmds_comp; i++) {
        if (strcmp(pal, cmds_comp[i].mnem) == 0) return 1;
    }
    for (size_t i = 0; i < n_cmds_simp; i++) {
        if (strcmp(pal, cmds_simp[i].mnem) == 0) return 1;
    }
    return 0;
}

void tokenizar(const char *src) {
    char buf[32];
    int idx = 0;

    while (*src) {
        if (isspace(*src)) {
            src++;
            continue;
        }
        if (*src == ';') { // Comentário
            while (*src && *src != '\n') src++;
            continue;
        }
        if (isdigit(*src) || (*src == '0' && tolower(*(src + 1)) == 'x')) { // Número (decimal ou hexadecimal)
            idx = 0;
            if (*src == '0' && tolower(*(src + 1)) == 'x') { // Hexadecimal
                buf[idx++] = *src++; // '0'
                buf[idx++] = *src++; // 'x'
                while (isxdigit(*src)) { // Dígitos hexadecimais
                    buf[idx++] = *src++;
                }
            } else { // Decimal
                while (isdigit(*src)) {
                    buf[idx++] = *src++;
                }
            }
            buf[idx] = '\0';
            adicionar_token(TOKEN_NUMERO, buf);
            continue;
        }
        if (isalpha(*src) || *src == '_' || *src == '.') { // Nome de variável, comando, DB, DS ou diretiva
            idx = 0;
            while (isalnum(*src) || *src == '_' || *src == '.') { // Aceita letras, números, underscores e pontos
                buf[idx++] = *src++;
            }
            buf[idx] = '\0';
            if (eh_p_chave(buf)) {
                if (strcmp(buf, ".DATA") == 0) {
                    adicionar_token(TOKEN_DADO, buf);
                } else if (strcmp(buf, ".CODE") == 0) {
                    adicionar_token(TOKEN_CODIGO, buf);
                } else if (strcmp(buf, "END") == 0) {
                    adicionar_token(TOKEN_FIM, buf);
                }
            } else if (eh_cmd(buf)) {
                adicionar_token(TOKEN_COMANDO, buf);
            } else if (strcmp(buf, "DB") == 0) {
                adicionar_token(TOKEN_DB, buf);
            } else if (strcmp(buf, "DS") == 0) {
                adicionar_token(TOKEN_DS, buf);
            } else {
                adicionar_token(TOKEN_VARIAVEL, buf); // Nome de variável
            }
            continue;
        }
        src++; // Ignora caracteres desconhecidos
    }

    // Exibir tokens
    for (int i = 0; i < cnt_tk; i++) {
        printf("Token: %s, Tipo: %s\n", tk[i].lex, nome_do_tipo(tk[i].tipo));
    }
}