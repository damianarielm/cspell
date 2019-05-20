#include <stdio.h> // printf, fopen, fclose
#include <assert.h> // assert
#include <string.h> // strtok
#include <stdlib.h> // malloc

#include "tablahash.h"
#include "cadena.h"

#define DICTIONARY "listado-general.txt"

TablaHash* crearDiccionario(String fileName) {
    // Validamos la entrada
    assert(fileName);

    // Creamos la tabla hash
    TablaHash* tabla = TablaHashCrear(HASH_SIZE, djb2);

    // Recorremos el archivo y agregamos las palabras
    FILE* file = fopen(fileName, "r"); assert(file);
    for (unsigned i = 0; !feof(file); i++) {
        String palabra = malloc(sizeof(char) * MAX_WORD_LEN); assert(palabra);
        fgets(palabra, MAX_WORD_LEN, file); strtok(palabra, "\n\r");
        TablaHashInsertar(tabla, palabra);
    }
    fclose(file);

    return tabla;
}

void sugerirPalabras(String palabra) {
    // COMPLETAR
    return;
}

void chequearPalabra(String palabra, int lineNumber, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    if (TablaHashBuscar(t, palabra) == -1) {
        printf("Linea %d, \"%s\" no esta en el diccionario.\n", lineNumber, palabra);
        sugerirPalabras(palabra);
    }
}

void main(int argc, char** argv) {
    // Chequeamos la sintaxis
    if (argc != 3) {
        printf("Uso correcto: %s archivoEntrada archivoSalida.\n", argv[0]);
    } else {
        // Creamos el diccionario
        TablaHash* t = crearDiccionario(DICTIONARY);

        // Leemos la entrada al mismo tiempo que buscamos errores
        FILE* file = fopen(argv[1], "r"); assert(file);
        char palabra[MAX_WORD_LEN]; unsigned lineNumber = 1;
        for (int i = 0; (palabra[i] = fgetc(file)) != EOF; i++) {
            if (isDelimiter(palabra[i])) {
                if (palabra[i] == '\n') lineNumber++;
                palabra[i] = '\0'; toLower(palabra);
                chequearPalabra(palabra, lineNumber, t);
                i = -1;
            }
        }
        fclose(file);

        TablaHashDestruir(t);
    }
}
