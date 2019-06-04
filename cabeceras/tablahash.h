#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "cadena.h"

#define MAX_LOAD 0.7
#define HASH_SIZE 115001
#define WORST_CASE 28

typedef unsigned long (*FuncionHash) (String);

unsigned long djb2(String s);

unsigned long sdbm(String s);

typedef struct {
    String *tabla;
    unsigned capacidad;
    unsigned nElementos;
    FuncionHash hash1;
    FuncionHash hash2;

    unsigned colisiones;
    unsigned peorcaso;
    unsigned rehasheos;
} TablaHash;

TablaHash* TablaHashCrear(unsigned c, FuncionHash f1, FuncionHash f2);

void TablaHashImprimir(TablaHash* t);

void TablaHashInsertar(TablaHash* t, String s);

int TablaHashBuscar(TablaHash* t, String s);

void TablaHashRedimensionar(TablaHash* t);

void TablaHashDestruir(TablaHash* t);

#endif
