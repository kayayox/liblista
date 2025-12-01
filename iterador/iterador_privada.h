#ifndef ITERADOR_PRIVADA_H_INCLUDED
#define ITERADOR_PRIVADA_H_INCLUDED

#include "../include/iterador.h"
#include "../include/lista.h"

struct iterador_s{
    struct nodo_s* nodo;
    struct nodo_s* prev;
    struct nodo_s* actual;
    size_t cont;
    size_t num_nodos;
    size_t tamanio_nodo;
};

#endif // ITERADOR_PRIVADA_H_INCLUDED
