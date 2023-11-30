#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "addData.h"

int main()
{
    int t;
    printf("Digite o grau t: ");
    scanf("%d", &t);

    No *filmes = inicializar();
    lerDadosArquivo("filmes.txt", &filmes, t);

    int continua = 1;

    char *titulo = (char *)malloc(sizeof(char));
    char *diretor = (char *)malloc(sizeof(char));
    char *genero = (char *)malloc(sizeof(char));
    int ano = 0;
    int duracao = 0;

    while (continua)
    {
        printf("\n");
        printf("O que você deseja fazer?\n");
        printf("1 - Fechar o programa \n");
        printf("2 - Inserir filme com todas as informações\n");
        printf("3 - Remover filme por nome e ano de lançamento\n");
        printf("4 - Buscar filme e receber informações subordinadas\n");
        printf("5 - Listar filmes em ordem alfabética\n");
        printf("6 - Alterar filme com as informações subordinadas\n");
        printf("7 - Buscar todos os filmes de um determinado diretor\n");
        printf("8 - Retirar todos os filmes de um determinado diretor\n"); // Atharv
        printf("9 - Retirar todos os filmes de um determinado gênero\n");  // Atharv
        printf("10 - Retirar todos os filmes de uma franquia\n");          // Gabriel
        printf("11 - Listar total de filmes\n");
        printf("Digite aqui: ");

        int resposta;
        scanf("%d", &resposta);
        getchar();

        switch (resposta)
        {
        case 1:
        {
            free(titulo);
            free(diretor);
            free(genero);
            filmes = liberacao(filmes);
            continua = 0;
            break;
        }

        case 2:
        {
            printf("Qual o nome do filme? ");
            fgets(titulo, 81, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            printf("Quando o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            printf("Quem é o diretor do filme? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';

            printf("Quanto tempo em minutos dura o filme? ");
            scanf("%d", &duracao);
            getchar();

            printf("Qual o gênero do filme? ");
            fgets(genero, 31, stdin);
            genero[strcspn(genero, "\n")] = '\0';

            Filme *novo = criar_filme(titulo, ano, diretor, duracao, genero);
            printf("\nFilme criado: %s %d\n", novo->titulo, novo->ano);
            filmes = inserir_filme(filmes, novo, t);
            break;
        }

        case 3:
        {
            printf("Qual o nome do filme? ");
            fgets(titulo, 81, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            printf("Quando o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            filmes = retirar_filme(filmes, titulo, ano, t);
            break;
        }

        case 4:
        {
            printf("Qual nome do filme você deseja buscar? ");
            fgets(titulo, 81, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            printf("Em que ano o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            Filme *filme = buscar_filme(filmes, titulo, ano);
            if (filme)
                printf("Diretor: %s\nDuracao: %d\nGenero: %s\n", filme->diretor, filme->duracao, filme->genero);
            else
                printf("Filme não encontrado\n");
            break;
        }

        case 5:
        {
            printf("\nLista de filmes:\n");
            impressao(filmes);
            break;
        }

        case 6:
        {
            printf("Qual filme você deseja alterar? ");
            fgets(titulo, 81, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            printf("Quando o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            printf("Qual é o novo diretor? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';

            printf("Qual é a nova duração do filme? ");
            scanf("%d", &duracao);
            getchar();

            printf("Qual o novo gênero do filme? ");
            fgets(genero, 31, stdin);
            genero[strcspn(genero, "\n")] = '\0';

            filmes = alterar(filmes, titulo, ano, genero, diretor, duracao);

            break;
        }

        case 7:
        {
            printf("Qual diretor voce quer buscar? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';

            printf("\nFilmes do diretor %s:\n", diretor);
            printar_filmes_diretor(filmes, diretor);
            break;
        }

        case 8:
        {
            break;
        }

        case 9:
        {
            break;
        }

        case 10:
        {
            // char *franquia = (char *)malloc(sizeof(char) * 81);
            // No *copia_Filme = filmes;
            // if (!franquia)
            // {
            //     printf("Falha na alocação");
            //     break;
            // }
            // printf("Digite a franquia que você deseja remover: ");
            // fgets(franquia, 81, stdin);
            // franquia[strcspn(genero, "\n")] = '\0';
            // filmes = removerFilme(filmes, "Star Wars", t);
            // free(franquia);
            // // fazer todos os testes de allocação bem sucedida
            break;
        }

        case 11:
        {
            int num = num_filmes(filmes);
            printf("Total de Filmes: %d\n", num);
            break;
        }

        default:
        {
            printf("Opção inválida\n");
        }
        }
    }

    return 0;
}