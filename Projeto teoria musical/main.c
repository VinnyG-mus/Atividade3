#include "funcoes.h"
#include "usuario.h"
#include "escala.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    carregarDados();

    if (totalUsuarios == 0) {
        printf("Nenhum usuario cadastrado. Criando usuario padrao...\n");
        Usuario admin;
        strcpy(admin.email, "admin@teoriamestre.com");
        strcpy(admin.senha, "admin123");
        adicionarUsuario(admin);
        salvarUsuariosArquivo();
    }

    while (!fazerLogin());

    mensagemBoasVindas();

    int opcao;
    do {
        exibirMenuPrincipal();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: gerenciarEscalas(); break;
        case 2: gerarEscalaTonica(); break;
        case 3: identificarAcordesEscala(); break;
        case 4: analisarIntervalo(); break;
        case 5: compararModos(); break;
        case 6: gerarCirculoQuintas(); break;
        case 7: printf("Saindo do sistema...\n"); break;
        default: printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);

    salvarDados();
    
    liberarListaUsuarios();
    liberarListaEscalas();
    if (vetorEscalas) free(vetorEscalas);

    return 0;
}
