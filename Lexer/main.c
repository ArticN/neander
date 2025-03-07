#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#define MAX_SRC 4096  // Tamanho máximo do código-fonte abreviado

// Função para ler o conteúdo de um arquivo e armazená-lo em um buffer
char *ler_arquivo(const char *arq) { // Arquivo abreviado
    FILE *f = fopen(arq, "r"); // Arquivo abreviado
    if (!f) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    char *buf = (char *)malloc(MAX_SRC); // Buffer abreviado
    if (!buf) {
        perror("Erro ao alocar memória");
        fclose(f);
        return NULL;
    }

    size_t tam = fread(buf, 1, MAX_SRC - 1, f); // Tamanho abreviado
    buf[tam] = '\0'; // Adiciona o terminador de string

    fclose(f);
    return buf;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.asm>\n", argv[0]);
        return 1;
    }

    char *src = ler_arquivo(argv[1]); // Fonte abreviado
    if (!src) {
        return 1;
    }

    printf("=== Analisando %s ===\n", argv[1]);
    tokenizar(src);
    
    free(src); // Liberar memória alocada
    return 0;
}