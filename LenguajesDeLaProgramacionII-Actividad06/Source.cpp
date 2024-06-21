#include "FuncionesComparadoras.h"

bool CompP(CProducto* a, CProducto* b) {
    return a->getPrecio() < b->getPrecio();
}

bool CompN(CProducto* a, CProducto* b) {
    return a->getNombre() < b->getNombre();
}