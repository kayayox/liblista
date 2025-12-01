/**
 * @file resultados.h
 * @brief Definición de códigos de resultado y sistema de logging
 * @author Tu Nombre
 * @version 1.0
 */

#ifndef RESULTADOS_H_INCLUDED
#define RESULTADOS_H_INCLUDED

#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

/**
 * @enum resultado_t
 * @brief Códigos de resultado para operaciones de la librería
 */
typedef enum {
    EXITO = 0,                      ///< Operación exitosa
    ERROR_PARAMETRO_NULO,           ///< Parámetro nulo no permitido
    ERROR_MEMORIA_INSUFICIENTE,     ///< No hay memoria disponible
    ERROR_ITERADOR_INVALIDO,        ///< Iterador en estado inválido
    ERROR_LISTA_VACIA,              ///< Operación no permitida en lista vacía
    ERROR_ELEMENTO_NO_ENCONTRADO,   ///< Elemento no encontrado en la lista
    ERROR_OPERACION_INVALIDA,       ///< Operación no válida para el estado actual
    ERROR_ITERADOR_FINALIZADO       ///< Iterador ha alcanzado el final
} resultado_t;

/**
 * @enum nivel_log_t
 * @brief Niveles de logging disponibles
 */
typedef enum {
    LOG_DEBUG,      ///< Mensajes de depuración
    LOG_INFO,       ///< Información general
    LOG_WARNING,    ///< Advertencias
    LOG_ERROR       ///< Errores
} nivel_log_t;

// Declaraciones de funciones de utilidad
const char* resultado_a_string(resultado_t resultado);
void manejar_error(resultado_t resultado, const char* contexto);

// Función de logging con formato
void log_mensaje(nivel_log_t nivel, const char* archivo, int linea, const char* formato, ...);

// Macros de logging con formato
#ifdef DEBUG
#define LOG_ERROR(formato, ...) log_mensaje(LOG_ERROR, __FILE__, __LINE__, formato, ##__VA_ARGS__)
#define LOG_WARNING(formato, ...) log_mensaje(LOG_WARNING, __FILE__, __LINE__, formato, ##__VA_ARGS__)
#define LOG_INFO(formato, ...) log_mensaje(LOG_INFO, __FILE__, __LINE__, formato, ##__VA_ARGS__)
#define LOG_DEBUG(formato, ...) log_mensaje(LOG_DEBUG, __FILE__, __LINE__, formato, ##__VA_ARGS__)
#else
#define LOG_ERROR(formato, ...) log_mensaje(LOG_ERROR, __FILE__, __LINE__, formato, ##__VA_ARGS__)
#define LOG_WARNING(formato, ...) log_mensaje(LOG_WARNING, __FILE__, __LINE__, formato, ##__VA_ARGS__)
#define LOG_INFO(formato, ...)  // No-op en producción
#define LOG_DEBUG(formato, ...) // No-op en producción
#endif

#endif /// RESULTADOS_H_INCLUDED
