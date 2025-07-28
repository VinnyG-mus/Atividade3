#include "lista.h"
#include <stdlib.h>
#include <string.h>

UsuarioNode* listaUsuarios = NULL;
EscalaNode* listaEscalas = NULL;
int totalUsuarios = 0;
int totalEscalas = 0;
Usuario usuarioLogado;

void adicionarUsuario(Usuario u) {
    UsuarioNode* novo = (UsuarioNode*)malloc(sizeof(UsuarioNode));
    novo->dado = u;
    novo->prox = listaUsuarios;
    listaUsuarios = novo;
    totalUsuarios++;
}

void adicionarEscala(Escala e) {
    EscalaNode* novo = (EscalaNode*)malloc(sizeof(EscalaNode));
    novo->dado = e;
    novo->prox = listaEscalas;
    listaEscalas = novo;
    totalEscalas++;
}

UsuarioNode* buscarUsuario(char email[]) {
    UsuarioNode* atual = listaUsuarios;
    while(atual != NULL) {
        if(strcmp(atual->dado.email, email) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

EscalaNode* buscarEscalaPorNome(char nome[]) {
    EscalaNode* atual = listaEscalas;
    while(atual != NULL) {
        if(strcmp(atual->dado.nome, nome) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void liberarListaUsuarios() {
    UsuarioNode* atual = listaUsuarios;
    while(atual != NULL) {
        UsuarioNode* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    listaUsuarios = NULL;
}

void liberarListaEscalas() {
    EscalaNode* atual = listaEscalas;
    while(atual != NULL) {
        EscalaNode* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    listaEscalas = NULL;
}
