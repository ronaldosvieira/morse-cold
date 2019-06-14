#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

#define D 4 /* depende de TipoChave */

TipoDib Bit(TipoIndexAmp i, TipoChave k) {
    return k[i];
}

short EExterno(TipoArvore p) {
    /* Verifica se p^ e nodo externo */
    return (p->nt == Externo);
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir) {
    TipoArvore p;
    p = (TipoArvore) malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    return p;
}

TipoArvore CriaNoExt(TipoChave k, TipoRegistro r) {
    TipoArvore p;
    p = (TipoArvore) malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    p->NO.NExterno.Chave = k;
    p->NO.NExterno.Registro = r;
    return p;
}

void Pesquisa(TipoChave k, TipoArvore t) {
    if (EExterno(t)) {
        if (strcmp(k, t->NO.NExterno.Chave) == 0)
            printf("Elemento encontrado\n");
        else
            printf("Elemento nao encontrado\n");

        return;
    }
    TipoIndexAmp bit_at_index = Bit(t->NO.NInterno.Index, k);

    if (bit_at_index == '.')
        Pesquisa(k, t->NO.NInterno.Esq);
    else if (bit_at_index == '-')
        Pesquisa(k, t->NO.NInterno.Dir);
    else
        printf("Erro: bit invalido\n");
}

TipoArvore InsereEntre(TipoChave k, TipoRegistro r, TipoArvore *t, int i) {
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) {
        /* cria um novo no externo */
        p = CriaNoExt(k, r);
        TipoIndexAmp bit_at_index = Bit(i, k);

        if (bit_at_index == '.')
            return (CriaNoInt(i, &p, t));
        else if (bit_at_index == '-')
            return (CriaNoInt(i, t, &p));
        else
            printf("Erro: bit invalido\n");
    } else {
        TipoIndexAmp bit_at_index = Bit((*t)->NO.NInterno.Index, k);

        if (bit_at_index == '.')
            (*t)->NO.NInterno.Esq = InsereEntre(k, r, &(*t)->NO.NInterno.Esq, i);
        else if (bit_at_index == '-')
            (*t)->NO.NInterno.Dir = InsereEntre(k, r, &(*t)->NO.NInterno.Dir, i);
        else
            printf("Erro: bit invalido\n");

        return (*t);
    }
}

TipoArvore Insere(TipoChave k, TipoRegistro r, TipoArvore *t) {
    TipoArvore p;
    int i;

    if (*t == NULL) return (CriaNoExt(k, r));
    else {
        p = *t;
        while (!EExterno(p)) {
            TipoIndexAmp bit_at_index = Bit(p->NO.NInterno.Index, k);

            if (bit_at_index == '.')
                p = p->NO.NInterno.Esq;
            else if (bit_at_index == '-')
                p = p->NO.NInterno.Dir;
            else
                printf("Erro: bit invalido\n");
        }

        /* acha o primeiro bit diferente */
        i = 0;

        while ((i <= D) && (Bit((int) i, k) == Bit((int) i, p->NO.NExterno.Chave)))
            i++;

        if (i > D) {
            printf("Erro: chave ja esta na arvore\n");
            return (*t);
        }
        else
            return (InsereEntre(k, r, t, i));
    }
}
