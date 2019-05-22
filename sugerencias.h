#ifndef __SUGERENCIAS_H_
#define __SUGERENCIAS_H__

#include "cadena.h"
#include "tablahash.h"

void intercambiarAdyacentes(String s, TablaHash* t);

void eliminarCaracteres(String s, TablaHash* t);

void agregarCaracter(String s, TablaHash* t);

void reemplazarCaracteres(String s, TablaHash* t);

void sugerirPalabra(String s, TablaHash* t);

void chequearPalabra(String s, unsigned ln, TablaHash* t);

#endif
