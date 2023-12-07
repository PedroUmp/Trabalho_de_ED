#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <structure.h>

#define MAX_TAM 300

void lerDadosArquivo(const char *nomeArquivo, No **filmes, int t, int *globalCounter)
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
        titulo = converterParaMinusculo(titulo);
        int ano = atoi(strtok(NULL, "/"));
        char *diretor = strtok(NULL, "/");
        diretor = converterParaMinusculo(diretor);
        char *genero = strtok(NULL, "/");
        genero = converterParaMinusculo(genero);
        int duracao = atoi(strtok(NULL, "/"));

        *filmes = inserir_filme(*filmes, criar_filme(titulo, ano, diretor, duracao, genero, globalCounter), t);
    }

    fclose(arquivo);
}
