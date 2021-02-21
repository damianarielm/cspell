#include <stdlib.h> // malloc, NULL
#include <wchar.h>  // wcslen, wcscmp
#include <assert.h> // assert

#include "cabeceras/tablahash.h"

// http://www.cse.yorku.ca/~oz/hash.html
unsigned long djb2(String string) {
    // Validamos la entrada
    assert(string);

    unsigned long hash = 5381; int c;
    while (c = *string++) hash = ((hash << 5) + hash) + c;

    return hash;
}

unsigned long sdbm(String string) {
    // Validamos la entrada
    assert(string);

    unsigned long hash = 0; int c;
    while (c = *string++) hash = c + (hash << 6) + (hash << 16) - hash;

    return ++hash;
}

TablaHash* TablaHashCrear(unsigned c, FuncionHash f1, FuncionHash f2) {
    // Validamos la entrada
    assert(c && f1 && f2);

    // Creamos la estructura
    TablaHash* t = malloc(sizeof(TablaHash)); assert(t);
    t->tabla = malloc(sizeof(String) * c); assert(t->tabla);
    t->capacidad = c; t->hash1 = f1; t->hash2 = f2;
    t->nElementos = t->colisiones = t->peorcaso = t->rehasheos = 0;

    // Inicializamos la tabla
    for (unsigned i = 0; i < c; i++) t->tabla[i] = NULL;

    return t;
}

void TablaHashImprimir(TablaHash* t) {
    // Validamos la entrada
    assert(t);

    // Imprimimos los datos
    for (unsigned i = 0; i < t->capacidad; i++)
        if (t->tabla[i]) wprintf(L"[%u] %ls.\n", i, t->tabla[i]);

    // Imprimimos estadisticas
    wprintf(L"Elementos: %d.\n", t->nElementos);
    wprintf(L"Capacidad: %d.\n", t->capacidad);
    wprintf(L"Factor de carga: %f.\n", (float) t->nElementos / t->capacidad);
    wprintf(L"Colisiones: %d.\n", t->colisiones);
    wprintf(L"Peor caso: %d.\n", t->peorcaso);
    wprintf(L"Rehasheos: %d.\n", t->rehasheos);

    // Imprimimos el tamaño de la tabla
    unsigned tamano = sizeof(String) * t->capacidad;
    for (unsigned i = 0; i < t->capacidad; i++)
        if (t->tabla[i])
            tamano += (wcslen(t->tabla[i]) + 1) * sizeof(wchar_t);
    wprintf(L"Tamaño en memoria: %f mb.\n", (float) tamano / 1024 / 1024);
}

void TablaHashInsertar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t && s);

    // Calculamos la posicion ideal
    unsigned i = t->hash1(s) % t->capacidad;

    // Doble hasheo
    int sondeos;
    if (t->tabla[i]) t->colisiones++;
    for (sondeos = 0; t->tabla[i] && sondeos < WORST_CASE; sondeos++)
        i = (i + t->hash2(s)) % t->capacidad;
    if (sondeos > t->peorcaso && sondeos < WORST_CASE) t->peorcaso = sondeos;

    // Almacenamos los datos
    if ((float) t->nElementos / (float) t->capacidad < MAX_LOAD && sondeos < WORST_CASE) {
        assert(!t->tabla[i]); // assert(TablaHashBuscar(t,s) == -1)
        t->tabla[i] = s;
        t->nElementos++;
    } else {
        TablaHashRedimensionar(t);
        TablaHashInsertar(t, s);
    }
}

int TablaHashBuscar(TablaHash* t, String s) {
    // Validamos la entrada
    assert(t && s);

    // Calculamos la posicion ideal
    unsigned idx = t->hash1(s) % t->capacidad;

    // Comparamos la palabra y hacemos el sondeo
    for (int i = 0; i < WORST_CASE && t->tabla[idx]; i++) {
        if (!wcscmp(s, t->tabla[idx])) return idx;
        idx = (idx + t->hash2(s)) % t->capacidad;
    }

    // Si todo fallo, la palabra no esta
    return -1;
}

void TablaHashRedimensionar(TablaHash* t) {
    // Validamos la entrada
    assert(t);

    // Creamos el nuevo arreglo e inicializamos
    String* tnueva = malloc(sizeof(String) * t->capacidad * 2); assert(tnueva);
    for (unsigned i = 0; i < t->capacidad * 2; i++) tnueva[i] = NULL;

    // Conservamos los datos viejos
    String* tvieja = t->tabla;
    unsigned cvieja = t->capacidad;

    // Intercambiamos las tablas
    t->tabla = tnueva;
    t->capacidad = t->capacidad * 2;
    t->nElementos = t->colisiones = t->peorcaso = 0;
    t->rehasheos++;

    // Volvemos a agregar los datos
    for (unsigned i = 0; i < cvieja; i++)
        if (tvieja[i]) TablaHashInsertar(t, tvieja[i]);

    // Destruimos la tabla vieja
    free(tvieja);
}

void TablaHashDestruir(TablaHash* t) {
    // Validamos la entrada
    assert(t);

    // Borramos las cadenas
    for (unsigned i = 0; i < t->capacidad; i++) free(t->tabla[i]);

    // Borramos el resto
    free(t->tabla); free(t);
}
