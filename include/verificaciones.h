#ifndef VERIFICACIONES_H_INCLUDED
#define VERIFICACIONES_H_INCLUDED

#include <stdbool.h>
#include "lista.h"
#include "lista_doble.h"
#include "iterador.h"
#include "iterador_bi.h"

/**
 * @brief Verifica que un puntero no sea NULL
 * @param puntero Puntero a verificar
 * @param nombre Nombre del puntero para logging
 * @return true si no es NULL, false si es NULL (y loggea error)
 */
bool verificar_puntero_no_nulo(const void* puntero, const char* nombre);

/**
 * @brief Verifica que una lista simple sea válida
 * @param lista Lista simple a verificar
 * @return true si es válida, false si no (y loggea error)
 */
bool verificar_lista_valida(const lista_t* lista);

/**
 * @brief Verifica que una lista doble sea válida
 * @param lista Lista doble a verificar
 * @return true si es válida, false si no (y loggea error)
 */
bool verificar_lista_doble_valida(const lista_doble_t* lista);

/**
 * @brief Verifica que un iterador simple sea válido
 * @param iterador Iterador simple a verificar
 * @return true si es válido, false si no (y loggea error)
 */
bool verificar_iterador_valido(const iterador_t* iterador);

/**
 * @brief Verifica que un iterador bidireccional sea válido
 * @param iterador Iterador bidireccional a verificar
 * @return true si es válido, false si no (y loggea error)
 */
bool verificar_iterador_bi_valido(const iterador_bi_t* iterador);

/**
 * @brief Verifica parámetros para operaciones de lista simple
 * @param lista Lista simple a verificar
 * @param dato Dato a verificar
 * @return EXITO si son válidos, código de error en caso contrario
 */
resultado_t verificar_parametros_lista(const lista_t* lista, const void* dato);

/**
 * @brief Verifica parámetros para operaciones de lista doble
 * @param lista Lista doble a verificar
 * @param dato Dato a verificar
 * @return EXITO si son válidos, código de error en caso contrario
 */
resultado_t verificar_parametros_lista_doble(const lista_doble_t* lista, const void* dato);

/**
 * @brief Verifica que un nodo pertenezca a una lista doble (DEBUG only)
 * @param lista Lista doble a verificar
 * @param nodo Nodo a verificar
 * @return true si el nodo pertenece a la lista, false si no
 */
bool verificar_nodo_pertenece_a_lista(const lista_doble_t* lista, const struct nodo_doble_s* nodo);

#endif // VERIFICACIONES_H_INCLUDED
