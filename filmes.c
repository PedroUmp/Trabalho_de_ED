#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structure.h"
#include "addData.h"

int main()
{
    int t;
    int globalCounter = 0;
    printf("Digite o grau t: ");
    scanf("%d", &t);
    No *filmes = inicializar();
    lerDadosArquivo("filmes.txt", &filmes, t, &globalCounter);

    int continua = 1;

    char *titulo = (char *)malloc(sizeof(char));
    char *diretor = (char *)malloc(sizeof(char));
    char *genero = (char *)malloc(sizeof(char));
    char *franquia = (char *)malloc(sizeof(char));
    int ano = 0;
    int duracao = 0;

    while (continua)
    {
        printf("\n");
        printf("O que voce deseja fazer?\n");
        printf("1 - Fechar o programa \n");
        printf("2 - Inserir filme com todas as informacoes\n");
        printf("3 - Remover filme por nome e ano de lançamento\n");
        printf("4 - Buscar filme e receber informações subordinadas\n");
        printf("5 - Listar filmes em ordem alfabetica\n");
        printf("6 - Alterar filme com as informacoes subordinadas\n");
        printf("7 - Buscar todos os filmes de um determinado diretor\n");
        printf("8 - Retirar todos os filmes de um determinado diretor\n");
        printf("9 - Retirar todos os filmes de um determinado genero\n");
        printf("10 - Retirar todos os filmes de uma franquia\n");
        printf("11 - Listar total de filmes\n");
        printf("12 - Imprime metodo Rosseti\n");
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
            titulo = converterParaMinusculo(titulo);

            printf("Quando o filme foi lancado? ");
            scanf("%d", &ano);
            getchar();

            printf("Quem e o diretor do filme? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';
            diretor = converterParaMinusculo(diretor);

            printf("Quanto tempo em minutos dura o filme? ");
            scanf("%d", &duracao);
            getchar();

            printf("Qual o genero do filme? ");
            fgets(genero, 31, stdin);
            genero[strcspn(genero, "\n")] = '\0';
            genero = converterParaMinusculo(genero);

            Filme *novo = criar_filme(titulo, ano, diretor, duracao, genero, &globalCounter);
            printf("\nFilme criado: %s %d\n", novo->titulo, novo->ano);
            filmes = inserir_filme(filmes, novo, t);
            printf("id: %d", novo->id);
            break;
        }

        case 3:
        {
            printf("Qual o nome do filme? ");
            fgets(titulo, 81, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';
            titulo = converterParaMinusculo(titulo);

            printf("Quando o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            filmes = retirar_filme(filmes, titulo, ano, t);
            break;
        }

        case 4:
        {
            printf("Qual nome do filme voce deseja buscar? ");
            fgets(titulo, 81, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';
            titulo = converterParaMinusculo(titulo);

            printf("Em que ano o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            Filme *filme = buscar_filme(filmes, titulo, ano);
            if (filme)
                printf("Diretor: %s\nDuracao: %d\nGenero: %s\n", filme->diretor, filme->duracao, filme->genero);
            else
                printf("Filme nao encontrado\n");
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
            titulo = converterParaMinusculo(titulo);


            printf("Quando o filme foi lançado? ");
            scanf("%d", &ano);
            getchar();

            printf("Qual e o novo diretor? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';
            diretor = converterParaMinusculo(diretor);

            printf("Qual e a nova duração do filme? ");
            scanf("%d", &duracao);
            getchar();

            printf("Qual o novo genero do filme? ");
            fgets(genero, 31, stdin);
            genero[strcspn(genero, "\n")] = '\0';
            genero = converterParaMinusculo(genero);

            filmes = alterar(filmes, titulo, ano, genero, diretor, duracao);

            break;
        }

        case 7:
        {
            printf("Qual diretor voce quer buscar? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';
            diretor = converterParaMinusculo(diretor);

            printf("\nFilmes do diretor %s:\n", diretor);
            printar_filmes_diretor(filmes, diretor);
            break;
        }

        case 8:
        {
            printf("Do qual diretor você quer retirar os filmes? ");
            fgets(diretor, 51, stdin);
            diretor[strcspn(diretor, "\n")] = '\0';
            diretor = converterParaMinusculo(diretor);

            filmes = retirar_diretor(filmes, diretor, t);
            printf("Filmes do %s retirados\n", diretor);
            break;
        }

        case 9:
        {
            printf("Do qual genero você quer retirar os filmes? ");
            fgets(genero, 31, stdin);
            genero[strcspn(genero, "\n")] = '\0';
            genero = converterParaMinusculo(genero);

            filmes = retirar_genero(filmes, genero, t);
            printf("Filmes do %s retirados\n", genero);
            break;
        }

        case 10:
        {
            printf("Da qual franquia você quer retirar os filmes? ");
            fgets(franquia, 81, stdin);
            franquia[strcspn(franquia, "\n")] = '\0';
            franquia = converterParaMinusculo(franquia);

            filmes = retirar_franquia(filmes, franquia, t);
            break;
        }

        case 11:
        {
            int num = num_filmes(filmes);
            printf("Total de Filmes: %d\n", num);
            break;
        }

            case 12:
            {
                imprimeId(filmes);
                imp_rec(filmes, 0);
                break;
            }

        default:
        {
            printf("Opção invalida\n");
        }
        }
    }

    return 0;
}