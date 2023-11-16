// estrutura da Árvore B, dos filmes e as funções
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef structure_h
#define structure_h

typedef struct filme
{
    char* titulo;
    char* diretor;
    char* genero;
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

Filme *criar_filme(char *titulo, int ano, char *diretor, int duracao, char *genero) {
    Filme *novo = (Filme*)malloc(sizeof(Filme));
    novo->titulo = (char*)malloc(sizeof(char)*81);
    novo->titulo = titulo;
    novo->ano = ano;
    novo->diretor = (char*)malloc(sizeof(char)*51);
    novo->diretor = diretor;
    novo->genero = (char*)malloc(sizeof(char)*31);
    novo->genero = genero;
    novo->duracao = duracao;

    return novo;
}


No *inicializar()
{
    return NULL;
}

No *cria(int t)
{
    No* novo = (No*)malloc(sizeof(No));
    novo->nChaves = 0;
    novo->eFolha=1;

    novo->chave = (Filme *)malloc(sizeof(Filme)*(2*t-1));
    novo->filhos = (No**)malloc(sizeof(No*)*t*2);

    int i;
    for(i = 0; i < (t*2); i++) novo->filhos[i] = NULL;
    return novo;
}

void impressao(No *a, int andar){
    if(a){
        int i,j;
        for(i=0; i<=a->nChaves-1; i++){
            impressao(a->filhos[i],andar+1);
            for(j=0; j<=andar; j++) printf("\t");
            printf("%s %d %s %d %s\n", a->chave[i]->titulo, a->chave[i]->ano, a->chave[i]->diretor, a->chave[i]->duracao, a->chave[i]->genero);
        }
        impressao(a->filhos[i],andar+1);
    }
}


No *divisao(No *x, int i, No * y, int t) {
    No *z =cria(t);
    z->nChaves= t - 1;
    z->eFolha = y->eFolha;

    int j;
    for(j=0;j<t-1;j++) {
        z->chave[j] = y->chave[j+t];
    }
    if(y->eFolha == 0){

        for(j=0;j<t;j++){
            z->filhos[j] = y->filhos[j+t];
            y->filhos[j+t] = NULL;
        }
    }

    y->nChaves = t-1;
    for(j=x->nChaves; j>=i; j--) x->filhos[j+1]=x->filhos[j];
    x->filhos[i] = z;
    for(j=x->nChaves; j>=i; j--) x->chave[j] = x->chave[j-1];
    x->chave[i-1] = y->chave[t-1];
    x->nChaves++;
    return x;
}



No *inserir_filme_incompleto(No *filmes, Filme *filme, int t){
    int i = filmes->nChaves-1;

    if(filmes->eFolha){
        while((i>=0) && (strcmp(filme->titulo, filmes->chave[i]->titulo) < 0)){
            filmes->chave[i+1] = filmes->chave[i];
            i--;
        }
        filmes->chave[i+1] = filme;
        filmes->nChaves++;
        return filmes;
    }

    while((i>=0) && (strcmp(filme->titulo, filmes->chave[i]->titulo) < 0)) i--;
    i++;

    if(filmes->filhos[i]->nChaves == ((2*t)-1)){
        filmes = divisao(filmes, (i+1), filmes->filhos[i], t);

        if(strcmp(filme->titulo, filmes->chave[i]->titulo) > 0) i++;
    }
    filmes->filhos[i] = inserir_filme_incompleto(filmes->filhos[i], filme, t);
    return filmes;
}

No *inserir_filme(No *filmes, Filme *filme, int t)
{

    No *novo = cria(t);

    if(!filmes) {
        novo->chave[0] = filme;
        novo->nChaves = 1;
        return novo;
    }

    if(filmes->nChaves == (2*t)-1) {
        novo->nChaves == 0;
        novo->eFolha = 0;
        novo->filhos[0] = filmes;
        novo = divisao(novo, 1, filmes, t);
        novo = inserir_filme_incompleto(filmes, filme, t);
        return novo;
    }

    filmes = inserir_filme_incompleto(filmes, filme, t);
    return filmes;

}

No *retirar_filme(No *filmes, char titulo[81], int ano)
{
}

Filme *buscar_filme(No *filmes, char titulo[81], int ano)
{
    if(!filmes) return NULL;
    int i=0;
    while((i<filmes->nChaves) && (strcmp(filmes->chave[i]->titulo, titulo) < 0))i++;
    //printf("%s", filmes->chave[i]->titulo);
    if(strcmp(filmes->chave[i]->titulo, titulo) == 0) return filmes->chave[i];
    else return buscar_filme(filmes->filhos[i], titulo, ano);
}

void mostrar_filme(No *filmes, char titulo[81], int ano)
{
    // print genero, diretor, duracao - informações SUBORDINADAS
}

No *alterar(No *filmes, char titulo[81], int ano, char cGenero[31], char cDiretor[51], int cDuracao)
{
    // alterar somente as informações SUBORDINADAS - genero, diretor, duracao
}

void filmes_diretor(No *filmes, char diretor[51])
{
    // print dos dados dos filmes com o diretor especificado
}

No *retirar_diretor(No *filmes, char diretor[51])
{
    // retirar todos os filmes com o diretor especificado
}

No *retirar_genero(No *filmes, char genero[31])
{
    // retirar todos os filmes com o genero especificado
}

No *retirar_franquia(No *filmes, char franquia[81])
{
    // retirar todos os filmes com a franquia especificada
}