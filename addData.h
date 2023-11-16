#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structure.h>

#define MAX_TAM 200

void lerDadosArquivo(const char *nomeArquivo, Filme ***listaFilmes, int *numFilmes) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Filme **filmes = (Filme **)malloc(MAX_TAM * sizeof(Filme *));
    *numFilmes = 0;

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *titulo = strtok(linha, "/");
        int ano = atoi(strtok(NULL, "/"));
        char *diretor = strtok(NULL, "/");
        char *genero = strtok(NULL, "/");               
        int duracao = atoi(strtok(NULL, "/"));
        
        Filme *novoFilme = criar_filme(titulo, ano, diretor, duracao, genero);
        filmes[*numFilmes] = novoFilme;
        (*numFilmes)++;

        if (*numFilmes >= MAX_TAM) {
            // Caso o número máximo de filmes seja atingido, realocar o array
            MAX_TAM *= 2;
            filmes = realloc(filmes, MAX_TAM * sizeof(Filme *));
        }
    }

    fclose(arquivo);
    *listaFilmes = filmes;
}


int main() {
    Filme **listaFilmes;
    int numFilmes;

    lerDadosArquivo("dados.txt", &listaFilmes, &numFilmes);


    for (int i = 0; i < numFilmes; i++) {
        free(listaFilmes[i]->titulo);
        free(listaFilmes[i]->diretor);
        free(listaFilmes[i]->genero);
        free(listaFilmes[i]);
    }
    free(listaFilmes);

    return 0;
}
