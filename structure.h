// estrutura da Árvore B, dos filmes e as funções
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef structure_h
#define structure_h

typedef struct filme
{
    char *titulo;
    char *diretor;
    char *genero;
    int ano;
    int duracao;
} Filme;

typedef struct no
{
    Filme **chave;
    struct no **filhos;
    int nChaves;
    int eFolha;
} No;

Filme *criar_filme(char *titulo, int ano, char *diretor, int duracao, char *genero)
{
    Filme *novo = (Filme *)malloc(sizeof(Filme));
    novo->titulo = (char *)malloc(sizeof(char) * (strlen(titulo) + 1));
    strcpy(novo->titulo, titulo);
    novo->ano = ano;
    novo->diretor = (char *)malloc(sizeof(char) * (strlen(diretor) + 1));
    strcpy(novo->diretor, diretor);
    novo->genero = (char *)malloc(sizeof(char) * (strlen(genero) + 1));
    strcpy(novo->genero, genero);
    novo->duracao = duracao;

    return novo;
}

No *inicializar()
{
    return NULL;
}

No *cria(int t)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Falha na alocação de memória para o nó!\n");
        exit(1);
    }

    novo->nChaves = 0;
    novo->eFolha = 1;

    novo->chave = (Filme **)malloc(sizeof(Filme *) * (2 * t - 1));
    if (!novo->chave)
    {
        printf("Falha na alocação de memória para as chaves do nó!\n");
        exit(1);
    }

    novo->filhos = (No **)malloc(sizeof(No *) * (2 * t));
    if (!novo->filhos)
    {
        printf("Falha na alocação de memória para os filhos do nó!\n");
        exit(1);
    }

    int i;
    for (i = 0; i < (2 * t); i++)
    {
        novo->filhos[i] = NULL;
    }

    return novo;
}

void impressao(No *filmes)
{
    if (!filmes)
        return;

    int i = 0;
    while (i < filmes->nChaves)
    {
        if (filmes->filhos[i])
            impressao(filmes->filhos[i]);
        printf("%s %d %s %d %s\n", filmes->chave[i]->titulo, filmes->chave[i]->ano, filmes->chave[i]->diretor, filmes->chave[i]->duracao, filmes->chave[i]->genero);
        i++;
    }
    if (filmes->filhos[i])
        impressao(filmes->filhos[i]);
}

No *liberacao(No *filmes)
{
    if (filmes)
    {
        if (!filmes->eFolha)
        {
            int i;
            for (i = 0; i <= filmes->nChaves; i++)
                liberacao(filmes->filhos[i]);
        }
        for (int j = 0; j < filmes->nChaves; j++)
        {
            free(filmes->chave[j]->titulo);
            free(filmes->chave[j]->diretor);
            free(filmes->chave[j]->genero);
            free(filmes->chave[j]);
        }
        free(filmes->chave);
        free(filmes->filhos);
        free(filmes);
        return NULL;
    }
}

No *divisao(No *x, int i, No *y, int t)
{
    No *z = cria(t);
    z->nChaves = t - 1;
    z->eFolha = y->eFolha;

    int j;
    for (j = 0; j < t - 1; j++)
    {
        z->chave[j] = y->chave[j + t];
    }
    if (y->eFolha == 0)
    {
        for (j = 0; j < t; j++)
        {
            z->filhos[j] = y->filhos[j + t];
            y->filhos[j + t] = NULL;
        }
    }

    y->nChaves = t - 1;

    for (j = x->nChaves; j >= i; j--)
    {
        x->filhos[j + 1] = x->filhos[j];
    }
    x->filhos[i] = z;

    for (j = x->nChaves - 1; j >= i - 1; j--)
    {
        x->chave[j + 1] = x->chave[j];
    }
    x->chave[i - 1] = y->chave[t - 1];

    x->nChaves++;
    return x;
}

No *inserir_filme_incompleto(No *filmes, Filme *filme, int t)
{
    int i = filmes->nChaves - 1;

if (filmes->eFolha)
    {
        while (i >= 0 && strcmp(filme->titulo, filmes->chave[i]->titulo) < 0)
        {
            filmes->chave[i + 1] = filmes->chave[i];
            i--;
        }
        filmes->chave[i + 1] = filme;
        filmes->nChaves++;
        return filmes;
    }

    while ((i >= 0) && (strcmp(filme->titulo, filmes->chave[i]->titulo) < 0))
    {
        i--;
    }
    i++;

    if (filmes->filhos[i]->nChaves == (2 * t) - 1)
    {
        filmes = divisao(filmes, (i + 1), filmes->filhos[i], t);
        if (strcmp(filme->titulo, filmes->chave[i]->titulo) > 0)
        {
            i++;
        }
    }
    filmes->filhos[i] = inserir_filme_incompleto(filmes->filhos[i], filme, t);
    return filmes;
}

No *inserir_filme(No *filmes, Filme *filme, int t)
{

    if (!filmes)
    {
        No *novo = cria(t);
        novo->chave[0] = filme;
        novo->nChaves = 1;
        return novo;
    }

    if (filmes->nChaves == (2 * t) - 1)
    {
        No *novo = cria(t);
        novo->nChaves = 0;
        novo->eFolha = 0;
        novo->filhos[0] = filmes;
        novo = divisao(novo, 1, filmes, t);
        novo = inserir_filme_incompleto(novo, filme, t);
        return novo;
    }

    filmes = inserir_filme_incompleto(filmes, filme, t);
    return filmes;
}

Filme *buscar_filme(No *filmes, char titulo[81], int ano)
{
    if (!filmes)
        return NULL;
    int i = 0;
    while ((i < filmes->nChaves) && (strcmp(filmes->chave[i]->titulo, titulo) < 0))
        i++;
    if ((i < filmes->nChaves) && strcmp(filmes->chave[i]->titulo, titulo) == 0 && (filmes->chave[i]->ano == ano))
        return filmes->chave[i];
    if (filmes->eFolha == 1)
        return NULL;
    return buscar_filme(filmes->filhos[i], titulo, ano);
}

No *alterar(No *filmes, char titulo[81], int ano, char nGenero[31], char nDiretor[51], int nDuracao)
{
    Filme *filme = buscar_filme(filmes, titulo, ano);
    if (filme)
    {
        strcpy(filme->genero, nGenero);
        strcpy(filme->diretor, nDiretor);
        filme->duracao = nDuracao;
    }
    else
    {
        printf("Filme não alterado e não encontrado\n");
    }
    return filmes;
}

void printar_filmes_diretor(No *filmes, char diretor[51])
{
    if (!filmes)
        return;
    int i = 0;
    while (i < filmes->nChaves)
    {
        if (strstr(filmes->chave[i]->diretor, diretor) != NULL)
        {
            printf("%s %d\n", filmes->chave[i]->titulo, filmes->chave[i]->ano);
        }
        i++;
    }
    for (int j = 0; j <= filmes->nChaves; j++)
    {
        printar_filmes_diretor(filmes->filhos[j], diretor);
    }
}

No *retirar_diretor(No *filmes, char diretor[51])
{
    // retirar todos os filmes com o diretor especificado
}

No *retirar_genero(No *filmes, char genero[31])
{
    // retirar todos os filmes com o genero especificado
}

int buscarChave(No* no, const char* franquia) {
    int i = 0;
    while (i < no->nChaves && strcmp(no->chave[i]->titulo, franquia) < 0) {
        i++;
    }
    return i;
}

// Função para remover uma chave de um nó
void removerChave(No* no, int indice) {
    free(no->chave[indice]->titulo);
    free(no->chave[indice]->diretor);
    free(no->chave[indice]->genero);
    free(no->chave[indice]);

    for (int i = indice; i < no->nChaves - 1; i++) {
        no->chave[i] = no->chave[i + 1];
        no->filhos[i + 1] = no->filhos[i + 2];
    }

    no->nChaves--;
}

// Função para remover um filme de uma árvore B
No *removerFilme(No* raiz, const char* franquia, int ordem) {
    if (!raiz) {
        return NULL;
    }

    int indice = buscarChave(raiz, franquia);

    if (indice < raiz->nChaves && strcmp(raiz->chave[indice]->titulo, franquia) == 0) {
        // A chave está presente neste nó
        if (raiz->eFolha) {
            // Se o nó é uma folha, apenas remova a chave
            removerChave(raiz, indice);
        } else {
            // Se o nó não é uma folha, substitua a chave pelo sucessor in-order
            No* sucessor = raiz->filhos[indice + 1];
            while (!sucessor->eFolha) {
                sucessor = sucessor->filhos[0];
            }
            raiz->chave[indice] = sucessor->chave[0];
            raiz->filhos[indice + 1] = removerFilme(raiz->filhos[indice + 1], sucessor->chave[0]->titulo, ordem);
        }
    } else {
        // A chave pode estar presente nos filhos do nó
        int ehUltimo = (indice == raiz->nChaves);

        if (raiz->filhos[indice]->nChaves < ordem) {
            // Se o filho que contém a chave tem menos de ORDEM-1 chaves, preencha-o
            // primeiro
            // Se o filho à esquerda tem mais de ORDEM-1 chaves, empreste uma chave
            if (indice != 0 && raiz->filhos[indice - 1]->nChaves >= ordem) {
                raiz->filhos[indice]->chave[0] = raiz->chave[indice - 1];
                raiz->chave[indice - 1] = raiz->filhos[indice - 1]->chave[raiz->filhos[indice - 1]->nChaves - 1];
                raiz->filhos[indice - 1]->nChaves--;
            }
                // Se o filho à direita tem mais de ORDEM-1 chaves, empreste uma chave
            else if (!ehUltimo && raiz->filhos[indice + 1]->nChaves >= ordem) {
                raiz->filhos[indice]->chave[0] = raiz->chave[indice];
                raiz->chave[indice] = raiz->filhos[indice + 1]->chave[0];
                for (int i = 0; i < raiz->filhos[indice + 1]->nChaves - 1; i++) {
                    raiz->filhos[indice + 1]->chave[i] = raiz->filhos[indice + 1]->chave[i + 1];
                }
                raiz->filhos[indice + 1]->nChaves--;
            }
                // Combinação com o filho à esquerda
            else if (indice != 0) {
                raiz->filhos[indice - 1]->chave[raiz->filhos[indice - 1]->nChaves] = raiz->chave[indice - 1];
                for (int i = 0; i < raiz->filhos[indice]->nChaves; i++) {
                    raiz->filhos[indice - 1]->chave[raiz->filhos[indice - 1]->nChaves + 1 + i] = raiz->filhos[indice]->chave[i];
                }
                raiz->filhos[indice - 1]->nChaves += 1 + raiz->filhos[indice]->nChaves;
                raiz->filhos[indice - 1]->filhos[raiz->filhos[indice - 1]->nChaves] = raiz->filhos[indice]->filhos[0];
                free(raiz->filhos[indice]);
                for (int i = indice - 1; i < raiz->nChaves - 1; i++) {
                    raiz->chave[i] = raiz->chave[i + 1];
                    raiz->filhos[i + 1] = raiz->filhos[i + 2];
                }
                raiz->nChaves--;
                if (raiz->nChaves == 0) {
                    No* tmp = raiz->filhos[0];
                    free(raiz);
                    raiz = tmp;
                }
                raiz->filhos[indice - 1] = removerFilme(raiz->filhos[indice - 1], franquia, ordem);
            }
                // Combinação com o filho à direita
            else {
                raiz->filhos[indice]->chave[raiz->filhos[indice]->nChaves] = raiz->chave[indice];
                for (int i = 0; i < raiz->filhos[indice + 1]->nChaves; i++) {
                    raiz->filhos[indice]->chave[raiz->filhos[indice]->nChaves + 1 + i] = raiz->filhos[indice + 1]->chave[i];
                }
                raiz->filhos[indice]->nChaves += 1 + raiz->filhos[indice + 1]->nChaves;
                raiz->filhos[indice]->filhos[raiz->filhos[indice]->nChaves] = raiz->filhos[indice + 1]->filhos[0];
                free(raiz->filhos[indice + 1]);
                for (int i = indice; i < raiz->nChaves - 1; i++) {
                    raiz->chave[i] = raiz->chave[i + 1];
                    raiz->filhos[i + 1] = raiz->filhos[i + 2];
                }
                raiz->nChaves--;
                if (raiz->nChaves == 0) {
                    No* tmp = raiz->filhos[0];
                    free(raiz);
                    raiz = tmp;
                }
                raiz->filhos[indice] = removerFilme(raiz->filhos[indice], franquia, ordem);
            }
        } else {
            // Se o filho que contém a chave tem ORDEM ou mais chaves, remova recursivamente
            raiz->filhos[indice] = removerFilme(raiz->filhos[indice], franquia, ordem);
        }
    }

    return raiz;
}

#endif