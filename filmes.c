#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TARVB.H>


#include "structure.h"
#include "addData.h"

int main() {
    int t;
    printf("Digite o grau t: ");
    scanf("%d", &t);

    No *filmes = inicializar();

    int continua = 1;

    while (continua) {
        printf("\n");
        printf("O que você deseja fazer: \n");
        printf("1 - Inserir filme\n");
        printf("2 - Remover filme\n");
        printf("3 - Buscar filme\n");
        printf("4 - Listar filmes em ordem alfabética\n");
        printf("10 - Fechar o programa\n");
        int resposta;
        scanf("%d", &resposta);

        switch (resposta) {
            case 1: {
                //printf("Insira o caminho do arquivo: ");
                //Gabriel se vira
                Filme *novo = criar_filme("star wars", 1972, "George Lucas", 150, "ficcao");

                filmes = inserir_filme(filmes, novo, t);
                printf("Filme %s inserido com sucesso", novo->titulo);
                break;
            }

            case 2: {

            }
            case 3: {
                char *titulo = (char *) malloc(sizeof(char) * 81);
                int ano;
                printf("Qual nome do filme você deseja buscar?\n");
                scanf("%s", titulo);
                printf("Em que ano ele foi lançado?\n");
                scanf("%d", &ano);

                Filme *filme = buscar_filme(filmes, titulo, ano);
                printf("%s", filme->titulo);
                break;
            }

            case 10: {
                continua = 0;
            }
        }

    }


    // menu

    return 0;
}