#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

#define D 4 /* depende de TipoChave */

int ChavesSaoIguais(TipoChave chave1, TipoChave chave2) {
    return strcmp(chave1, chave2) == 0;
}

int ObterDigito(TipoChave chave, int posicao) {
    return chave[posicao];
}

TipoArvore NovoNoComRegistro(TipoChave chave, TipoRegistro registro) {
    TipoArvore p = (TipoArvore) malloc(sizeof(TipoTrieNo));

    p->Chave = chave;
    p->Registro = registro;

    return p;
}

TipoArvore NovoNoVazio() {
    return (TipoArvore) malloc(sizeof(TipoTrieNo));
}

TipoRegistro* PesquisarR(TipoChave k, TipoArvore t, int posicao) {
    if (t == NULL) return NULL;

    TipoIndexAmp digitoAtual = ObterDigito(k, posicao);

    if (t->Esq == NULL && t->Dir == NULL) {
        if (ChavesSaoIguais(t->Chave, k))
            return &t->Registro;
        else
            return NULL;
    }

    if (posicao > D) return NULL;

    if (digitoAtual == '.')
        return PesquisarR(k, t->Esq, posicao + 1);
    else if (digitoAtual == '-')
        return PesquisarR(k, t->Dir, posicao + 1);
    else if (digitoAtual == '\0')
        if (ChavesSaoIguais(t->Chave, k))
            return &t->Registro;
        else
            return NULL;
    else
        printf("Erro: digito invalido\n");

    return NULL;
}

TipoRegistro* Pesquisar(TipoChave k, TipoArvore t) {
    return PesquisarR(k, t, 0);
}

TipoArvore Separar(TipoArvore no1, TipoArvore no2, int posicao) {
    TipoArvore novo = NovoNoVazio();

    printf("Separar %c de %c\n", no1->Registro, no2->Registro);

    TipoIndexAmp digitoAtual1 = ObterDigito(no1->Chave, posicao);
    TipoIndexAmp digitoAtual2 = ObterDigito(no2->Chave, posicao);

    if (digitoAtual1 == '.' && digitoAtual2 == '.') {
        novo->Esq = Separar(no1, no2, posicao + 1);
    } else if (digitoAtual1 == '-' && digitoAtual2 == '-') {
        novo->Dir = Separar(no1, no2, posicao + 1);
    } else if (digitoAtual1 == '.' && digitoAtual2 == '-') {
        novo->Esq = no1;
        novo->Dir = no2;
    } else if (digitoAtual1 == '-' && digitoAtual2 == '.') {
        novo->Esq = no2;
        novo->Dir = no1;
    } else if (digitoAtual1 == '\0') {
        if (digitoAtual2 == '.')
            no1->Esq = no2;
        else if (digitoAtual2 == '-')
            no1->Dir = no2;

        free(novo);

        novo = no1;
    } else if (digitoAtual2 == '\0') {
        if (digitoAtual1 == '.')
            no2->Esq = no1;
        else if (digitoAtual1 == '-')
            no2->Dir = no1;

        free(novo);

        novo = no2;
    }

    return novo;
}

TipoArvore InserirR(TipoChave k, TipoRegistro r, TipoArvore t, int posicao) {
    if (t == NULL) return NovoNoComRegistro(k, r);

    if (t->Esq == NULL && t->Dir == NULL)
        return Separar(NovoNoComRegistro(k, r), t, posicao);

    TipoIndexAmp digitoAtual = ObterDigito(k, posicao);

    if (digitoAtual == '.')
        t->Esq = InserirR(k, r, t->Esq, posicao + 1);
    else if (digitoAtual == '-')
        t->Dir = InserirR(k, r, t->Dir, posicao + 1);
    else if (digitoAtual == '\0') {
        if (t->Chave == NULL) {
            t->Chave = k;
            t->Registro = r;
        }
    } else
        printf("Erro: digito invalido\n");

    return t;
}

TipoArvore Inserir(TipoChave k, TipoRegistro r, TipoArvore t) {
    return InserirR(k, r, t, 0);
}

void ImprimirArvoreR(TipoArvore a, int nivel) {
    if (a == NULL) return;

    int i;
    for (i = 0; i < nivel; i++)
        printf("\t");

    if (a->Chave != NULL)
        printf("(%s %c)\n", a->Chave, a->Registro);
    else
        printf("( . )\n");

    ImprimirArvoreR(a->Esq, nivel + 1);
    ImprimirArvoreR(a->Dir, nivel + 1);
}

void ImprimirArvore(TipoArvore a) {
    ImprimirArvoreR(a, 0);
}
