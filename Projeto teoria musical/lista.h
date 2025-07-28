#ifndef LISTA_H
#define LISTA_H

#define TAM_EMAIL 80
#define TAM_SENHA 30
#define TAM_NOME 50

typedef struct Usuario {
    char email[TAM_EMAIL];
    char senha[TAM_SENHA];
} Usuario;

typedef struct Escala {
    char nome[TAM_NOME];
    char formula[20];
    char notas[100];
} Escala;

typedef struct UsuarioNode {
    Usuario dado;
    struct UsuarioNode* prox;
} UsuarioNode;

typedef struct EscalaNode {
    Escala dado;
    struct EscalaNode* prox;
} EscalaNode;

extern UsuarioNode* listaUsuarios;
extern EscalaNode* listaEscalas;
extern int totalUsuarios;
extern int totalEscalas;
extern Usuario usuarioLogado;

void adicionarUsuario(Usuario u);
void adicionarEscala(Escala e);
UsuarioNode* buscarUsuario(char email[]);
EscalaNode* buscarEscalaPorNome(char nome[]);
void liberarListaUsuarios();
void liberarListaEscalas();

#endif
