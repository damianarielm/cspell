#include "tablahash.h"
#define HASH_SIZE 100000

unsigned hash(String s) { return 0; }

void main() {
    TablaHash* t = TablaHashCrear(HASH_SIZE, hash);

    TablaHashInsertar(t, "Damian");
    TablaHashInsertar(t, "Ariel");
    TablaHashInsertar(t, "Marotte");

    TablaHashImprimir(t);
}
