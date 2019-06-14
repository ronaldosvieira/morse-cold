#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

TipoArvore ConstruirArvore() {
    FILE *arquivo;
    char* linha = NULL;
    size_t tamanho = 0;

    // Abre arquivo morse.txt
    arquivo = fopen("src/morse.txt", "r");

    // Termina a execucao em caso de erro
    if (arquivo == NULL) {
        printf("Erro: morse.txt nao pode ser aberto. Ele existe?\n");
        exit(EXIT_FAILURE);
    }

    TipoArvore arvore = NULL;
    int i;

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
        arvore = Inserir(codigo, simbolo, arvore);
    }

    return arvore;
}

void TraduzirMensagem(char *mensagem, TipoArvore arvore) {
    // Divide a mensagem em letras
    char *codigo = strtok(mensagem, " ");

    // Enquanto houverem letras na mensagem
    while (codigo) {
        // Se for /, imprime espaco
        if (codigo[0] == '/')
            printf(" ");
        else {
            // Traduz a letra
            TipoRegistro simbolo = *Pesquisar(codigo, arvore);

            // Imprime a letra
            printf("%c", simbolo);
        }

        // Obtem proxima letra
        codigo = strtok(NULL, " ");
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    // Constroi a arvore
    TipoArvore arvore = ConstruirArvore();

    char* mensagem = NULL;
    size_t tamanhoDoBuffer = 0;

    // Le cada linha da entrada padrao
    while (getline(&mensagem, &tamanhoDoBuffer, stdin) != -1) {
        int i;

        // Encontra o \n, se estiver presente
        for (i = 0; mensagem[i] != '\n' && i < tamanhoDoBuffer; i++);

        // Substitui o \n por \0
        if (i < tamanhoDoBuffer)
            mensagem[i] = '\0';

        // Traduz a mensagem
        TraduzirMensagem(mensagem, arvore);
    }

    // Se parametro exibir arvore estiver presente
    if (argc == 2 && strcmp(argv[1], "-a") == 0) {
        printf("\n");

        // Imprime a arvore em pre-ordem
        ImprimirArvore(arvore);
    }

    return 0;
}
