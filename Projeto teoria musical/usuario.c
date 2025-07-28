#include "usuario.h"
#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validarEmail(char email[]) {
    if (strchr(email, '@') == NULL) {
        printf("Email invalido: deve conter '@'\n");
        return 0;
    }

    if (strlen(email) >= TAM_EMAIL) {
        printf("Email invalido: maximo de %d caracteres\n", TAM_EMAIL - 1);
        return 0;
    }

    if (buscarUsuario(email) != NULL) {
        printf("Email ja cadastrado\n");
        return 0;
    }

    return 1;
}

void cadastrarUsuario() {
    Usuario novo;
    printf("\n--- CADASTRO DE USUARIO ---\n");

    do {
        printf("Email: ");
        lerString(novo.email, TAM_EMAIL);
    } while (!validarEmail(novo.email));

    printf("Senha: ");
    lerString(novo.senha, TAM_SENHA);

    adicionarUsuario(novo);
    salvarUsuariosArquivo();
    printf("Usuario cadastrado com sucesso!\n");
}

int fazerLogin() {
    char email[TAM_EMAIL];
    char senha[TAM_SENHA];
    int tentativas = 0;

    printf("\n=== LOGIN ===\n");
    printf("1. Fazer login\n");
    printf("2. Cadastrar novo usuario\n");
    printf("Escolha: ");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    if (opcao == 2) {
        cadastrarUsuario();
    }

    while (1) {
        printf("\nEmail: ");
        lerString(email, TAM_EMAIL);

        printf("Senha: ");
        lerString(senha, TAM_SENHA);

        UsuarioNode* usuarioEncontrado = buscarUsuario(email);
        if (usuarioEncontrado != NULL && strcmp(senha, usuarioEncontrado->dado.senha) == 0) {
            usuarioLogado = usuarioEncontrado->dado;
            return 1;
        }

        printf("Credenciais invalidas! Tente novamente.\n");
        tentativas++;

        if (tentativas >= 3) {
            printf("Numero maximo de tentativas excedido.\n");
            return 0;
        }
    }
}

void salvarUsuariosArquivo() {
    FILE* arquivo = fopen("usuarios.txt", "w");
    if (arquivo) {
        UsuarioNode* atual = listaUsuarios;
        while (atual != NULL) {
            fprintf(arquivo, "%s;%s\n", atual->dado.email, atual->dado.senha);
            atual = atual->prox;
        }
        fclose(arquivo);
    }
}

void carregarUsuariosArquivo() {
    FILE* arquivo = fopen("usuarios.txt", "r");
    if (arquivo) {
        char linha[TAM_EMAIL + TAM_SENHA + 3];
        while (fgets(linha, sizeof(linha), arquivo)) {
            char* email = strtok(linha, ";");
            char* senha = strtok(NULL, "\n");

            if (email && senha) {
                Usuario u;
                strcpy(u.email, email);
                strcpy(u.senha, senha);
                adicionarUsuario(u);
            }
        }
        fclose(arquivo);
    }
}
