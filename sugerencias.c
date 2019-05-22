#include <assert.h> // assert
#include <stdio.h> // printf
#include <string.h> // strlen, strcpy, memmove
#include <malloc.h> // malloc, NULL

#include "sugerencias.h"

void intercambiarAdyacentes(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra) - 1; i++) {
        char temp[strlen(palabra)];
        strcpy(temp, palabra);

        // Intercambio de caracteres
        char c = temp[i];
        temp[i] = temp[i+1];
        temp[i+1] = c;

        sugerirPalabra(temp, t);
    }
}

void eliminarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra); i++) {
        char temp[strlen(palabra)];
        strcpy(temp, palabra);

        memmove(&temp[i], &temp[i+1], strlen(temp) - i);

        sugerirPalabra(temp, t);
    }
}

void agregarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra); i++) {
        for (unsigned j = 'a'; j != 'z' + 1; j++) {
            char temp[strlen(palabra) + 1];
            strcpy(temp, palabra);

            memmove(&temp[i+1], &temp[i], strlen(temp) - i);
            temp[i] = j;

            sugerirPalabra(temp, t);
        }
    }
}

void agregarEspacios(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 1; i < strlen(palabra); i++) {
        char* temp = malloc(sizeof(char) * strlen(palabra));
        strcpy(temp, palabra);

        memmove(&temp[i+1], &temp[i], strlen(temp) - i);
        temp[i] = ' ';
        char temp2[strlen(temp)];
        strcpy(temp2, temp);
        char* temp3 = temp;

        temp = strtok(temp, " ");
        if (TablaHashBuscar(t, temp) != -1) {
            temp = strtok(NULL, " ");
            if (TablaHashBuscar(t, temp) != -1)
                printf("%s, ", temp2);
        }

        free(temp3);
    }
}

void reemplazarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < strlen(palabra); i++) {
        for (unsigned j = 'a'; j != 'z' + 1; j++) {
            char temp[strlen(palabra)];
            strcpy(temp, palabra);

            temp[i] = j;

            sugerirPalabra(temp, t);
        }
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
