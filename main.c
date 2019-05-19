#include <math.h> // pow
#include <stdio.h> // printf

#include "tablahash.h"

#define HASH_SIZE 10
#define PRIME_NUMBER 31

// https://cp-algorithms.com/string/string-hashing.html
unsigned stringHash(String s) {
    unsigned h = 0;
    for (unsigned i = 0; s[i] != '\0'; i++)
        h += s[i] * pow(PRIME_NUMBER, i);

    return h;
}

void main() {
    TablaHash* t = TablaHashCrear(HASH_SIZE, stringHash);

    TablaHashInsertar(t, "Es");
    TablaHashInsertar(t, "muy");
    TablaHashInsertar(t, "facil");
    TablaHashInsertar(t, "atrapar");
    TablaHashInsertar(t, "custodiando");
    TablaHashInsertar(t, "continuamente");
    TablaHashInsertar(t, "hispanoamericanas");
    TablaHashInsertar(t, "internacionalizadas");
    TablaHashInsertar(t, "anticonstitucionalmente");

    printf("Tabla antes de eliminar:\n");
    TablaHashImprimir(t);

    TablaHashEliminar(t, "Es");
    TablaHashEliminar(t, "facil");
    TablaHashEliminar(t, "atrapar");
    TablaHashEliminar(t, "custodianto");

    printf("Tabla despues de eliminar:\n");
    TablaHashImprimir(t);

    char palabra[30];
    printf("Ingrese la palabra a buscar: "); scanf("%s", palabra);
    printf("La palabra `%s` se encuentra en la posicion %d.\n", palabra, TablaHashBuscar(t, palabra));

    TablaHashDestruir(t);
}
