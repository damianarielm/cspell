#include <math.h> // pow
#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <string.h> // strtok

#include "tablahash.h"

#define MAX_WORD_LEN 30
#define HASH_SIZE 100000
#define PRIME_NUMBER 31

// https://cp-algorithms.com/string/string-hashing.html
unsigned stringHash(String s) {
    unsigned h = 0;
    for (unsigned i = 0; s[i] != '\0'; i++)
        h += s[i] * pow(PRIME_NUMBER, i);

    return h;
}

TablaHash* leerArchivo(String a) {
    TablaHash* t = TablaHashCrear(HASH_SIZE, stringHash);

    FILE* f = fopen(a, "r");
    for (unsigned i = 0; !feof(f); i++) {
        char* palabra = malloc(sizeof(char) * MAX_WORD_LEN);
        fgets(palabra, MAX_WORD_LEN, f);
        strtok(palabra, "\n\r");
        TablaHashInsertar(t, palabra);
    }
    fclose(f);

    return t;
}

void main() {
    TablaHash* t = leerArchivo("listado-general.txt");
    char palabra[30];
    printf("Ingrese la palabra a buscar: "); scanf("%s", palabra);
    printf("La palabra `%s` se encuentra en la posicion %d.\n", palabra, TablaHashBuscar(t, palabra));

    TablaHashDestruir(t);
}
