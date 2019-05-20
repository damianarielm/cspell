#include <stdio.h> // printf
#include <stdlib.h> // malloc, NULL
#include <string.h> // strcmp
#include <assert.h> // assert

#include "tablahash.h"

// http://www.cse.yorku.ca/~oz/hash.html
unsigned long djb2(String string) {
    // Validamos la entrada
    assert(string);

    unsigned long hash = 5381; int c;
    while (c = *string++) hash = ((hash << 5) + hash) + c;

    return hash;
}

TablaHash* TablaHashCrear(unsigned c, FuncionHash f) {
    // Validamos la entrada
    assert(c && f);

    // Creamos la estructura
    TablaHash* t = malloc(sizeof(TablaHash)); assert(t);
    t->tabla = malloc(sizeof(String) * c); assert(t->tabla);
    t->capacidad = c;
    t->nElementos = 0;
    t->hash = f;
    t->eliminadas = malloc(sizeof(unsigned) * c); assert(t->eliminadas);

    // Inicializamos la tabla
    for (unsigned i = 0; i < c; i++) {
        t->tabla[i] = NULL;
        t->eliminadas[i] = 0;
    }

    return t;
}

void TablaHashImprimir(TablaHash* t) {
    // Validamos la entrada
    assert(t);

    // Imprimimos
    for (unsigned i = 0; i < t->capacidad; i++)
        if (t->tabla[i]) printf("[%d] `%s`.\n", i, t->tabla[i]);
}

int TablaHashCasilleroVacio(TablaHash* t, unsigned i) {
    // Validamos la entrada
    assert(t);

    // El casillero esta vacio si es NULL y no esta eliminado
    return !t->tabla[i] && !t->eliminadas[i];
}

void TablaHashInsertar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t && s);

    // Comprobamos el factor de carga
    if (t->nElementos / t->capacidad > MAX_LOAD) TablaHashRedimensionar(t);

    // Calculamos la posicion ideal
    unsigned idx = t->hash(s) % t->capacidad;

    // Sondeo lineal
    while (t->tabla[idx]) idx = ++idx % t->capacidad;

    // Almacenamos los datos
    t->tabla[idx] = s;
    t->eliminadas[idx] = 0;
    t->nElementos++;
}

int TablaHashBuscar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t && s);

    // Calculamos la posicion ideal
    unsigned idx = t->hash(s) % t->capacidad;

    // Comparamos la palabra y hacemos el sondeo
    while (!TablaHashCasilleroVacio(t, idx)) {
        if (t->tabla[idx] && !strcmp(s, t->tabla[idx])) return idx;
        idx = ++idx % t->capacidad;
    }

    // Si todo fallo, la palabra no esta
    return -1;
}

void TablaHashEliminar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t && s);

    // Buscamos la palabra
    int i = TablaHashBuscar(t, s);

    // Si encontramos la palabra, la eliminamos
    if (i != -1) {
        t->tabla[i] = NULL;
        t->eliminadas[i] = 1;
        t->nElementos--;
    }
}

void TablaHashRedimensionar(TablaHash* t) {
    // Validamos la entrada
    assert(t);

    // COMPLETAR
    return;
}

void TablaHashDestruir(TablaHash* t) {
    // Validamos la entrada
    assert(t);

    // Borramos las cadenas
    for (unsigned i = 0; i < t->capacidad; i++) free(t->tabla[i]);

    // Borramos el resto
    free(t->tabla);
    free(t->eliminadas);
    free(t);
}
