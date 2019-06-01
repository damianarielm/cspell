#ifndef __SUGERENCIAS_H_
#define __SUGERENCIAS_H__

#include "cadena.h"
#include "tablahash.h"

int intercambiarAdyacentes(String s, TablaHash* t, String* a);

int eliminarCaracteres(String s, TablaHash* t, String* a);

int agregarCaracter(String s, TablaHash* t, String* a);

int reemplazarCaracteres(String s, TablaHash* t, String* a);

int sugerirPalabra(String s, TablaHash* t);

void chequearPalabra(String s, unsigned ln, TablaHash* t);

#endif
