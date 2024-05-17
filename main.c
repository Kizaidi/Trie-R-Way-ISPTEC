#include "assinatura.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

void menu(NoTrie* raiz) {
    int opcao;
    char chave[100];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir chave\n");
        printf("2. Remover chave\n");
        printf("3. Buscar chave\n");
        printf("4. Imprimir em ordem\n");
        printf("5. Maior prefixo comum\n");
        printf("6. Chave com maior ocorrencia\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave para inserir: ");
                scanf("%s", chave);
                inserir(raiz, chave);
                break;
            case 2:
                printf("Digite a chave para remover: ");
                scanf("%s", chave);
                raiz = remover_chave(raiz, chave, 0);
                break;
            case 3:
                printf("Digite a chave para buscar: ");
                scanf("%s", chave);
                if (buscar(raiz, chave)) {
                    printf("Chave encontrada.\n");
                } else {
                    printf("Chave nao encontrada.\n");
                }
                break;
            case 4:
                printf("Palavras em ordem alfabetica:\n");
                imprimir_em_ordem(raiz);
                break;
            case 5:
                maior_prefixo_comum(raiz);
                break;
            case 6:
                chave_mais_frequente(raiz);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 7);
}

int main() {
    NoTrie* raiz = criar_no();
    menu(raiz);
    return 0;
}
