#ifndef __TABLAHASH_H_
#define __TABLAHASH_H_

#define MAX_LOAD 0.7

typedef char* String;

typedef unsigned (*FuncionHash) (String);

typedef struct {
    String *tabla;
    unsigned capacidad;
    unsigned nElementos;
    FuncionHash hash;
    int* eliminadas;
} TablaHash;

TablaHash* TablaHashCrear(unsigned c, FuncionHash f);

void TablaHashImprimir(TablaHash* t);

void TablaHashInsertar(TablaHash* t, String s);

int TablaHashBuscar(TablaHash* t, String s);

void TablaHashEliminar(TablaHash* t, String s);

void TablaHashRedimensionar(TablaHash* t);

void TablaHashDestruir(TablaHash* t);

#endif
