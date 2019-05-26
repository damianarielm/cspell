#include <assert.h> // assert
#include <wchar.h> // wcslen, wcscpy, wmemmove, wcstok
#include <malloc.h> // malloc

#include "cadena.h"
#include "sugerencias.h"

void intercambiarAdyacentes(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (int i = 0; i < wcslen(palabra) - 1; i++) {
        wchar_t sugerencia[wcslen(palabra) + 1];
        wcscpy(sugerencia, palabra);

        // Intercambio de caracteres
        wchar_t c = sugerencia[i];
        sugerencia[i] = sugerencia[i+1];
        sugerencia[i+1] = c;

        sugerirPalabra(sugerencia, t);
    }
}

void eliminarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < wcslen(palabra); i++) {
        wchar_t sugerencia[wcslen(palabra) + 1];
        wcscpy(sugerencia, palabra);

        wmemmove(&sugerencia[i], &sugerencia[i+1], wcslen(sugerencia) - i);

        sugerirPalabra(sugerencia, t);
    }
}

void agregarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < wcslen(palabra); i++) {
        for (unsigned j = 0; ALFABETO[j]; j++) {
            wchar_t sugerencia[wcslen(palabra) + 1];
            wcscpy(sugerencia, palabra);

            // Separamos la cadena y agregamos el caracter
            wmemmove(&sugerencia[i+1], &sugerencia[i], wcslen(sugerencia) - i);
            sugerencia[i] = ALFABETO[j];

            sugerirPalabra(sugerencia, t);
        }
    }
}

void agregarEspacios(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 1; i < wcslen(palabra); i++) {
        wchar_t sugerencia[wcslen(palabra) + 2];
        wcscpy(sugerencia, palabra);

        // Separamos las palabras
        wmemmove(&sugerencia[i+1], &sugerencia[i], wcslen(sugerencia) - i + 1);
        sugerencia[i] = L'\0';

        if (TablaHashBuscar(t, sugerencia) != -1)
            if (TablaHashBuscar(t, &sugerencia[i+1]) != -1) {
                sugerencia[i] = L' ';
                wprintf(L"%ls, ", sugerencia);
            }
    }
}

void reemplazarCaracteres(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    for (unsigned i = 0; i < wcslen(palabra); i++)
        for (unsigned j = 0; ALFABETO[j]; j++) {
            wchar_t sugerencia[wcslen(palabra) + 1];
            wcscpy(sugerencia, palabra);

            // Reemplazamos el caracter actual
            sugerencia[i] = ALFABETO[j];

            sugerirPalabra(sugerencia, t);
        }
}

void sugerirPalabra(String palabra, TablaHash* t) {
    // Validamos la entrada
    assert(palabra && t);

    if (TablaHashBuscar(t, palabra) != -1) wprintf(L"%ls, ", palabra);
}

void chequearPalabra(String s, unsigned lineNumber, TablaHash* t) {
    // Validamos la entrada
    assert(s && t);

    if (TablaHashBuscar(t, s) == -1) {
        wprintf(L"Linea %d, %ls no esta en el diccionario.\n", lineNumber, s);
        wprintf(L"Quizas quizo decir: ");
        intercambiarAdyacentes(s, t);
        eliminarCaracteres(s, t);
        agregarCaracteres(s, t);
        reemplazarCaracteres(s, t);
        agregarEspacios(s, t);
        wprintf(L"\n");
    }
}
