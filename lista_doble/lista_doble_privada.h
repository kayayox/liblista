/**
 * @file lista_doble_privada.h
 * @brief Definiciones privadas para Lista Doblemente Enlazada
 * @author Soubhi Khayat Najjar kayayox@gmail.com
 * @version 2.0
 *
 * @note Este archivo solo debe ser incluido en los archivos de implementación
 * No exponer estas estructuras al usuario final.
 */

#ifndef LISTA_DOBLE_PRIVADA_H_INCLUDED
#define LISTA_DOBLE_PRIVADA_H_INCLUDED

#include "../include/lista_doble.h"
#include "../include/verificaciones.h"
#include <stdlib.h>
#include <string.h>

/**
 * @struct nodo_doble_s
 * @brief Nodo interno de la lista doblemente enlazada
 *
 * @var nodo_doble_s::dato Puntero a los datos almacenados
 * @var nodo_doble_s::siguiente Puntero al siguiente nodo en la lista
 * @var nodo_doble_s::anterior Puntero al nodo anterior en la lista
 */
struct nodo_doble_s{
    void* dato;
    struct nodo_doble_s* siguiente;
    struct nodo_doble_s* anterior;
};

/**
 * @struct lista_doble_s
 * @brief Estructura interna de la lista doblemente enlazada
 *
 * @var lista_doble_s::cabeza Puntero al primer nodo de la lista
 * @var lista_doble_s::cola Puntero al último nodo de la lista
 * @var lista_doble_s::cantidad_elementos Número de elementos en la lista
 * @var lista_doble_s::tamanio_elemento Tamaño en bytes de cada elemento
 * @var lista_doble_s::copiar_dato Función personalizada para copiar datos
 * @var lista_doble_s::liberar_dato Función personalizada para liberar datos
 * @var lista_doble_s::comparar_dato Función personalizada para comparar datos
 */
struct lista_doble_s{
    struct nodo_doble_s* cabeza;
    struct nodo_doble_s* cola;
    size_t cantidad_elementos;
    size_t tamanio_elemento;
    lista_funcion_copiar copiar_dato;
    lista_funcion_liberar liberar_dato;
    lista_funcion_comparar comparar_dato;
};

/**
 * @brief Crea un nuevo nodo doble para la lista
 *
 * @param lista Lista doble donde se insertará el nodo
 * @param dato Dato a almacenar en el nodo
 * @return Puntero al nodo creado, NULL si hay error
 */
struct nodo_doble_s* lista_doble_crear_nodo(lista_doble_t* lista,const void* dato);

/**
 * @brief Encuentra el nodo que contiene un valor específico
 *
 * @param lista Lista doble donde buscar
 * @param dato Valor a buscar
 * @return Puntero al nodo encontrado, NULL si no se encuentra
 */
struct nodo_doble_s* lista_doble_buscar_nodo(const lista_doble_t* lista,const void* dato);

#endif /// LISTA_DOBLE_PRIVADA_H_INCLUDED
