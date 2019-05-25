#ifndef __CADENA_H__
#define __CADENA_H__

#include <wchar.h>

#define WORD_LEN 30
#define DELIMITADORES L" \n:;,.!?"
#define ALFABETO L"abcdefghijklmnopqrstuvwxyzáéíóúüñ"

typedef wchar_t* String;

void toLower(String s);

int isDelimiter(wchar_t c);

#endif
