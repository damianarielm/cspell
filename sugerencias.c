#include <assert.h> // assert
#include <wchar.h>  // wcslen, wcscpy, wmemmove, wcstok
#include <malloc.h> // malloc

#include "cabeceras/cadena.h"
#include "cabeceras/sugerencias.h"

int intercambiarAdyacentes(String palabra, TablaHash* t, String* a, String* b) {
    // Validamos la entrada
    assert(palabra && t && b);

    int sugerencias = 0;
    for (int i = 0; i < wcslen(palabra) - 1; i++) {
        wchar_t sugerencia[wcslen(palabra) + 1];
        wcscpy(sugerencia, palabra);

        // Intercambio de caracteres
        wchar_t c = sugerencia[i];
        sugerencia[i] = sugerencia[i + 1];
        sugerencia[i + 1] = c;

        if (a) wcscpy(a[i], sugerencia);
        sugerencias += sugerirPalabra(sugerencia, t, b);
    }

    return sugerencias;
}

int eliminarCaracteres(String palabra, TablaHash* t, String* a, String* b) {
    // Validamos la entrada
    assert(palabra && t && b);

   int sugerencias = 0;
   for (unsigned i = 0; i < wcslen(palabra); i++) {
        wchar_t sugerencia[wcslen(palabra) + 1];
        wcscpy(sugerencia, palabra);

        wmemmove(&sugerencia[i], &sugerencia[i + 1], wcslen(sugerencia) - i);

        if (a) wcscpy(a[i], sugerencia);
        sugerencias += sugerirPalabra(sugerencia, t, b);
    }

    return sugerencias;
}

int agregarCaracteres(String palabra, TablaHash* t, String* a, String* b) {
    // Validamos la entrada
    assert(palabra && t && b);

    int sugerencias = 0;
    for (unsigned i = 0; i < wcslen(palabra) + 1; i++) {
        for (unsigned j = 0; ALFABETO[j]; j++) {
            wchar_t sugerencia[wcslen(palabra) + 2];
            wcscpy(sugerencia, palabra);

            // Separamos la cadena y agregamos el caracter
            wmemmove(&sugerencia[i + 1], &sugerencia[i], wcslen(sugerencia) - i + 1);
            sugerencia[i] = ALFABETO[j];
            if (a) wcscpy(a[j + wcslen(ALFABETO) * i], sugerencia);

            sugerencias += sugerirPalabra(sugerencia, t, b);
        }
    }

    return sugerencias;
}

int agregarEspacios(String palabra, TablaHash* t, String* b) {
    // Validamos la entrada
    assert(palabra && t && b);

    int sugerencias = 0;
    for (unsigned i = 1; i < wcslen(palabra); i++) {
        wchar_t sugerencia[wcslen(palabra) + 2];
        wcscpy(sugerencia, palabra);

        // Separamos las palabras
        wmemmove(&sugerencia[i+1], &sugerencia[i], wcslen(sugerencia) - i + 1);
        sugerencia[i] = L'\0';

        if (TablaHashBuscar(t, sugerencia) != -1)
            if (TablaHashBuscar(t, &sugerencia[i + 1]) != -1) {
                sugerencias++;
                sugerencia[i] = L' ';
                wprintf(L"%ls, ", sugerencia);
            }
    }

    return sugerencias;
}

int reemplazarCaracteres(String palabra, TablaHash* t, String* a, String* b) {
    // Validamos la entrada
    assert(palabra && t && b);

    int sugerencias = 0;
    for (unsigned i = 0; i < wcslen(palabra); i++)
        for (unsigned j = 0; ALFABETO[j]; j++) {
            wchar_t sugerencia[wcslen(palabra) + 1];
            wcscpy(sugerencia, palabra);

            // Reemplazamos el caracter actual
            sugerencia[i] = ALFABETO[j];
            if (a) wcscpy(a[j + wcslen(ALFABETO) * i], sugerencia);

            sugerencias += sugerirPalabra(sugerencia, t, b);
        }

    return sugerencias;
}

int sugerirPalabra(String palabra, TablaHash* t, String* b) {
    // Validamos la entrada
    assert(palabra && t && b);

    if (TablaHashBuscar(t, palabra) != -1 && !enArreglo(palabra, b)) {
        wprintf(L"%ls, ", palabra);
        arregloAgregar(palabra, b);
        return 1;
    }

    return 0;
}

void chequearPalabra(String s, unsigned lineNumber, TablaHash* t) {
    // Validamos la entrada
    assert(s && t);

    // Buscamos la palabra actual
    int sugerencias = 0;
    if (TablaHashBuscar(t, s) == -1) {
        wprintf(L"Linea %d, %ls no esta en el diccionario. ", lineNumber, s);
        if (wcslen(s) < MAXLONGITUD) {
            int intercambios = wcslen(s) - 1;
            int eliminaciones = wcslen(s);
            int agregados = (wcslen(s) + 1) * wcslen(ALFABETO);
            int reemplazos = wcslen(s) * wcslen(ALFABETO);
            int total = intercambios + eliminaciones + agregados + reemplazos;

            // Arreglos para guardar palabras sugeridas y del primer nivel
            String nivel1[total]; String sugeridas[total+1];
            for (int i = 0; i < total; i++) {
                nivel1[i] = malloc(sizeof(wchar_t) * LONGITUD); assert(nivel1[i]);
                sugeridas[i] = malloc(sizeof(wchar_t) * LONGITUD); assert(sugeridas[i]);
                sugeridas[i][0] = L'\0';
            }
            sugeridas[total] = NULL;

            // Primer nivel
            wprintf(L"Quizas quizo decir:\n(1) ");
            sugerencias += intercambiarAdyacentes(s, t, nivel1, sugeridas);
            sugerencias += eliminarCaracteres(s, t, &nivel1[intercambios], sugeridas);
            sugerencias += agregarCaracteres(s, t, &nivel1[intercambios+eliminaciones], sugeridas);
            sugerencias += reemplazarCaracteres(s, t, &nivel1[intercambios+eliminaciones+agregados], sugeridas);
            sugerencias += agregarEspacios(s, t, sugeridas);

            // Segundo nivel
            if (sugerencias < MINSUGERENCIAS) wprintf(L"\n(2) ");
            for (int i = 0; i < total && sugerencias < MINSUGERENCIAS; i++)
                sugerencias += eliminarCaracteres(nivel1[i], t, NULL, sugeridas);
            for (int i = 0; i < total && sugerencias < MINSUGERENCIAS; i++)
                sugerencias += intercambiarAdyacentes(nivel1[i], t, NULL, sugeridas);
            for (int i = 0; i < total && sugerencias < MINSUGERENCIAS; i++)
                sugerencias += reemplazarCaracteres(nivel1[i], t, NULL, sugeridas);
            for (int i = 0; i < total && sugerencias < MINSUGERENCIAS; i++)
                sugerencias += agregarCaracteres(nivel1[i], t, NULL, sugeridas);
            for (int i = 0; i < total && sugerencias < MINSUGERENCIAS; i++)
                sugerencias += agregarEspacios(nivel1[i], t, sugeridas);
            wprintf(L"\n\n");

            // Liberamos la memoria
            for (int i = 0; i < total; i++) {
                free(nivel1[i]); free(sugeridas[i]);
            }
        } else
            wprintf(L"\n(0) Palabra demasiado grande. Omitiendo sugerencias.\n");
    }
}
