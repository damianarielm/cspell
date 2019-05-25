#include <ctype.h> // tolower
#include <string.h> // strlen

#include "cadena.h"

void toLower(String s) {
    for (unsigned i = 0; s[i]; i++) s[i] = tolower(s[i]);
}

int isDelimiter(char c) {
    for (unsigned i = 0; i < strlen(DELIMITADORES); i++)
        if (c == DELIMITADORES[i]) return 1;
    return 0;
}
