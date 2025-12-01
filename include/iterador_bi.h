/**
 * @file iterador_bi.h
 * @brief Interfaz pública para Iterador Bidireccional de Lista Doble
 * @author Soubhi Khayat Najjar kayayox@gmail.com
 * @version 2.0
 *
 * @note Este iterador ofrece operaciones O(1) en ambas direcciones
 * y debe usarse exclusivamente con listas doblemente enlazadas.
 */

#ifndef ITERADOR_BI_H_INCLUDED
#define ITERADOR_BI_H_INCLUDED

#pragma once
#include "resultados.h"
#include "lista_doble.h"

/**
 * @typedef iterador_bi_t
 * @brief Tipo opaco que representa un iterador bidireccional
 */
typedef struct iterador_bi_s iterador_bi_t;

/**
 * @typedef iterador_bi_funcion_mapear
 * @brief Función para transformar elementos (map)
 */
typedef void (*iterador_bi_funcion_mapear)(const void* elemento, void* resultado);

/**
 * @typedef iterador_bi_funcion_filtrar
 * @brief Función para filtrar elementos (filter)
 */
typedef bool (*iterador_bi_funcion_filtrar)(const void* elemento);

/**
 * @typedef iterador_bi_funcion_reducir
 * @brief Función para reducir elementos (reduce)
 */
typedef void (*iterador_bi_funcion_reducir)(const void* elemento, void* acumulador);

/**
 * @brief Crea un nuevo iterador bidireccional para una lista doble
 *
 * @param lista Lista doble sobre la que iterar
 * @param iterador Donde se almacenará el iterador creado
 * @return EXITO si se creó correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_crear(const lista_doble_t* lista, iterador_bi_t** iterador);

/**
 * @brief Libera los recursos del iterador bidireccional
 *
 * @param iterador Iterador bidireccional a liberar
 * @return EXITO si se liberó correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_liberar(iterador_bi_t** iterador);

/**
 * @brief Avanza al siguiente elemento y lo obtiene
 *
 * @param iterador Iterador bidireccional a avanzar
 * @param elemento Donde se almacenará el elemento actual
 * @return EXITO si se avanzó, ERROR_ITERADOR_FINALIZADO si no hay más elementos
 */
resultado_t iterador_bi_siguiente(iterador_bi_t* iterador, void* elemento);

/**
 * @brief Retrocede al elemento anterior y lo obtiene (OPERACIÓN RÁPIDA O(1))
 *
 * @param iterador Iterador bidireccional a retroceder
 * @param elemento Donde se almacenará el elemento actual
 * @return EXITO si se retrocedió, ERROR_ITERADOR_FINALIZADO si no hay elementos anteriores
 */
resultado_t iterador_bi_anterior(iterador_bi_t* iterador, void* elemento);

/**
 * @brief Verifica si hay más elementos hacia adelante
 *
 * @param iterador Iterador bidireccional a verificar
 * @param tiene_siguiente Donde se almacenará el resultado
 * @return EXITO si se verificó correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_tiene_siguiente(const iterador_bi_t* iterador, bool* tiene_siguiente);

/**
 * @brief Verifica si hay más elementos hacia atrás (OPERACIÓN RÁPIDA O(1))
 *
 * @param iterador Iterador bidireccional a verificar
 * @param tiene_anterior Donde se almacenará el resultado
 * @return EXITO si se verificó correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_tiene_anterior(const iterador_bi_t* iterador, bool* tiene_anterior);

/**
 * @brief Obtiene el elemento actual sin avanzar el iterador
 *
 * @param iterador Iterador bidireccional a consultar
 * @param elemento Donde se almacenará el elemento actual
 * @return EXITO si se obtuvo, ERROR_ITERADOR_FINALIZADO si no hay elemento actual
 */
resultado_t iterador_bi_elemento_actual(const iterador_bi_t* iterador, void* elemento);

/**
 * @brief Inserta un elemento después de la posición actual (OPERACIÓN RÁPIDA O(1))
 *
 * @param iterador Iterador bidireccional donde insertar
 * @param dato Elemento a insertar
 * @return EXITO si se insertó, código de error en caso contrario
 */
resultado_t iterador_bi_insertar_despues(iterador_bi_t* iterador, const void* dato);

/**
 * @brief Inserta un elemento antes de la posición actual (OPERACIÓN RÁPIDA O(1))
 *
 * @param iterador Iterador bidireccional donde insertar
 * @param dato Elemento a insertar
 * @return EXITO si se insertó, código de error en caso contrario
 */
resultado_t iterador_bi_insertar_antes(iterador_bi_t* iterador, const void* dato);

/**
 * @brief Elimina el elemento actual de la lista (OPERACIÓN RÁPIDA O(1))
 *
 * @param iterador Iterador bidireccional posicionado en el elemento a eliminar
 * @return EXITO si se eliminó, código de error en caso contrario
 */
resultado_t iterador_bi_eliminar_actual(iterador_bi_t* iterador);

/**
 * @brief Reinicia el iterador al inicio de la lista
 *
 * @param iterador Iterador bidireccional a reiniciar
 * @return EXITO si se reinició correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_reiniciar(iterador_bi_t* iterador);

/**
 * @brief Mueve el iterador al final de la lista (OPERACIÓN RÁPIDA O(1))
 *
 * @param iterador Iterador bidireccional a mover
 * @return EXITO si se movió correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_ir_final(iterador_bi_t* iterador);

/**
 * @brief Obtiene la posición actual del iterador (0-based)
 *
 * @param iterador Iterador bidireccional a consultar
 * @param posicion Donde se almacenará la posición actual
 * @return EXITO si se obtuvo correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_obtener_posicion(const iterador_bi_t* iterador, size_t* posicion);

/**
 * @brief Mueve el iterador a una posición específica
 *
 * @param iterador Iterador bidireccional a mover
 * @param posicion Posición destino (0-based)
 * @return EXITO si se movió, ERROR_OPERACION_INVALIDA si la posición no existe
 */
resultado_t iterador_bi_ir_a_posicion(iterador_bi_t* iterador, size_t posicion);

/**
 * @brief Aplica una función de mapeo a todos los elementos
 *
 * @param iterador Iterador sobre la lista original
 * @param funcion Función de transformación
 * @param lista_resultado Donde se almacenará la lista resultante
 * @return EXITO si se mapeó correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_mapear(iterador_bi_t* iterador, iterador_bi_funcion_mapear funcion, lista_doble_t** lista_resultado);

/**
 * @brief Filtra elementos usando un predicado
 *
 * @param iterador Iterador sobre la lista original
 * @param predicado Función de filtrado
 * @param lista_resultado Donde se almacenará la lista filtrada
 * @return EXITO si se filtró correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_filtrar(iterador_bi_t* iterador, iterador_bi_funcion_filtrar predicado, lista_doble_t** lista_resultado);

/**
 * @brief Reduce la lista a un único valor usando una función acumuladora
 *
 * @param iterador Iterador sobre la lista
 * @param funcion Función de reducción
 * @param valor_inicial Valor inicial para la reducción
 * @param resultado Donde se almacenará el resultado de la reducción
 * @return EXITO si se redujo correctamente, código de error en caso contrario
 */
resultado_t iterador_bi_reducir(iterador_bi_t* iterador, iterador_bi_funcion_reducir funcion, void* valor_inicial, void* resultado);

#endif /// ITERADOR_BI_H_INCLUDED
