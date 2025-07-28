#include "funcoes.h"
#include "escala.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_NOTAS 12

void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    char *pos = strchr(buffer, '\n');
    if (pos) *pos = '\0';
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void carregarDados() {
    carregarUsuariosArquivo();
    carregarEscalasArquivo();
}

void salvarDados() {
    salvarUsuariosArquivo();
    salvarEscalasArquivo();
}

void mensagemBoasVindas() {
    printf("\n========================================\n");
    printf("|  Bem-vindo ao Teoria mestre!  |\n");
    printf("|  Explore escalas, acordes e         |\n");
    printf("|  progressoes harmonicas como nunca! |\n");
    printf("========================================\n\n");
}

void exibirMenuPrincipal() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Gerenciar escalas musicais\n");
    printf("2. Gerar escala a partir de tonica\n");
    printf("3. Identificar acordes de uma escala\n");
    printf("4. Analisar intervalo entre duas notas\n");
    printf("5. Comparar modos musicais\n");
    printf("6. Gerar circulo de quintas\n");
    printf("7. Sair\n");
}

void gerenciarEscalas() {
    int opcao;
    do {
        printf("\n--- GERENCIAMENTO DE ESCALAS ---\n");
        printf("1. Cadastrar nova escala\n");
        printf("2. Listar escalas cadastradas\n");
        printf("3. Editar escala\n");
        printf("4. Excluir escala\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: cadastrarEscala(); break;
        case 2: listarEscalas(); break;
        case 3: editarEscala(); break;
        case 4: excluirEscala(); break;
        case 5: printf("Retornando...\n"); break;
        default: printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
}

void gerarEscalaTonica() {
    char* notas[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    char tonica[5];

    printf("\nDigite a tonica (Utilize somente notas sem acidente ou com sustenido) (ex: C, D#, F): ");
    lerString(tonica, sizeof(tonica));
    toUpperString(tonica);

    int pos = -1;
    int i;
    for (i = 0; i < MAX_NOTAS; i++) {
        if (strcmp(tonica, notas[i]) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Nota invalida!\n");
        return;
    }

    int intervalos[] = { 2, 2, 1, 2, 2, 2, 1 };
    printf("\nEscala maior de %s: ", tonica);
    for (i = 0; i < 7; i++) {
        printf("%s ", notas[pos]);
        pos = (pos + intervalos[i]) % MAX_NOTAS;
    }
    printf("\n");
}

void identificarAcordesEscala() {
    char* notas[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    char* acordes[] = { "I", "ii", "iii", "IV", "V", "vi", "vii°" };
    char tonica[5];

    printf("\nDigite a tonica da escala maior (Utilize somente notas sem acidente ou com sustenido) (ex: C, G, D): ");
    lerString(tonica, sizeof(tonica));
    toUpperString(tonica);

    int pos = -1;
    int i;
    for (i = 0; i < MAX_NOTAS; i++) {
        if (strcmp(tonica, notas[i]) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Nota invalida!\n");
        return;
    }

    int intervalos[] = { 2, 2, 1, 2, 2, 2, 1 };
    int escala[7];
    for (i = 0; i < 7; i++) {
        escala[i] = pos;
        pos = (pos + intervalos[i]) % MAX_NOTAS;
    }

    printf("\nAcordes na escala de %s maior:\n", tonica);
    for (i = 0; i < 7; i++) {
        printf("%s: %s%s\n", acordes[i], notas[escala[i]],
            (i == 0 || i == 3 || i == 4) ? "" : "m");
    }
}

int converterNotaParaNumero(char* nota) {
    char* notas[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    int len = strlen(nota);
    if (len < 2) return -1;
    int oitava = nota[len - 1] - '0';
    if (oitava < 0 || oitava > 9) return -1;
    char nomeNota[4] = { 0 };
    strncpy(nomeNota, nota, len - 1);
    nomeNota[len - 1] = '\0';
    toUpperString(nomeNota);
    int i;
    for (i = 0; i < 12; i++) {
        if (strcmp(nomeNota, notas[i]) == 0) {
            return oitava * 12 + i;
        }
    }
    return -1;
}

void analisarIntervalo() {
    char nota1[10], nota2[10];
    printf("\nDigite a primeira nota (Fale a oitava em que se encontra a nota e utilize somente notas sem acidente ou com sustenido) (ex: C4, F#3, A5): ");
    lerString(nota1, sizeof(nota1));

    printf("Digite a segunda nota (Fale a oitava em que se encontra a nota e utilize somente notas sem acidente ou com sustenido) (ex: C4, F#3, A5): ");
    lerString(nota2, sizeof(nota2));

    int num1 = converterNotaParaNumero(nota1);
    int num2 = converterNotaParaNumero(nota2);

    if (num1 == -1 || num2 == -1) {
        printf("Nota(s) invalida(s)!\n");
        return;
    }

    int diferenca = abs(num1 - num2);
    int oitavas = diferenca / 12;
    int semitons = diferenca % 12;

    char* intervalos[] = {
        "Unissono",
        "Segunda menor",
        "Segunda maior",
        "Terca menor",
        "Terca maior",
        "Quarta justa",
        "Tritono",
        "Quinta justa",
        "Sexta menor",
        "Sexta maior",
        "Setima menor",
        "Setima maior"
    };

    char* nomeIntervalo = (semitons <= 11) ? intervalos[semitons] : "Invalido";

    if (oitavas > 0 && semitons == 0) {
        printf("\nIntervalo entre %s e %s: %d oitava(s) exata(s)\n", nota1, nota2, oitavas);
    }
    else if (semitons == 0) {
        printf("\nIntervalo entre %s e %s: Unissono\n", nota1, nota2);
    }
    else {
        printf("\nIntervalo entre %s e %s: %s (%d semitons)\n",
            nota1, nota2, nomeIntervalo, diferenca);
    }
}

void compararModos() {
    printf("\n--- COMPARACAO DE MODOS GREGOS ---\n");

    printf("\nModo Jonico (Escala Maior): T-T-sT-T-T-T-sT\n");
    printf("Caracteristica: Alegre, estavel, luminoso\n");
    printf("Comparacao: Escala maior tradicional\n");
    printf("Usos comuns: Pop, hinos, musicas felizes ou triunfantes\n");

    printf("\nModo Dorico: T-sT-T-T-T-sT-T\n");
    printf("Caracteristica: Triste com um leve brilho, groove, sofisticado\n");
    printf("Comparacao: Menor com sexta maior\n");
    printf("Usos comuns: Funk, jazz modal, rock progressivo, musica folclorica\n");

    printf("\nModo Frigio: sT-T-T-T-sT-T-T\n");
    printf("Caracteristica: Tenso, sombrio, exotico, misterioso\n");
    printf("Comparacao: Menor com segunda menor\n");
    printf("Usos comuns: Flamenco, metal, trilhas dramaticas\n");

    printf("\nModo Lidio: T-T-T-sT-T-T-sT\n");
    printf("Caracteristica: Sonhador, etereo, esperancoso, flutuante\n");
    printf("Comparacao: Maior com quarta aumentada\n");
    printf("Usos comuns: Musica cinematografica, trilhas epicas, fusion\n");

    printf("\nModo Mixolidio: T-T-sT-T-T-sT-T\n");
    printf("Caracteristica: Alegre com leve tensao, sensacao bluesy\n");
    printf("Comparacao: Maior com setima menor\n");
    printf("Usos comuns: Rock, blues, country, funk\n");

    printf("\nModo Eolio (Escala Menor Natural): T-sT-T-T-sT-T-T\n");
    printf("Caracteristica: Triste, melancolico, introspectivo\n");
    printf("Comparacao: Escala menor natural\n");
    printf("Usos comuns: Baladas, musica emocional, trilhas tristes\n");

    printf("\nModo Locrio: sT-T-T-sT-T-T-T\n");
    printf("Caracteristica: Instavel, caotico, dissonante\n");
    printf("Comparacao: Menor com quinta diminuta\n");
    printf("Usos comuns: Jazz experimental, tensao, pouco usado como tom principal\n");
}

void gerarCirculoQuintas() {
    char* tonalidades[] = {
        "C", "G", "D", "A", "E", "B", "F#", "C#", 
        "G#", "D#", "A#", "F"
    };
    
    char* armaduras[] = {
        "0 sustenidos", "1 sustenido (F#)", "2 sustenidos (F#, C#)", 
        "3 sustenidos (F#, C#, G#)", "4 sustenidos (F#, C#, G#, D#)", 
        "5 sustenidos (F#, C#, G#, D#, A#)", 
        "6 sustenidos (F#, C#, G#, D#, A#, E#)",
        "7 sustenidos (F#, C#, G#, D#, A#, E#, B#)",
        "4 bemois (Bb, Eb, Ab, Db)", "5 bemóis (Bb, Eb, Ab, Db, Gb)",
        "6 bemois (Bb, Eb, Ab, Db, Gb, Cb)", "1 bemol (Bb)"
    };
    
    printf("\n--- CIRCULO DE QUINTAS ---\n");
    int i;
    for (i = 0; i < 12; i++) {
        printf("%s: %s\n", tonalidades[i], armaduras[i]);
    }
}

void toUpperString(char* str) {
	int i;
    for (i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}
