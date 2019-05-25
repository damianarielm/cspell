#include <stdio.h> // printf, fopen, fclose
#include <assert.h> // assert
#include <string.h> // strcpy
#include <stdlib.h> // malloc
#include <fcntl.h> // open
#include <unistd.h> // close, dup
#include <locale.h> // setlocale

#include "tablahash.h"
#include "cadena.h"
#include "sugerencias.h"

#define DICTIONARY "listado-general.txt"

TablaHash* crearDiccionario(char* fileName) {
    // Validamos la entrada
    assert(fileName);

    // Creamos la tabla hash
    TablaHash* tabla = TablaHashCrear(HASH_SIZE, djb2, sdbm);

    // Recorremos el archivo y agregamos las palabras
    FILE* file = fopen(fileName, "r"); assert(file);
    wchar_t leido[WORD_LEN];
    for (int i = 0; (leido[i] = fgetwc(file)) != WEOF; i++)
        if (leido[i] == L'\n' || leido[i] == L'\r') {
            leido[i] = L'\0';
            if (i) {
                String palabra = malloc(sizeof(wchar_t) * ++i); assert(palabra);
                TablaHashInsertar(tabla, wcscpy(palabra, leido));
            }
            i = -1;
        }
    fclose(file);

    return tabla;
}

void main(int argc, char** argv) {
    // Chequeamos la sintaxis
    if (argc != 3) {
        printf("Uso correcto: %s archivoEntrada archivoSalida.\n", argv[0]);
        return;
    }

    // Redireccionamos la salida estandar
    if (strcmp(argv[2], "stdout")) {
        close(1);
        open(argv[2], O_WRONLY|O_CREAT, 0666);
    }

    setlocale(LC_ALL, "");

    // Creamos el diccionario
    TablaHash* t = crearDiccionario(DICTIONARY);

    // Leemos la entrada al mismo tiempo que buscamos errores
    FILE* file = fopen(argv[1], "r"); assert(file);
    wchar_t palabra[WORD_LEN]; unsigned lineNumber = 1;
    for (int i = 0; (palabra[i] = fgetwc(file)) != WEOF; i++)
        if (isDelimiter(palabra[i])) {
            if (palabra[i] == L'\n') lineNumber++;
            palabra[i] = L'\0'; toLower(palabra);
            if (i) chequearPalabra(palabra, lineNumber, t);
            i = -1;
        }
    fclose(file);

    TablaHashDestruir(t);
}
