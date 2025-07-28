#include "escala.h"
#include "ordenacao.h"
#include "busca.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Escala* vetorEscalas = NULL;
int totalEscalasVetor = 0;

void cadastrarEscala() {
    Escala nova;
    
    printf("\nNome da escala: ");
    lerString(nova.nome, TAM_NOME);

    printf("Formula (ex: T-T-sT-T-T-T-sT): ");
    lerString(nova.formula, 20);

    printf("Notas (separadas por espaco): ");
    lerString(nova.notas, 100);

    adicionarEscala(nova);
    salvarEscalasArquivo();
    printf("Escala cadastrada com sucesso!\n");
}

void listarEscalas() {
    printf("\n--- ESCALAS CADASTRADAS ---\n");
    EscalaNode* atual = listaEscalas;
    int i = 1;
    while (atual != NULL) {
        printf("\n%d. %s\n", i, atual->dado.nome);
        printf("Formula: %s\n", atual->dado.formula);
        printf("Notas: %s\n", atual->dado.notas);
        atual = atual->prox;
        i++;
    }
    if (totalEscalas == 0) {
        printf("Nenhuma escala cadastrada!\n");
    }
}

void editarEscala() {
    listarEscalas();
    if (totalEscalas == 0) return;

    int id;
    printf("\nID da escala a editar: ");
    scanf("%d", &id);
    getchar();

    if (id < 1 || id > totalEscalas) {
        printf("ID invalido!\n");
        return;
    }

    EscalaNode* atual = listaEscalas;
    int cont = 1;
    while (atual != NULL && cont < id) {
        atual = atual->prox;
        cont++;
    }

    if (atual == NULL) {
        printf("Escala nao encontrada!\n");
        return;
    }

    Escala* e = &(atual->dado);
    printf("\nEditar nome [%s]: ", e->nome);
    char input[TAM_NOME];
    lerString(input, TAM_NOME);
    if (strlen(input) > 0) {
        strcpy(e->nome, input);
    }

    printf("Editar formula [%s]: ", e->formula);
    lerString(input, 20);
    if (strlen(input) > 0) {
        strcpy(e->formula, input);
    }

    printf("Editar notas [%s]: ", e->notas);
    lerString(input, 100);
    if (strlen(input) > 0) {
        strcpy(e->notas, input);
    }

    salvarEscalasArquivo();
    printf("Escala atualizada com sucesso!\n");
}

void excluirEscala() {
    listarEscalas();
    if (totalEscalas == 0) return;

    int id;
    printf("\nID da escala a excluir: ");
    scanf("%d", &id);
    getchar();

    if (id < 1 || id > totalEscalas) {
        printf("ID invalido!\n");
        return;
    }

    EscalaNode* atual = listaEscalas;
    EscalaNode* anterior = NULL;
    int cont = 1;

    while (atual != NULL && cont < id) {
        anterior = atual;
        atual = atual->prox;
        cont++;
    }

    if (atual == NULL) {
        printf("Escala nao encontrada!\n");
        return;
    }

    if (anterior == NULL) {
        listaEscalas = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    totalEscalas--;
    salvarEscalasArquivo();
    printf("Escala excluida com sucesso!\n");
}

void salvarEscalasArquivo() {
    FILE* arquivo = fopen("escalas.txt", "w");
    if (arquivo) {
        EscalaNode* atual = listaEscalas;
        while (atual != NULL) {
            fprintf(arquivo, "%s;%s;%s\n", 
                    atual->dado.nome, 
                    atual->dado.formula, 
                    atual->dado.notas);
            atual = atual->prox;
        }
        fclose(arquivo);
    }
}

void carregarEscalasArquivo() {
    FILE* arquivo = fopen("escalas.txt", "r");
    if (arquivo) {
        char linha[200];
        while (fgets(linha, 200, arquivo)) {
            char* nome = strtok(linha, ";");
            char* formula = strtok(NULL, ";");
            char* notas = strtok(NULL, "\n");

            if (nome && formula && notas) {
                Escala e;
                strcpy(e.nome, nome);
                strcpy(e.formula, formula);
                strcpy(e.notas, notas);
                adicionarEscala(e);
            }
        }
        fclose(arquivo);
    }
}

void ordenarEscalasParaBusca() {
    if (vetorEscalas != NULL) {
        free(vetorEscalas);
    }
    
    vetorEscalas = (Escala*)malloc(totalEscalas * sizeof(Escala));
    if (vetorEscalas == NULL) {
        perror("Erro ao alocar memoria");
        exit(1);
    }
    
    EscalaNode* atual = listaEscalas;
    int i = 0;
    while (atual != NULL) {
        vetorEscalas[i] = atual->dado;
        atual = atual->prox;
        i++;
    }
    totalEscalasVetor = i;
    
    if (totalEscalasVetor > 0) {
        mergeSort(vetorEscalas, 0, totalEscalasVetor - 1);
    }
}

Escala* buscarEscalaBinaria(char* nome) {
    if (vetorEscalas == NULL || totalEscalasVetor == 0) {
        ordenarEscalasParaBusca();
    }
    return buscaBinariaRecursiva(vetorEscalas, 0, totalEscalasVetor - 1, nome);
}
