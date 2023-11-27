#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <structure.h>

#define MAX_TAM 300

void lerDadosArquivo(const char *nomeArquivo, No **filmes, int t)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char linha[MAX_TAM];
    while (fgets(linha, MAX_TAM, arquivo) != NULL)
    {
        char *titulo = strtok(linha, "/");
        int ano = atoi(strtok(NULL, "/"));
        char *diretor = strtok(NULL, "/");
        char *genero = strtok(NULL, "/");
        int duracao = atoi(strtok(NULL, "/"));

        *filmes = inserir_filme(*filmes, criar_filme(titulo, ano, diretor, duracao, genero), t);
    }

    fclose(arquivo);
}
