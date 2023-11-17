#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "addData.h"

int main() {
   
    char* titulo = (char *) malloc(sizeof(char) * 81);
    char* diretor = (char *) malloc(sizeof(char) * 51);
    char *genero = (char *) malloc(sizeof(char) * 31);
    int ano;
    int duracao;

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
        printf("6 - Alterar as informações subordinadas");
        printf("7 - Buscar todos os filmes de um determinado diretor");
        printf("10 - Fechar o programa\n");

        int resposta;
        scanf("%d", &resposta);
        getchar();

        switch (resposta) {
            case 1: {
                char nome_arquivo[20];
                printf("Insira o caminho do arquivo: ");
                fgets(nome_arquivo, 20, stdin);
                //lerDadosArquivo(nome_arquivo, *filmes, 0, t);
                break;
            }

            case 2: {
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

                printf("Qual filme você deseja alterar:");
                fgets(titulo, 81, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Quando o filme foi lançado?");
                scanf("%d", &ano);
                getchar();

                printf("Qual é o novo diretor?");
                fgets(diretor, 51, stdin);
                diretor[strcspn(diretor, "\n")] = '\0';

                printf("Qual é a nova duração do filme?");
                scanf("%d", &duracao);
                getchar();

                printf("Qual o novo gênero do filme?");
                fgets(genero, 31, stdin);
                genero[strcspn(genero, "\n")] = '\0';

                filmes = alterar(filmes, titulo, ano, genero, diretor, duracao);
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