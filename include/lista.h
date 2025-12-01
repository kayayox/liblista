/**
 * @file lista.h
 * @brief Interfaz pública para la estructura de datos Lista Enlazada
 * @author Soubhi Khayat Najjar kayayox@gmail.com
 * @version 1.0
 */

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#pragma once
#include "resultados.h"

/**
 * @typedef lista_t
 * @brief Tipo opaco que representa una lista enlazada
 */
typedef struct lista_s lista_t;

/**
 * @struct nodo_s
 * @brief Nodo interno de la lista (definición privada)
 */
struct nodo_s;

/**
 * @typedef lista_funcion_copiar
 * @brief Función para copiar datos personalizados
 */
typedef void* (*lista_funcion_copiar)(const void* dato);

/**
 * @typedef lista_funcion_liberar
 * @brief Función para liberar datos personalizados
 */
typedef void (*lista_funcion_liberar)(void* dato);

/**
 * @typedef lista_funcion_comparar
 * @brief Función para comparar datos personalizados
 */
typedef int (*lista_funcion_comparar)(const void* a, const void* b);

/**
 * @brief Crea una nueva lista vacía
 *
 * @param lista Puntero donde se almacenará la lista creada
 * @param tamanio_elemento Tamaño en bytes de cada elemento
 * @return EXITO si se creó correctamente, código de error en caso contrario
 */
resultado_t lista_crear(lista_t** lista, size_t tamanio_elemento);

/**
 * @brief Crea una nueva lista con funciones personalizadas
 *
 * @param lista Puntero donde se almacenará la lista creada
 * @param tamanio_elemento Tamaño en bytes de cada elemento
 * @param copiar Función para copiar elementos (NULL para memcpy)
 * @param liberar Función para liberar elementos (NULL para free)
 * @param comparar Función para comparar elementos (NULL para memcmp)
 * @return EXITO si se creó correctamente, código de error en caso contrario
 */
resultado_t lista_crear_avanzado(lista_t** lista, size_t tamanio_elemento,
                                lista_funcion_copiar copiar,
                                lista_funcion_liberar liberar,
                                lista_funcion_comparar comparar);

/**
 * @brief Establece funciones personalizadas para una lista existente
 *
 * @param lista Lista a configurar
 * @param copiar Función para copiar elementos (NULL para memcpy)
 * @param liberar Función para liberar elementos (NULL para free)
 * @param comparar Función para comparar elementos (NULL para memcmp)
 * @return EXITO si se configuró correctamente, código de error en caso contrario
 */
resultado_t lista_establecer_funciones(lista_t* lista,
                                      lista_funcion_copiar copiar,
                                      lista_funcion_liberar liberar,
                                      lista_funcion_comparar comparar);

/**
 * @brief Libera todos los recursos asociados a la lista
 *
 * @param lista Puntero a la lista a liberar
 * @return EXITO si se liberó correctamente, código de error en caso contrario
 */
resultado_t lista_liberar(lista_t** lista);

/**
 * @brief Inserta un elemento al final de la lista
 *
 * @param lista Lista donde insertar
 * @param dato Elemento a insertar
 * @return EXITO si se insertó correctamente, código de error en caso contrario
 */
resultado_t lista_insertar_final(lista_t* lista, const void* dato);

/**
 * @brief Inserta un elemento al inicio de la lista
 *
 * @param lista Lista donde insertar
 * @param dato Elemento a insertar
 * @return EXITO si se insertó correctamente, código de error en caso contrario
 */
resultado_t lista_insertar_inicio(lista_t* lista, const void* dato);

/**
 * @brief Elimina la primera ocurrencia de un valor en la lista
 *
 * @param lista Lista de donde eliminar
 * @param dato Valor a eliminar
 * @return EXITO si se eliminó, ERROR_ELEMENTO_NO_ENCONTRADO si no existe
 */
resultado_t lista_eliminar_valor(lista_t* lista, const void* dato);

/**
 * @brief Obtiene el número de elementos en la lista
 *
 * @param lista Lista a consultar
 * @param tamanio Donde se almacenará el tamaño
 * @return EXITO si se obtuvo correctamente, código de error en caso contrario
 */
resultado_t lista_obtener_tamanio(const lista_t* lista, size_t* tamanio);

/**
 * @brief Obtiene el elemento en la cabeza de la lista
 *
 * @param lista Lista a consultar
 * @param dato_cabeza Donde se almacenará el elemento de la cabeza
 * @return EXITO si se obtuvo, ERROR_LISTA_VACIA si está vacía
 */
resultado_t lista_obtener_cabeza(const lista_t* lista, void** dato_cabeza);

/**
 * @brief Obtiene el nodo cabeza de la lista (uso interno)
 *
 * @param lista Lista a consultar
 * @param nodo_cabeza Donde se almacenará el nodo cabeza
 * @return EXITO si se obtuvo, ERROR_LISTA_VACIA si está vacía
 */
resultado_t lista_obtener_nodo_cabeza(const lista_t* lista, void** nodo_cabeza);

#endif /// LISTA_H_INCLUDED
