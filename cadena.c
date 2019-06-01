#include <wctype.h> // towlower
#include <wchar.h> // wcslen
#include <assert.h> // assert

#include "cadena.h"

void toLower(String s) {
    assert(s);
    for (unsigned i = 0; s[i]; i++) s[i] = towlower(s[i]);
}

int isDelimiter(wchar_t c) {
    for (unsigned i = 0; i < wcslen(DELIMITADORES); i++)
        if (c == DELIMITADORES[i]) return 1;
    return 0;
}

int enArreglo(String s, String* a) {
    assert(s && a);
    for (int i = 0; a[i] && a[i][0]; i++) if (!wcscmp(a[i], s)) return 1;
    return 0;
}

void arregloAgregar(String s, String* a) {
    assert(s && a);
    for (int i = 0; a[i]; i++)
        if (!a[i][0]) {
            wcscpy(a[i], s); return;
        }

    assert(0);
}
