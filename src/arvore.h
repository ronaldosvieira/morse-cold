#ifndef MORSE_COLD_ARVORE_H
#define MORSE_COLD_ARVORE_H

typedef char* TipoChave; /* a definir, dependendo da aplicacao */
typedef char TipoRegistro;
typedef unsigned char TipoIndexAmp;
typedef char TipoDib;

typedef enum {
    Interno, Externo
} TipoNo;

typedef struct TipoPatNo *TipoArvore;
typedef struct TipoPatNo {
    TipoNo nt;
    union {
        struct {
            TipoIndexAmp Index;
            TipoArvore Esq, Dir;
        } NInterno;
        struct {
            TipoChave Chave;
            TipoRegistro Registro;
        } NExterno;
    } NO;
} TipoPatNo;

TipoDib Bit(TipoIndexAmp i, TipoChave k);

short EExterno(TipoArvore p);

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir);

TipoArvore CriaNoExt(TipoChave k, TipoRegistro r);

void Pesquisa(TipoChave k, TipoArvore t);

TipoArvore InsereEntre(TipoChave k, TipoRegistro r, TipoArvore *t, int i);

TipoArvore Insere(TipoChave k, TipoRegistro r, TipoArvore *t);


#endif //MORSE_COLD_ARVORE_H
