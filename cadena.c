#include <wctype.h> // towlower
#include <wchar.h> // wcslen

#include "cadena.h"

void toLower(String s) {
    for (unsigned i = 0; s[i]; i++) s[i] = towlower(s[i]);
}

int isDelimiter(wchar_t c) {
    for (unsigned i = 0; i < wcslen(DELIMITADORES); i++)
        if (c == DELIMITADORES[i]) return 1;
    return 0;
}
