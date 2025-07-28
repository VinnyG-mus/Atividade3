#ifndef USUARIO_H
#define USUARIO_H

#include "lista.h"

int validarEmail(char email[]);
void cadastrarUsuario();
int fazerLogin();
void salvarUsuariosArquivo();
void carregarUsuariosArquivo();

#endif
