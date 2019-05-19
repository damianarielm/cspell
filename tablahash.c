#include <stdio.h> // printf
#include <stdlib.h> // malloc, NULL
#include "tablahash.h"

TablaHash* TablaHashCrear(unsigned c, FuncionHash f) {
    // Creamos la estructura
    TablaHash* tablahash = malloc(sizeof(TablaHash));
    tablahash->tabla = malloc(sizeof(String) * c);
    tablahash->capacidad = c;
    tablahash->nElementos = 0;
    tablahash->hash = f;
    tablahash->eliminadas = malloc(sizeof(int) * c);

    // Inicializamos la tabla
    for (unsigned i = 0; i < c; i++) {
        tablahash->tabla[i] = NULL;
        tablahash->eliminadas[i] = 0;
    }

    return tablahash;
}

void TablaHashImprimir(TablaHash* t) {
    for (unsigned i = 0; i < t->capacidad; i++)
        if (t->tabla[i] != NULL) printf("[%d] `%s`.\n", i, t->tabla[i]);
}

void TablaHashInsertar(TablaHash* t, String s) {
    // Comprobamos el factor de carga
    if (t->nElementos / t->capacidad > MAX_LOAD)
        TablaHashRedimensionar(t);

    // Calculamos la posicion ideal
    unsigned i = t->hash(s) % t->capacidad;

    // Sondeo lineal
    while (t->tabla[i] != NULL) i = (i + 1) % t->capacidad;

    // Almacenamos los datos
    t->tabla[i] = s;
    t->nElementos++;
}

int TablaHashBuscar(TablaHash* t, String s) {
    return 0;
}

void TablaHashEliminar(TablaHash* t, String s) {
    return;
}

void TablaHashRedimensionar(TablaHash* t) {
    return;
}

void TablaHashDestruir(TablaHash* t) {
    return;
}
