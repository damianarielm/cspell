#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "cadena.h"

#define MAX_LOAD 0.7
#define HASH_SIZE 115001
#define MAX_WORD_LEN 30

typedef unsigned long (*FuncionHash) (String);

unsigned long djb2(String s);

typedef struct {
    String *tabla;
    unsigned capacidad;
    unsigned nElementos;
    FuncionHash hash;
    unsigned* eliminadas;
} TablaHash;

TablaHash* TablaHashCrear(unsigned c, FuncionHash f);

void TablaHashImprimir(TablaHash* t);

int TablaHashCasilleroVacio(TablaHash* t, unsigned i);

void TablaHashInsertar(TablaHash* t, String s);

int TablaHashBuscar(TablaHash* t, String s);

void TablaHashEliminar(TablaHash* t, String s);

void TablaHashRedimensionar(TablaHash* t);

void TablaHashDestruir(TablaHash* t);

#endif
