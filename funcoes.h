#ifndef FUNCOES_H
#define FUNCOES_H


#include "assinatura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NoTrie* criar_no() {
    NoTrie* no = (NoTrie*)malloc(sizeof(NoTrie));
    no->fim_da_palavra = false;
    no->contagem = 0;
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        no->filhos[i] = NULL;
    }
    return no;
}

void inserir(NoTrie* raiz, const char* chave) {
    NoTrie* no = raiz;
    while (*chave) {
        int indice = *chave - 'a';
        if (!no->filhos[indice]) {
            no->filhos[indice] = criar_no();
        }
        no = no->filhos[indice];
        chave++;
    }
    no->fim_da_palavra = true;
    no->contagem++;
}

NoTrie* remover_chave(NoTrie* no, const char* chave, int profundidade) {
    if (!no) {
        return NULL;
    }

    if (profundidade == strlen(chave)) {
        if (no->fim_da_palavra) {
            no->fim_da_palavra = false;
        }
        if (no->contagem > 0) {
            no->contagem--;
        }
        if (no->contagem == 0) {
            for (int i = 0; i < TAMANHO_ALFABETO; i++) {
                if (no->filhos[i]) {
                    return no;
                }
            }
            free(no);
            no = NULL;
        }
        return no;
    }

    int indice = chave[profundidade] - 'a';
    no->filhos[indice] = remover_chave(no->filhos[indice], chave, profundidade + 1);

    if (!no->fim_da_palavra && no->contagem == 0) {
        for (int i = 0; i < TAMANHO_ALFABETO; i++) {
            if (no->filhos[i]) {
                return no;
            }
        }
        free(no);
        no = NULL;
    }
    return no;
}

bool buscar(NoTrie* raiz, const char* chave) {
    NoTrie* no = raiz;
    while (*chave) {
        int indice = *chave - 'a';
        if (!no->filhos[indice]) {
            return false;
        }
        no = no->filhos[indice];
        chave++;
    }
    return no && no->fim_da_palavra;
}

void coletar(NoTrie* no, char* prefixo, int nivel) {
    if (no->fim_da_palavra) {
        prefixo[nivel] = '\0';
        printf("  %s  ", prefixo);
    }
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (no->filhos[i]) {
            prefixo[nivel] = i + 'a';
            coletar(no->filhos[i], prefixo, nivel + 1);
        }
    }
}

void imprimir_em_ordem(NoTrie* raiz) {
    char prefixo[100];
    coletar(raiz, prefixo, 0);
}

void maior_prefixo_comum(NoTrie* raiz) {
    NoTrie* no = raiz;
    char prefixo[100];
    int nivel = 0;

    while (no) {
        int contador_filhos = 0;
        NoTrie* proximo_no = NULL;
        for (int i = 0; i < TAMANHO_ALFABETO; i++) {
            if (no->filhos[i]) {
                contador_filhos++;
                proximo_no = no->filhos[i];
            }
        }
        if (contador_filhos != 1) {
            break;
        }
        prefixo[nivel++] = proximo_no - raiz->filhos[0] + 'a';
        no = proximo_no;
    }

    prefixo[nivel] = '\0';
    printf("Maior prefixo comum: %s\n", prefixo);
}

void dfs_chave_mais_frequente(NoTrie* no, char* chave_atual, int nivel, char* resultado, int* max_contagem) {
    if (no->fim_da_palavra && no->contagem > *max_contagem) {
        *max_contagem = no->contagem;
        chave_atual[nivel] = '\0';
        strcpy(resultado, chave_atual);
    }
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (no->filhos[i]) {
            chave_atual[nivel] = i + 'a';
            dfs_chave_mais_frequente(no->filhos[i], chave_atual, nivel + 1, resultado, max_contagem);
        }
    }
}

void chave_mais_frequente(NoTrie* raiz) {
    char chave_atual[100], resultado[100];
    int max_contagem = 0;
    dfs_chave_mais_frequente(raiz, chave_atual, 0, resultado, &max_contagem);
    printf("Chave com maior ocorrencia: %s (ocorrencias: %d)\n", resultado, max_contagem);
}

#endif 