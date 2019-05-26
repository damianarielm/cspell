#include <stdio.h>  // fopen, fclose
#include <wchar.h>  // wprintf
#include <assert.h> // assert
#include <string.h> // strcmp
#include <stdlib.h> // malloc
#include <unistd.h> // close
#include <locale.h> // setlocale

#include "tablahash.h"
#include "cadena.h"
#include "sugerencias.h"

#define DICTIONARY "listado-general.txt"

TablaHash* crearDiccionario(char* fileName) {
    // Validamos la entrada
    assert(fileName);

    // Creamos la tabla hash
    TablaHash* t = TablaHashCrear(HASH_SIZE, djb2, sdbm);

    // Recorremos el archivo y agregamos las palabras
    FILE* file = fopen(fileName, "r"); assert(file);
    wchar_t leido[LONGITUD];
    for (int i = 0; (leido[i] = fgetwc(file)) != WEOF; i++)
        if (isDelimiter(leido[i])) {
            leido[i] = L'\0';
            if (i) {
                assert(i < LONGITUD);
                String palabra = malloc(sizeof(wchar_t) * ++i); assert(palabra);
                TablaHashInsertar(t, wcscpy(palabra, leido));
            }
            i = -1;
        }
    fclose(file);

    return t;
}

void main(int argc, char** argv) {
    // Chequeamos la sintaxis
    if (argc != 3) {
        wprintf(L"Uso correcto: %s archivoEntrada archivoSalida.\n", argv[0]);
        return;
    }

    // Redireccionamos la salida estandar
    if (strcmp(argv[2], "stdout")) {
        close(1);
        fopen(argv[2], "w");
    }

    // Configuracion de idioma
    setlocale(LC_ALL, "");

    // Creamos el diccionario
    TablaHash* t = crearDiccionario(DICTIONARY);

    // Leemos la entrada al mismo tiempo que buscamos errores
    FILE* file = fopen(argv[1], "r"); assert(file);
    wchar_t palabra[LONGITUD]; unsigned lineNumber = 1;
    for (int i = 0; (palabra[i] = fgetwc(file)) != WEOF; i++)
        if (isDelimiter(palabra[i])) {
            if (palabra[i] == L'\n') lineNumber++;
            palabra[i] = L'\0'; toLower(palabra); assert(i < LONGITUD);
            if (i) chequearPalabra(palabra, lineNumber, t);
            i = -1;
        }
    fclose(file);

    TablaHashDestruir(t);
}
