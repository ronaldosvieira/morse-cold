#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "arvore.h"

int rand() {return 5;}

void imprimir_arvore_r(TipoArvore a, int nivel) {
    if (a == NULL) return;

    int i;
    for (i = 0; i < nivel; i++)
        printf("\t");

    if (a->Chave != NULL)
        printf("(%s %c)\n", a->Chave, a->Registro);
    else
        printf("( . )\n");

    imprimir_arvore_r(a->Esq, nivel + 1);
    imprimir_arvore_r(a->Dir, nivel + 1);
}

void imprimir_arvore(TipoArvore a) {
    imprimir_arvore_r(a, 0);
}

int main(int argc, char *argv[]) {
    TipoArvore a = NULL;
    int i, j, k, n;

    int min = 32, max = 126;
    TipoChave vetor[95];

    FILE *arquivo;
    char* linha = NULL;
    size_t tamanho = 0;
    ssize_t leu;

    // Abre arquivo morse.txt
    arquivo = fopen("../src/morse.txt", "r");

    // Termina a execucao em caso de erro
    if (arquivo == NULL) {
        printf("Erro: morse.txt nao pode ser aberto. Ele existe?\n");
        return EXIT_FAILURE;
    }

    // Lê cada linha do arquivo
    while (getline(&linha, &tamanho, arquivo) != -1) {
        // Obtem simbolo e codigo
        TipoRegistro simbolo = linha[0];
        TipoChave codigo = (TipoChave) malloc(6 * sizeof(char));

        strcpy(codigo, &linha[2]);

        // Coloca o \0 no lugar do \n no codigo
        for (i = 0; linha[i + 2] != '\n'; i++);

        codigo[i] = '\0';

        // Insere na arvore
        printf("Inserindo %c %s\n", simbolo, codigo);
        a = Inserir(codigo, simbolo, a);
    }

    TipoRegistro *reg = Pesquisa("..-.", a);

    if (reg == NULL)
        printf("Nao foi encontrado\n");
    else
        printf("Foi encontrado\n");

    imprimir_arvore(a);

    // Insere cada chave na arvore
    /*for (i = min; i <= max; i++) {
        c = vetor[i - 32];
        printf("Inserindo chave: %c\n", c);
        a = Insere(c, &a);
    }

    // Gera outra permutacao aleatoria de chaves
    for (i = min; i <= max; i++) {
        k = min + (int) ((float) (max - min) * rand() / (RAND_MAX + 1.0));
        j = min + (int) ((float) (max - min) * rand() / (RAND_MAX + 1.0));
        n = vetor[k - 32];
        vetor[k - 32] = vetor[j - 32];
        vetor[j - 32] = n;
    }

    // Pesquisa cada chave na arvore
    for (i = min; i <= max; i++) {
        c = vetor[i - 32];
        printf("Pesquisando chave: %c\n", c);
        Pesquisa(c, a);
    }*/

    return 0;
}