#include <ctype.h> // tolower

#include "cadena.h"

void toLower(String s) {
    for (unsigned i =0; s[i] != '\0'; i++) s[i] = tolower(s[i]);
}

int isDelimiter(char c) {
    switch (c) {
        case ' ' : return 1;
        case '\n': return 1;
        case '.' : return 1;
        case ':' : return 1;
        case ',' : return 1;
        case '!' : return 1;
        case '?' : return 1;
        default  : return 0;
    }
}
