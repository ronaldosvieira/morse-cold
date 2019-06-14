#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

#define D 4 /* depende de TipoChave */

TipoArvore Separa(TipoArvore pNo, TipoArvore pTrieNo, int posicao);

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

TipoRegistro* PesquisaR(TipoChave k, TipoArvore t, int posicao) {
    if (t == NULL) return NULL;

    if (t->Esq == NULL && t->Dir == NULL) {
        if (ChavesSaoIguais(t->Chave, k))
            return &t->Registro;
        else
            return NULL;
    }

    if (posicao > D) return NULL;

    if (ObterDigito(k, posicao) == '.')
        return PesquisaR(k, t->Esq, posicao + 1);
    else if (ObterDigito(k, posicao) == '-')
        return PesquisaR(k, t->Dir, posicao + 1);
    else
        printf("Erro: digito invalido\n");

    return NULL;
}

TipoRegistro* Pesquisa(TipoChave k, TipoArvore t) {
    return PesquisaR(k, t, 0);
}

TipoArvore Separa(TipoArvore no1, TipoArvore no2, int posicao) {
    TipoArvore novo = NovoNoVazio();

    TipoIndexAmp digitoAtual1 = ObterDigito(no1->Chave, posicao);
    TipoIndexAmp digitoAtual2 = ObterDigito(no2->Chave, posicao);

    if (digitoAtual1 == '.' && digitoAtual2 == '.') {
        novo->Esq = Separa(no1, no2, posicao + 1);
    } else if (digitoAtual1 == '-' && digitoAtual2 == '-') {
        novo->Dir = Separa(no1, no2, posicao + 1);
    } else if (digitoAtual1 == '.' && digitoAtual2 == '-') {
        novo->Esq = no1;
        novo->Dir = no2;
    } else if (digitoAtual1 == '-' && digitoAtual2 == '.') {
        novo->Esq = no2;
        novo->Dir = no1;
    }

    return novo;
}

TipoArvore InserirR(TipoChave k, TipoRegistro r, TipoArvore t, int posicao) {
    if (t == NULL) return NovoNoComRegistro(k, r);

    if (t->Esq == NULL && t->Dir == NULL)
        return Separa(NovoNoComRegistro(k, r), t, posicao);

    TipoIndexAmp digitoAtual = ObterDigito(k, posicao);
    if (digitoAtual == '.')
        t->Esq = InserirR(k, r, t->Esq, posicao + 1);
    else if (digitoAtual == '-')
        t->Dir = InserirR(k, r, t->Dir, posicao + 1);
    else
        printf("Erro: digito invalido\n");

    return t;
}

TipoArvore Inserir(TipoChave k, TipoRegistro r, TipoArvore t) {
    return InserirR(k, r, t, 0);
}