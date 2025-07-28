#include "busca.h"
#include <string.h>

Escala* buscaBinariaRecursiva(Escala arr[], int inicio, int fim, char* nome) {
    if (fim >= inicio) {
        int meio = inicio + (fim - inicio) / 2;
        
        int cmp = strcmp(nome, arr[meio].nome);
        
        if (cmp == 0) return &arr[meio];
        if (cmp < 0) return buscaBinariaRecursiva(arr, inicio, meio - 1, nome);
        return buscaBinariaRecursiva(arr, meio + 1, fim, nome);
    }
    return NULL;
}
