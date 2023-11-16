#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TARVB.H>


#include "structure.h"
#include "addData.h"

int main() {
    size_t t_titulo = 81;
    size_t t_diretor = 51;
    size_t t_genero = 31;

    int t;
    printf("Digite o grau t: ");
    scanf("%d", &t);

    No *filmes = inicializar();

    int continua = 1;

    while (continua) {
        printf("\n");
        printf("O que você deseja fazer: \n");
        printf("1 - Inserir filme com arquivo \n");
        printf("2 - Inserir filme com input\n");
        printf("3 - Remover filme\n");
        printf("4 - Buscar filme e receber informações subordinadas\n");
        printf("5 - Listar filmes em ordem alfabética\n");
        printf("10 - Fechar o programa\n");

        int resposta;
        scanf("%d", &resposta);
        getchar();

        switch (resposta) {
            case 1: {
                //printf("Insira o caminho do arquivo: ");
                //Gabriel se vira
                Filme *novo = criar_filme("starwars", 1972, "George Lucas", 150, "ficcao");

                filmes = inserir_filme(filmes, novo, t);
                printf("Filme %s inserido com sucesso", novo->titulo);
                break;
            }

            case 2: {
                char* titulo = (char *) malloc(sizeof(char) * 81);
                char* diretor = (char *) malloc(sizeof(char) * 51);
                char *genero = (char *) malloc(sizeof(char) * 31);
                int ano;
                int duracao;


                printf("Qual o nome do filme?");
                fgets(titulo, 81, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Quando o filme foi lançado?");
                scanf("%d", &ano);
                getchar();

                printf("Quem é o diretor do filme?");
                fgets(diretor, 51, stdin);
                diretor[strcspn(diretor, "\n")] = '\0';

                printf("Quanto tempo em minutos dura o filme?");
                scanf("%d", &duracao);
                getchar();

                printf("Qual o gênero do filme?");
                fgets(genero, 31, stdin);
                genero[strcspn(genero, "\n")] = '\0';

                Filme *novo = criar_filme(titulo, ano, diretor, duracao, genero);
                filmes = inserir_filme(filmes, novo, t);
            }

            case 3: {
                break;
            }

            case 4: {
                char *titulo = (char *) malloc(sizeof(char) * 81);
                int ano;
                printf("Qual nome do filme você deseja buscar?\n");
                scanf("%s", titulo);
                printf("Em que ano o filme foi lançado?\n");
                scanf("%d", &ano);

                Filme *filme = buscar_filme(filmes, titulo, ano);
                printf("%s", filme->titulo);

                break;
            }

            case 5: {
                impressao(filmes, 1);
                break;
            }

            case 6: {
                break;
            }

            case 7: {
                break;
            }

            case 8: {
                break;
            }

            case 9: {
                break;
            }

            case 10: {
                continua = 0;
                break;
            }
            default: {
                printf("Opção inválida");
            }
        }

    }




    return 0;
}