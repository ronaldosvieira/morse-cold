#ifndef MORSE_COLD_ARVORE_H
#define MORSE_COLD_ARVORE_H

typedef char* TipoChave;
typedef char TipoRegistro;
typedef char TipoDigito;

typedef struct TipoTrieNo *TipoArvore;
typedef struct TipoTrieNo {
    TipoChave Chave;
    TipoArvore Esq, Dir;
    TipoRegistro Registro;
} TipoTrieNo;

int ChavesSaoIguais(TipoChave chave1, TipoChave chave2);

int ObterDigito(TipoChave chave, int posicao);

TipoArvore NovoNoComRegistro(TipoChave chave, TipoRegistro registro);

TipoArvore NovoNoVazio();

TipoRegistro* PesquisarR(TipoChave k, TipoArvore t, int posicao);

TipoRegistro* Pesquisar(TipoChave k, TipoArvore t);

TipoArvore Separar(TipoArvore no1, TipoArvore no2, int posicao);

TipoArvore InserirR(TipoChave k, TipoRegistro r, TipoArvore t, int posicao);

TipoArvore Inserir(TipoChave k, TipoRegistro r, TipoArvore t);

void ImprimirArvoreR(TipoArvore a, int nivel);

void ImprimirArvore(TipoArvore a);

#endif //MORSE_COLD_ARVORE_H
