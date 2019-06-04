#ifndef __SUGERENCIAS_H_
#define __SUGERENCIAS_H__

#include "cadena.h"
#include "tablahash.h"

int intercambiarAdyacentes(String s, TablaHash* t, String* a, String* b);

int eliminarCaracteres(String s, TablaHash* t, String* a, String* b);

int agregarCaracter(String s, TablaHash* t, String* a, String* b);

int reemplazarCaracteres(String s, TablaHash* t, String* a, String* b);

int agregarEspacios(String s, TablaHash* t, String* b);

int sugerirPalabra(String s, TablaHash* t, String* b);

void chequearPalabra(String s, unsigned ln, TablaHash* t);

#endif
