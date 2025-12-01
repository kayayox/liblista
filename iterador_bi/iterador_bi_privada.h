/**
 * @file iterador_bi_privada.h
 * @brief Definiciones privadas para Iterador Bidireccional
 * @author Soubhi Khayat Najjar kayayox@gmail.com
 * @version 2.0
 *
 * @note Este archivo solo debe ser incluido en los archivos de implementación
 * Requiere acceso a las estructuras internas de lista_doble.
 */

#ifndef ITERADOR_BI_PRIVADA_H_INCLUDED
#define ITERADOR_BI_PRIVADA_H_INCLUDED

#include "../include/iterador_bi.h"
#include "../lista_doble/lista_doble_privada.h"  // Para struct nodo_doble_s

/**
 * @struct iterador_bi_s
 * @brief Estructura interna del iterador bidireccional
 *
 * @var iterador_bi_s::nodo_inicio Puntero al primer nodo (para reinicio)
 * @var iterador_bi_s::actual Puntero al nodo actual de la iteración
 * @var iterador_bi_s::lista_original Referencia a la lista sobre la que itera
 * @var iterador_bi_s::posicion Posición actual en la lista (0-based)
 * @var iterador_bi_s::num_nodos_total Número total de nodos en la lista
 * @var iterador_bi_s::tamanio_elemento Tamaño de cada elemento (copia de la lista)
 * @var iterador_bi_s::direccion_avance Dirección del último movimiento (true=adelante, false=atrás)
 * @var iterador_bi_s::valido Flag que indica si el iterador está en estado válido
 */
struct iterador_bi_s{
    struct nodo_doble_s* nodo_inicio;
    struct nodo_doble_s* actual;
    const lista_doble_t* lista_original;
    size_t posicion;
    size_t num_nodos_total;
    size_t tamanio_elemento;
    bool direccion_avance;
    bool valido;
};

/**
 * @brief Verifica si el iterador sigue siendo válido (lista no modificada externamente)
 *
 * @param iterador Iterador a verificar
 * @return true si el iterador es válido, false si la lista fue modificada externamente
 */
bool iterador_bi_es_valido(const iterador_bi_t* iterador);

/**
 * @brief Actualiza el estado del iterador después de una modificación de la lista
 *
 * @param iterador Iterador a actualizar
 * @return EXITO si se actualizó correctamente, ERROR_ITERADOR_INVALIDO si no es recuperable
 */
resultado_t iterador_bi_actualizar_estado(iterador_bi_t* iterador);

/**
 * @brief Mueve el iterador a un nodo específico (función interna)
 *
 * @param iterador Iterador a mover
 * @param nuevo_actual Nuevo nodo actual
 * @param nueva_posicion Nueva posición del iterador
 * @return EXITO si se movió correctamente
 */
resultado_t iterador_bi_mover_a_nodo(iterador_bi_t* iterador, struct nodo_doble_s* nuevo_actual, size_t nueva_posicion);

/**
 * @brief Encuentra la posición de un nodo en la lista (función interna O(n))
 *
 * @param lista Lista donde buscar
 * @param nodo Nodo cuya posición se busca
 * @param posicion Donde se almacenará la posición encontrada
 * @return EXITO si se encontró, ERROR_ELEMENTO_NO_ENCONTRADO si no
 */
resultado_t iterador_bi_encontrar_posicion(const lista_doble_t* lista, const struct nodo_doble_s* nodo, size_t* posicion);

/**
 * @brief Encuentra el nodo en una posición específica (función interna O(n/2))
 *
 * @param lista Lista donde buscar
 * @param posicion Posición deseada (0-based)
 * @param nodo_encontrado Donde se almacenará el nodo encontrado
 * @return EXITO si se encontró, ERROR_OPERACION_INVALIDA si la posición no existe
 */
resultado_t iterador_bi_encontrar_nodo_en_posicion(const lista_doble_t* lista, size_t posicion, struct nodo_doble_s** nodo_encontrado);

#endif /// ITERADOR_BI_PRIVADA_H_INCLUDED
