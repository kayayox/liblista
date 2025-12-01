/**
 * @file lista_doble.h
 * @brief Interfaz pública para Lista Doblemente Enlazada
 * @author Soubhi Khayat Najjar kayayox@gmail.com
 * @version 2.0
 *
 * @note Esta implementación ofrece O(1) para operaciones bidireccionales
 * a cambio de mayor uso de memoria por nodo.
 */

#ifndef LISTA_DOBLE_H_INCLUDED
#define LISTA_DOBLE_H_INCLUDED

#pragma once
#include "resultados.h"

/**
 * @typedef lista_doble_t
 * @brief Tipo opaco que representa una lista doblemente enlazada
 */
typedef struct lista_doble_s lista_doble_t;

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
 * @brief Crea una nueva lista doble vacía
 *
 * @param lista Puntero donde se almacenará la lista creada
 * @param tamanio_elemento Tamaño en bytes de cada elemento
 * @return EXITO si se creó correctamente, código de error en caso contrario
 */
resultado_t lista_doble_crear(lista_doble_t** lista, size_t tamanio_elemento);

/**
 * @brief Crea una nueva lista doble con funciones personalizadas
 *
 * @param lista Puntero donde se almacenará la lista creada
 * @param tamanio_elemento Tamaño en bytes de cada elemento
 * @param copiar Función para copiar elementos (NULL para memcpy)
 * @param liberar Función para liberar elementos (NULL para free)
 * @param comparar Función para comparar elementos (NULL para memcmp)
 * @return EXITO si se creó correctamente, código de error en caso contrario
 */
resultado_t lista_doble_crear_avanzado(lista_doble_t** lista, size_t tamanio_elemento,
                                      lista_funcion_copiar copiar,
                                      lista_funcion_liberar liberar,
                                      lista_funcion_comparar comparar);

/**
 * @brief Libera todos los recursos asociados a la lista doble
 *
 * @param lista Puntero a la lista doble a liberar
 * @return EXITO si se liberó correctamente, código de error en caso contrario
 */
resultado_t lista_doble_liberar(lista_doble_t** lista);

/**
 * @brief Inserta un elemento al final de la lista doble
 *
 * @param lista Lista doble donde insertar
 * @param dato Elemento a insertar
 * @return EXITO si se insertó correctamente, código de error en caso contrario
 */
resultado_t lista_doble_insertar_final(lista_doble_t* lista, const void* dato);

/**
 * @brief Inserta un elemento al inicio de la lista doble
 *
 * @param lista Lista doble donde insertar
 * @param dato Elemento a insertar
 * @return EXITO si se insertó correctamente, código de error en caso contrario
 */
resultado_t lista_doble_insertar_inicio(lista_doble_t* lista, const void* dato);

/**
 * @brief Elimina la primera ocurrencia de un valor en la lista doble
 *
 * @param lista Lista doble de donde eliminar
 * @param dato Valor a eliminar
 * @return EXITO si se eliminó, ERROR_ELEMENTO_NO_ENCONTRADO si no existe
 */
resultado_t lista_doble_eliminar_valor(lista_doble_t* lista, const void* dato);

/**
 * @brief Obtiene el número de elementos en la lista doble
 *
 * @param lista Lista doble a consultar
 * @param tamanio Donde se almacenará el tamaño
 * @return EXITO si se obtuvo correctamente, código de error en caso contrario
 */
resultado_t lista_doble_obtener_tamanio(const lista_doble_t* lista, size_t* tamanio);

/**
 * @brief Obtiene el elemento en la cabeza de la lista doble
 *
 * @param lista Lista doble a consultar
 * @param dato_cabeza Donde se almacenará el elemento de la cabeza
 * @return EXITO si se obtuvo, ERROR_LISTA_VACIA si está vacía
 */
resultado_t lista_doble_obtener_cabeza(const lista_doble_t* lista, void** dato_cabeza);

/**
 * @brief Obtiene el elemento en la cola de la lista doble
 *
 * @param lista Lista doble a consultar
 * @param dato_cola Donde se almacenará el elemento de la cola
 * @return EXITO si se obtuvo, ERROR_LISTA_VACIA si está vacía
 */
resultado_t lista_doble_obtener_cola(const lista_doble_t* lista, void** dato_cola);

#endif /// LISTA_DOBLE_H_INCLUDED
