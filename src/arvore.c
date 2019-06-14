#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

#define D 5 /* depende de TipoChave */

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
        if (k == t->NO.NExterno.Chave)
            printf("Elemento encontrado\n");
        else printf("Elemento nao encontrado\n");
        return;
    }
    if (Bit(t->NO.NInterno.Index, k) == 0)
        Pesquisa(k, t->NO.NInterno.Esq);
    else
        Pesquisa(k, t->NO.NInterno.Dir);
}

TipoArvore InsereEntre(TipoChave k, TipoRegistro r, TipoArvore *t, int i) {
    TipoArvore p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) {
        /* cria um novo no externo */
        p = CriaNoExt(k, r);
        if (Bit(i, k) == 1)
            return (CriaNoInt(i, t, &p));
        else return (CriaNoInt(i, &p, t));
    } else {
        if (Bit((*t)->NO.NInterno.Index, k) == 1)
            (*t)->NO.NInterno.Dir = InsereEntre(k, r, &(*t)->NO.NInterno.Dir, i);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, r, &(*t)->NO.NInterno.Esq, i);
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
            if (Bit(p->NO.NInterno.Index, k) == 1)
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
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
