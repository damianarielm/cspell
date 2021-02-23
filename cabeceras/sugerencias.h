#ifndef __SUGERENCIAS_H_
#define __SUGERENCIAS_H__

#include "cadena.h"
#include "tablahash.h"

int intercambiarAdyacentes(String s, TablaHash* t, String* a, String* b);

int eliminarCaracteres(String s, TablaHash* t, String* a, String* b);

int agregarCaracter(String s, TablaHash* t, String* a, String* b);

int reemplazarCaracteres(String s, TablaHash* t, String* a, String* b);

int agregarEspacios(String s, TablaHash* t, String* b);

// Si la palabra se encuentra en el diccionario y no se encuentra en el
// arreglo de palabras ya sugeridas, entonces la muestra por pantalla y
// la agrega a dicho arreglo. Deuvuelve 1 en tal caso y 0 en caso contrario.
int sugerirPalabra(String s, TablaHash* t, String* b);

void chequearPalabra(String s, unsigned ln, TablaHash* t);

#endif
