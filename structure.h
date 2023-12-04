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
    int id;
} Filme;

typedef struct no
{
    Filme **chave;
    struct no **filhos;
    int nChaves;
    int eFolha;
} No;

Filme *criar_filme(char *titulo, int ano, char *diretor, int duracao, char *genero, int *globalCounter)
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
    novo->id = (*globalCounter);
    (*globalCounter)++;

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
        printf("%s %d %s %d %s %d\n", filmes->chave[i]->titulo, filmes->chave[i]->ano, filmes->chave[i]->diretor, filmes->chave[i]->duracao, filmes->chave[i]->genero, filmes->chave[i]->id);
        i++;
    }
    if (filmes->filhos[i])
        impressao(filmes->filhos[i]);
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

int num_filmes(No *filmes)
{
    if (!filmes)
        return 0;
    int i = 0;
    while (i < filmes->nChaves)
    {
        i++;
    }
    for (int j = 0; j <= filmes->nChaves; j++)
    {
        i += num_filmes(filmes->filhos[j]);
    }
    return i;
}

No *liberacao(No *filmes)
{
    if (filmes)
    {
        if (!filmes->eFolha)
        {
            for (int i = 0; i <= filmes->nChaves; i++)
                liberacao(filmes->filhos[i]);
        }
        for (int i = 0; i < filmes->nChaves; i++)
        {
            free(filmes->chave[i]->titulo);
            free(filmes->chave[i]->diretor);
            free(filmes->chave[i]->genero);
            free(filmes->chave[i]);
        }
        free(filmes->chave);
        free(filmes->filhos);
        free(filmes);
        return NULL;
    }
}

No *free_filmes(No *filmes)
{
    if (filmes)
    {
        if (!filmes->eFolha)
        {
            for (int i = 0; i <= filmes->nChaves; i++)
                free_filmes(filmes->filhos[i]);
        }
        free(filmes->chave);
        free(filmes->filhos);
        free(filmes);
        return NULL;
    }
}

No *free_filmes_remove(No *filmes)
{
    free(filmes->chave);
    free(filmes->filhos);
    free(filmes);
    return NULL;
}

No *retirar_filme_helper(No *filmes, char titulo[81], int t, Filme *p)
{
    if (!filmes)
        return filmes;
    int i;
    for (i = 0; i < filmes->nChaves && strcmp(titulo, filmes->chave[i]->titulo) > 0; ++i)
        ;
    if (i < filmes->nChaves && strcmp(titulo, filmes->chave[i]->titulo) == 0)
    {
        if (filmes->eFolha) // 1
        {
            int j;
            for (j = i; j < filmes->nChaves - 1; j++)
            {
                filmes->chave[j] = filmes->chave[j + 1];
            }
            filmes->nChaves--;
            if (!filmes->nChaves)
            {
                free_filmes(filmes);
                filmes = NULL;
            }
            return filmes;
        }
        if (!filmes->eFolha && filmes->filhos[i]->nChaves >= t) // 2A
        {
            No *y = filmes->filhos[i];
            while (!y->eFolha)
                y = y->filhos[y->nChaves];
            Filme *temp = y->chave[y->nChaves - 1];
            filmes->filhos[i] = retirar_filme_helper(filmes->filhos[i], temp->titulo, t, p);
            filmes->chave[i] = temp;
            return filmes;
        }
        if (!filmes->eFolha && filmes->filhos[i + 1]->nChaves >= t) // 2B
        {
            No *y = filmes->filhos[i + 1];
            while (!y->eFolha)
                y = y->filhos[0];
            Filme *temp = y->chave[0];
            y = retirar_filme_helper(filmes->filhos[i + 1], temp->titulo, t, p);
            filmes->chave[i] = temp;
            return filmes;
        }
        if (!filmes->eFolha && filmes->filhos[i + 1]->nChaves == t - 1 && filmes->filhos[i]->nChaves == t - 1) // 2C
        {
            No *y = filmes->filhos[i];
            No *z = filmes->filhos[i + 1];
            y->chave[y->nChaves] = p;
            int j;
            for (j = 0; j < t - 1; j++)
            {
                y->chave[t + j] = z->chave[j];
            }
            for (j = 0; j < t; j++)
            {
                y->filhos[t + j] = z->filhos[j];
                z->filhos[j] = NULL;
            }
            y->nChaves = 2 * t - 1;
            for (j = i; j < filmes->nChaves - 1; j++)
            {
                filmes->chave[j] = filmes->chave[j + 1];
            }
            for (j = i + 1; j < filmes->nChaves; j++)
            {
                filmes->filhos[j] = filmes->filhos[j + 1];
            }
            filmes->filhos[j] = NULL;
            free_filmes_remove(z);
            filmes->nChaves--;
            if (!filmes->nChaves)
            {
                No *temp = filmes;
                filmes = filmes->filhos[0];
                temp->filhos[0] = NULL;
                free_filmes_remove(temp);
                filmes = retirar_filme_helper(filmes, titulo, t, p);
            }
            else
            {
                filmes->filhos[i] = retirar_filme_helper(filmes->filhos[i], titulo, t, p);
            }
            return filmes;
        }
    }
    No *y = filmes->filhos[i], *z = NULL;
    if (y->nChaves == t - 1) // 3A e 3B
    {
        if ((i < filmes->nChaves) && (filmes->filhos[i + 1]->nChaves >= t))
        {
            z = filmes->filhos[i + 1];
            y->chave[t - 1] = filmes->chave[i];
            y->nChaves++;
            filmes->chave[i] = z->chave[0];
            int j;
            for (j = 0; j < z->nChaves - 1; j++)
            {
                z->chave[j] = z->chave[j + 1];
            }
            y->filhos[y->nChaves] = z->filhos[0];
            for (j = 0; j < z->nChaves; j++)
            {
                z->filhos[j] = z->filhos[j + 1];
            }
            z->nChaves--;
            filmes->filhos[i] = retirar_filme_helper(filmes->filhos[i], titulo, t, p);
            return filmes;
        }
        if ((i > 0) && (!z) && (filmes->filhos[i - 1]->nChaves >= t))
        {
            z = filmes->filhos[i - 1];
            int j;
            for (j = y->nChaves; j > 0; j--)
            {
                y->chave[j] = y->chave[j - 1];
            }
            for (j = y->nChaves + 1; j > 0; j--)
            {
                y->filhos[j] = y->filhos[j - 1];
            }
            y->chave[0] = filmes->chave[i - 1];
            y->nChaves++;
            filmes->chave[i - 1] = z->chave[z->nChaves - 1];
            y->filhos[0] = z->filhos[z->nChaves];
            z->nChaves--;
            filmes->filhos[i] = retirar_filme_helper(y, titulo, t, p);
            return filmes;
        }
        if (!z)
        {
            if (i < filmes->nChaves && filmes->filhos[i + 1]->nChaves == t - 1)
            {
                z = filmes->filhos[i + 1];
                y->chave[t - 1] = filmes->chave[i];
                y->nChaves++;
                int j;
                for (j = 0; j < t - 1; j++)
                {
                    y->chave[t + j] = z->chave[j];
                    y->nChaves++;
                }
                if (!y->eFolha)
                {
                    for (j = 0; j < t; j++)
                    {
                        y->filhos[t + j] = z->filhos[j];
                        z->filhos[j] = NULL;
                    }
                }
                free_filmes(z);
                for (j = i; j < filmes->nChaves - 1; j++)
                {
                    filmes->chave[j] = filmes->chave[j + 1];
                    filmes->filhos[j + 1] = filmes->filhos[j + 2];
                }
                filmes->filhos[filmes->nChaves] = NULL;
                filmes->nChaves--;
                if (!filmes->nChaves)
                {
                    No *temp = filmes;
                    filmes = filmes->filhos[0];
                    temp->filhos[0] = NULL;
                    free_filmes(temp);
                }
                filmes = retirar_filme_helper(filmes, titulo, t, p);
                return filmes;
            }
            if (i > 0 && filmes->filhos[i - 1]->nChaves == t - 1)
            {
                z = filmes->filhos[i - 1];
                if (i == filmes->nChaves)
                    z->chave[t - 1] = filmes->chave[i - 1];
                else
                    z->chave[t - 1] = filmes->chave[i];
                z->nChaves++;
                int j;
                for (j = 0; j < t - 1; j++)
                {
                    z->chave[t + j] = y->chave[j];
                    z->nChaves++;
                }
                if (!z->eFolha)
                {
                    for (j = 0; j < t; j++)
                    {
                        z->filhos[t + j] = y->filhos[j];
                        y->filhos[j] = NULL;
                    }
                }
                free_filmes(y);
                filmes->filhos[filmes->nChaves] = NULL;
                filmes->nChaves--;
                if (!filmes->nChaves)
                {
                    No *temp = filmes;
                    filmes = filmes->filhos[0];
                    temp->filhos[0] = NULL;
                    free_filmes(temp);
                }
                else
                    filmes->filhos[i - 1] = z;
                filmes = retirar_filme_helper(filmes, titulo, t, p);
                return filmes;
            }
        }
    }
    filmes->filhos[i] = retirar_filme_helper(filmes->filhos[i], titulo, t, p);
    return filmes;
}

No *retirar_filme(No *filmes, char titulo[81], int ano, int t)
{
    Filme *p = buscar_filme(filmes, titulo, ano);
    if (!p || !filmes)
    {
        printf("Filme não encontrado\n");
        return filmes;
    }
    filmes = retirar_filme_helper(filmes, titulo, t, p);
    printf("Filme removido\n");
    return filmes;
}

No *retirar_diretor(No *filmes, char diretor[51], int t) {
    if (!filmes) return NULL;


    int i=0;
    while(filmes && i < filmes->nChaves) {
        if (filmes->chave[i] != NULL && strcmp(filmes->chave[i]->diretor, diretor) == 0) {
            filmes = retirar_filme(filmes, filmes->chave[i]->titulo, filmes->chave[i]->ano, t);
            i--;
        }
    }

    if(filmes) {
        for (int j = 0; j < filmes->nChaves; j++) {
            if (filmes->filhos[j] != NULL) {
                if (filmes->filhos[j]) filmes->filhos[j] = retirar_diretor(filmes->filhos[j], diretor, t);
            }
            filmes->filhos[filmes->nChaves] = retirar_diretor(filmes->filhos[filmes->nChaves], diretor, t);
        }
    }
    return filmes;
}

No *retirar_genero(No *filmes, char genero[31], int t)
{
    if (!filmes)
        return NULL;

    for (int i = 0; i < filmes->nChaves; i++)
    {
        if (strstr(filmes->chave[i]->genero, genero) != NULL)
        {
            filmes = retirar_filme(filmes, filmes->chave[i]->titulo, filmes->chave[i]->ano, t);
            i--;
        }
    }

    for (int j = 0; j < filmes->nChaves + 1; j++)
    {
        filmes->filhos[j] = retirar_genero(filmes->filhos[j], genero, t);
    }

    return filmes;
}

No *retirar_franquia(No *filmes, char franquia[81], int t) {
    if (!filmes)
        return NULL;


    int i=0;
    while(filmes && i < filmes->nChaves) {
        if (filmes->chave[i] != NULL && strstr(filmes->chave[i]->titulo, franquia) != NULL) {
            printf("----------------removendo: %s\n", filmes->chave[i]->titulo);
            filmes = retirar_filme(filmes, filmes->chave[i]->titulo, filmes->chave[i]->ano, t);
            i--;
        }
    }

    if(filmes) {
        for (int j = 0; j < filmes->nChaves; j++) {
            if (filmes->filhos[j] != NULL) {
                //printf("descendo em: %s\n", filmes->chave[j]->titulo);
                if (filmes->filhos[j]) filmes->filhos[j] = retirar_franquia(filmes->filhos[j], franquia, t);
            }
            filmes->filhos[filmes->nChaves] = retirar_franquia(filmes->filhos[filmes->nChaves], franquia, t);
        }
    }
    return filmes;
}

void imp_rec(No *a, int andar){
    if(a){
        int i,j;
        for(i=0; i<=a->nChaves-1; i++){
            imp_rec(a->filhos[i],andar+1);
            for(j=0; j<=andar; j++) printf("\t");
            printf("%d\n", a->chave[i]->id);
        }
        imp_rec(a->filhos[i],andar+1);
    }
}

//No* retirar_franquia(No* filmes, char franquia[81], int t) {
//
//    if (!filmes) return NULL;
//    int i = 0;
//    while (filmes && i < filmes->nChaves) {
//        printf("inicio da recursao\n");
//        if(filmes->filhos[i]) filmes->filhos[i] = retirar_franquia(filmes->filhos[i], franquia, t);
//        printf("final da recursao\n");
//        printf("inicio da recursao do irmao mais a direita\n");
//        if(filmes->filhos[filmes->nChaves]) filmes->filhos[filmes->nChaves] = retirar_franquia(filmes->filhos[filmes->nChaves], franquia, t);
//        printf("saida da recursao do irmao mais a direita\n");
//        i++;
//    }
//
//    int j =0;
//    while (j < filmes->nChaves) {
//        printf("%s", filmes->chave[j]->titulo);
//    if (filmes->chave[j] && strstr(filmes->chave[j]->titulo, franquia) != NULL) {
//            printf("filme %s a ser removido\n", filmes->chave[j]->titulo);
//            filmes = retirar_filme(filmes, filmes->chave[j]->titulo, filmes->chave[j]->ano, t);
//            j--;
//            printf("filme removido\n");
//        }
//        j++;
//
//    }
//    printf("pre retorno");
//    return filmes;
//}




void imprimeId(No *filmes) {
    if(!filmes) return;

    int i=0;
    while(i<filmes->nChaves) {
        if(filmes->filhos[i]) imprimeId(filmes->filhos[i]);
        printf("%s %d\n", filmes->chave[i]->titulo, filmes->chave[i]->id);
        i++;
    }

    if(filmes->filhos[i]) imprimeId(filmes->filhos[i]);
}





#endif