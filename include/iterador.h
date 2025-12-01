/**
 * @file iterador.h
 * @brief Interfaz pública para el iterador de lista
 * @author Soubhi Khayat Najjar kayayox@gmail.com
 * @version 1.0
 */

#ifndef ITERADOR_H_INCLUDED
#define ITERADOR_H_INCLUDED

#pragma once
#include "resultados.h"
#include "lista.h"

/**
 * @typedef iterador_t
 * @brief Tipo opaco que representa un iterador de lista
 */
typedef struct iterador_s iterador_t;

/**
 * @typedef iterador_funcion_mapear
 * @brief Función para transformar elementos (map)
 */
typedef void(*iterador_funcion_mapear)(const void* elemento,void* resultado);

/**
 * @typedef iterador_funcion_filtrar
 * @brief Función para filtrar elementos (filter)
 */
typedef bool(*iterador_funcion_filtrar)(const void* elemento);

/**
 * @typedef iterador_funcion_reducir
 * @brief Función para reducir elementos (reduce)
 */
typedef void(*iterador_funcion_reducir)(const void* elemento,void* acumulador);

/**
 * @brief Crea un nuevo iterador para una lista
 *
 * @param lista Lista sobre la que iterar
 * @param iterador Donde se almacenará el iterador creado
 * @return EXITO si se creó correctamente, código de error en caso contrario
 */
resultado_t iterador_crear(const lista_t* lista,iterador_t** iterador);

/**
 * @brief Libera los recursos del iterador
 *
 * @param iterador Iterador a liberar
 * @return EXITO si se liberó correctamente, código de error en caso contrario
 */
resultado_t iterador_liberar(iterador_t** iterador);

/**
 * @brief Avanza al siguiente elemento y lo obtiene
 *
 * @param iterador Iterador a avanzar
 * @param elemento Donde se almacenará el elemento actual
 * @return EXITO si se avanzó, ERROR_ITERADOR_FINALIZADO si no hay más elementos
 */
resultado_t iterador_siguiente(iterador_t* iterador,void* elemento);

/**
 * @brief Verifica si hay más elementos por iterar
 *
 * @param iterador Iterador a verificar
 * @param tiene_siguiente Donde se almacenará el resultado
 * @return EXITO si se verificó correctamente, código de error en caso contrario
 */
resultado_t iterador_tiene_siguiente(const iterador_t* iterador,bool* tiene_siguiente);

/**
 * @brief Obtiene el elemento actual sin avanzar el iterador
 *
 * @param iterador Iterador a consultar
 * @param elemento Donde se almacenará el elemento actual
 * @return EXITO si se obtuvo, ERROR_ITERADOR_FINALIZADO si no hay elemento actual
 */
resultado_t iterador_elemento_actual(const iterador_t* iterador,void* elemento);

/**
 * @brief Inserta un elemento despues de actual sin avanzar el iterador
 *
 * @param iterador Iterador a consultar
 * @param elemento Donde se almacenará el elemento a insertar
 * @return EXITO si se obtuvo, ERROR_MEMORIA_INSUFICIENTE si no se logra allocar espacio
 */
resultado_t iterador_insertar_despues(iterador_t* iterador,lista_t* lista,const void* dato);

/**
 * @brief Inserta un elemento antes de actual sin avanzar el iterador
 *
 * @param iterador Iterador a consultar
 * @param elemento Donde se almacenará el elemento a insertar
 * @return EXITO si se obtuvo, ERROR_MEMORIA_INSUFICIENTE si no se logra allocar espacio
 */
resultado_t iterador_insertar_antes(iterador_t* iterador,lista_t* lista,const void* dato);

/**
 * @brief Reinicia el iterador al inicio de la lista
 *
 * @param iterador Iterador a reiniciar
 * @return EXITO si se reinició correctamente, código de error en caso contrario
 */
resultado_t iterador_reiniciar(iterador_t* iterador);

/**
 * @brief Aplica una función de mapeo a todos los elementos
 *
 * @param iterador Iterador sobre la lista original
 * @param funcion Función de transformación
 * @param lista_resultado Donde se almacenará la lista resultante
 * @return EXITO si se mapeó correctamente, código de error en caso contrario
 */
resultado_t iterador_mapear(iterador_t* iterador,iterador_funcion_mapear funcion,lista_t** lista_resultado);

/**
 * @brief Filtra elementos usando un predicado
 *
 * @param iterador Iterador sobre la lista original
 * @param predicado Función de filtrado
 * @param lista_resultado Donde se almacenará la lista filtrada
 * @return EXITO si se filtró correctamente, código de error en caso contrario
 */
resultado_t iterador_filtrar(iterador_t* iterador,iterador_funcion_filtrar predicado,lista_t** lista_resultado);

/**
 * @brief Reduce la lista a un único valor usando una función acumuladora
 *
 * @param iterador Iterador sobre la lista
 * @param funcion Función de reducción
 * @param valor_inicial Valor inicial para la reducción
 * @param resultado Donde se almacenará el resultado de la reducción
 * @return EXITO si se redujo correctamente, código de error en caso contrario
 */
resultado_t iterador_reducir(iterador_t* iterador,iterador_funcion_reducir funcion,void* valor_inicial,void* resultado);

#endif /// ITERADOR_H_INCLUDED
