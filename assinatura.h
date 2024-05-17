#ifndef ASSINATURA_H
#define ASSINATURA_H

#include <stdbool.h>

#define TAMANHO_ALFABETO 26

typedef struct NoTrie {
    struct NoTrie* filhos[TAMANHO_ALFABETO];
    bool fim_da_palavra;
    int contagem; // Para rastrear a ocorrência de uma chave
} NoTrie;

// Função para criar um novo nó da Trie
NoTrie* criar_no();

// Função para inserir uma chave na Trie
void inserir(NoTrie* raiz, const char* chave);

// Função para remover uma chave da Trie
NoTrie* remover_chave(NoTrie* no, const char* chave, int profundidade);

// Função para buscar uma chave na Trie
bool buscar(NoTrie* raiz, const char* chave);

// Função para imprimir palavras em ordem alfabética
void imprimir_em_ordem(NoTrie* raiz);

// Função para encontrar o maior prefixo comum
void maior_prefixo_comum(NoTrie* raiz);

// Função para encontrar a chave com maior ocorrência
void chave_mais_frequente(NoTrie* raiz);

#endif // ASSINATURA_H
