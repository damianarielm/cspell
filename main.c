#include <stdio.h> // printf, fopen, fclose
#include <assert.h> // assert
#include <string.h> // strtok
#include <stdlib.h> // malloc
#include <fcntl.h> // open
#include <unistd.h> // close, dup

#include "tablahash.h"
#include "cadena.h"
#include "sugerencias.h"

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

void main(int argc, char** argv) {
    // Redireccionamos la salida estandar
    int fileDescriptor = open(argv[2], O_WRONLY|O_CREAT, 0666);
    close(1);
    dup(fileDescriptor);

    // Chequeamos la sintaxis
    if (argc != 3) {
        printf("Uso correcto: %s archivoEntrada archivoSalida.\n", argv[0]);
        return;
    }

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
