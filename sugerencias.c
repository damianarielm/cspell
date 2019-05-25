#include <assert.h> // assert
#include <stdio.h> // printf
#include <string.h> // strlen, strcpy, memmove
#include <malloc.h> // malloc, NULL

#include "sugerencias.h"

void intercambiarAdyacentes(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (int i = 0; i < (int) strlen(palabra); i++) {
        char sugerencia[strlen(palabra)];
        strcpy(sugerencia, palabra);

        // Intercambio de caracteres
        char c = sugerencia[i];
        sugerencia[i] = sugerencia[i+1];
        sugerencia[i+1] = c;

        sugerirPalabra(sugerencia, t);
    }
}

void eliminarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra); i++) {
        char sugerencia[strlen(palabra)];
        strcpy(sugerencia, palabra);

        memmove(&sugerencia[i], &sugerencia[i+1], strlen(sugerencia) - i);

        sugerirPalabra(sugerencia, t);
    }
}

void agregarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra); i++) {
        for (unsigned char j = 'a'; j != 'z' + 1; j++) {
            char sugerencia[strlen(palabra) + 1];
            strcpy(sugerencia, palabra);

            // Separamos la cadena y agregamos el caracter
            memmove(&sugerencia[i+1], &sugerencia[i], strlen(sugerencia) - i);
            sugerencia[i] = j;

            sugerirPalabra(sugerencia, t);
        }
    }
}

void agregarEspacios(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 1; i < strlen(palabra); i++) {
        char sugerencia[strlen(palabra) + 1];
        strcpy(sugerencia, palabra);

        // Separamos las palabras
        memmove(&sugerencia[i+1], &sugerencia[i], strlen(sugerencia) - i + 1);
        sugerencia[i] = ' ';

        // Tokenizamos y buscamos en el diccionario
        String token = malloc(sizeof(char) * strlen(palabra));
        strcpy(token, sugerencia); String temp = token;
        if (TablaHashBuscar(t, strtok(token, " ")) != -1)
            if (TablaHashBuscar(t, strtok(NULL, " ")) != -1)
                printf("%s, ", sugerencia);
        free(temp);
    }
}

void reemplazarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra); i++)
        for (unsigned j = 'a'; j != 'z' + 1; j++) {
            char sugerencia[strlen(palabra)];
            strcpy(sugerencia, palabra);

            sugerencia[i] = j;

            sugerirPalabra(sugerencia, t);
        }
}

void sugerirPalabra(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    if (TablaHashBuscar(t, palabra) != -1) printf("%s, ", palabra);
}

void chequearPalabra(String s, unsigned lineNumber, TablaHash* t) {
    // Validamos la entrada
    assert(s && t);

    if (TablaHashBuscar(t, s) == -1) {
        printf("Linea %d, \"%s\" no esta en el diccionario.\n", lineNumber, s);
        printf("Quizas quizo decir: ");
        intercambiarAdyacentes(s, t);
        eliminarCaracteres(s, t);
        agregarCaracteres(s, t);
        reemplazarCaracteres(s, t);
        agregarEspacios(s, t);
        printf("\n");
    }
}
