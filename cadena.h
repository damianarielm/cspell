#ifndef __CADENA_H__
#define __CADENA_H__

#define WORD_LEN 30
#define DELIMITADORES " \n:;,.!?"
#define ESPECIALES L"áéíóúüñ"

typedef unsigned char* String;

void toLower(String s);

int isDelimiter(char c);

#endif
