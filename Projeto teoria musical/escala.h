#ifndef ESCALA_H
#define ESCALA_H

#include "lista.h"

void cadastrarEscala();
void listarEscalas();
void editarEscala();
void excluirEscala();
void salvarEscalasArquivo();
void carregarEscalasArquivo();
void ordenarEscalasParaBusca();
Escala* buscarEscalaBinaria(char* nome);
extern Escala* vetorEscalas;
extern int totalEscalasVetor;

#endif
