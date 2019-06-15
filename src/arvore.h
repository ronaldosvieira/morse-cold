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

// Checa se duas chaves sao iguais
int ChavesSaoIguais(TipoChave chave1, TipoChave chave2);

// Obtem o digito de uma posicao especifica da chave
int ObterDigito(TipoChave chave, int posicao);

// Cria um novo no da arvore com registro
TipoArvore NovoNoComRegistro(TipoChave chave, TipoRegistro registro);

// Cria um novo no vazio na arvore
TipoArvore NovoNoVazio();

// Pesquisa na arvore por uma chave especifica (recursao)
TipoRegistro* PesquisarR(TipoChave k, TipoArvore t, int posicao);

// Pesquisa na arvore por uma chave especifica
TipoRegistro* Pesquisar(TipoChave k, TipoArvore t);

// Insere um registro onde ja existe um
TipoArvore Separar(TipoArvore no1, TipoArvore no2, int posicao);

// Insere um registro na arvore (recursao)
TipoArvore InserirR(TipoChave k, TipoRegistro r, TipoArvore t, int posicao);

// Insere um registro na arvore
TipoArvore Inserir(TipoChave k, TipoRegistro r, TipoArvore t);

// Percorre e imprime a arvore em pre-ordem (recursao)
void ImprimirArvoreR(TipoArvore a, int nivel);

// Percorre e imprime a arvore em pre-ordem
void ImprimirArvore(TipoArvore a);

#endif //MORSE_COLD_ARVORE_H
