#ifndef MORSE_COLD_ARVORE_H
#define MORSE_COLD_ARVORE_H

typedef unsigned char TipoChave; /* a definir, dependendo da aplicacao */
typedef char TipoRegistro;
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

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

TipoArvore CriaNoExt(TipoChave k);

void Pesquisa(TipoChave k, TipoArvore t);

TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i);

TipoArvore Insere(TipoChave k, TipoArvore *t);


#endif //MORSE_COLD_ARVORE_H
