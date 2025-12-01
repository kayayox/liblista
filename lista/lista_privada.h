#ifndef LISTA_PRIVADA_H_INCLUDED
#define LISTA_PRIVADA_H_INCLUDED

#include "../include/lista.h"

struct lista_s{
    struct nodo_s* cabeza;
    struct nodo_s* cola;
    size_t cantidad_elementos;
    size_t tamanio_elemento;
    lista_funcion_copiar copiar_dato;
    lista_funcion_liberar liberar_dato;
    lista_funcion_comparar comparar_dato;
};

struct nodo_s{
    void* dato;
    struct nodo_s* siguiente;
};

struct nodo_s* crear_nodo_s(lista_t* lista,const void* dato);

#endif /// LISTA_PRIVADA_H_INCLUDED
