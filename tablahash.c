#include <stdio.h> // printf
#include <stdlib.h> // malloc, NULL
#include <string.h> // strcmp
#include <assert.h> // assert

#include "tablahash.h"

TablaHash* TablaHashCrear(unsigned c, FuncionHash f) {
    // Validamos la entrada
    assert(c != 0 && f != NULL);

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
    // Validamos la entrada
    assert(t != NULL);

    // Imprimimos
    for (unsigned i = 0; i < t->capacidad; i++)
        if (t->tabla[i] != NULL) printf("[%d] `%s`.\n", i, t->tabla[i]);
}

int TablaHashCasilleroVacio(TablaHash* t, unsigned i) {
    // Validamos la entrada
    assert(t != NULL);

    // El casillero esta vacio si es NULL y no esta eliminado
    return t->tabla[i] == NULL && !t->eliminadas[i];
}

void TablaHashInsertar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t != NULL && s != NULL);

    // Comprobamos el factor de carga
    if (t->nElementos / t->capacidad > MAX_LOAD)
        TablaHashRedimensionar(t);

    // Calculamos la posicion ideal
    unsigned i = t->hash(s) % t->capacidad;

    // Sondeo lineal
    while (t->tabla[i] != NULL) i = (i + 1) % t->capacidad;

    // Almacenamos los datos
    t->tabla[i] = s;
    t->eliminadas[i] = 0;
    t->nElementos++;
}

int TablaHashBuscar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t != NULL && s != NULL);

    // Calculamos la posicion ideal
    unsigned i = t->hash(s) % t->capacidad;

    // Comparamos la palabra y hacemos el sondeo
    while (!TablaHashCasilleroVacio(t, i)) {
        if (t->tabla[i] != NULL && !strcmp(s, t->tabla[i])) return i;
        i++;
    }

    // Si todo fallo, la palabra no esta
    return -1;
}

void TablaHashEliminar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t != NULL && s != NULL);

    // Buscamos la palabra
    int i = TablaHashBuscar(t, s);

    // Si no se encuentra, no se hace nada
    if (i == -1) return;

    // De lo contrario, eliminamos la palabra
    t->tabla[i] = NULL;
    t->eliminadas[i] = 1;
    t->nElementos--;
}

void TablaHashRedimensionar(TablaHash* t) {
    return;
}

void TablaHashDestruir(TablaHash* t) {
    free(t->tabla);
    free(t->eliminadas);
    free(t);
}
