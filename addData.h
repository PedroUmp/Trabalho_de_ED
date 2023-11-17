#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <structure.h>

#define MAX_TAM 200

void lerDadosArquivo(const char *nomeArquivo, No **filmes, int *numFilmes, int t) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    *numFilmes = 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *titulo = strtok(linha, "/");
        int ano = atoi(strtok(NULL, "/"));
        char *diretor = strtok(NULL, "/");
        char *genero = strtok(NULL, "/");               
        int duracao = atoi(strtok(NULL, "/"));
        
        Filme *novoFilme = criar_filme(titulo, ano, diretor, duracao, genero);

        *filmes = inserir_filme(*filmes, novoFilme, t);

    fclose(arquivo);
    }
}
