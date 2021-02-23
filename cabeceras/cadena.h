#ifndef __CADENA_H__
#define __CADENA_H__

#include <wchar.h>

#define LONGITUD 35
#define DELIMITADORES L" \n\r:;,.!?¡¿\"()[]{}"
#define ALFABETO L"abcdefghijklmnopqrstuvwxyzáéíóúüñ"
#define MINSUGERENCIAS 5
#define MAXLONGITUD 20

// Arreglo de caracteres anchos.
typedef wchar_t* String;

// Convierte una cadena a minusculas.
void toLower(String s);

// Determina si un caracter es un delimitador.
int isDelimiter(wchar_t c);

// Determina si una cadena esta en un arreglo.
int enArreglo(String s, String* a);

// Copia una cadena a un arreglo.
void arregloAgregar(String s, String* a);

#endif
