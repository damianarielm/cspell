#include <ctype.h> // tolower

#include "cadena.h"

void toLower(String s) {
    for (unsigned i = 0; s[i]; i++) s[i] = tolower(s[i]);
}

int isDelimiter(char c) {
    switch (c) {
        case ' ' :
        case '\n':
        case ':' :
        case ';' :
        case ',' :
        case '.' :
        case '!' :
        case '?' : return 1;
        default  : return 0;
    }
}
