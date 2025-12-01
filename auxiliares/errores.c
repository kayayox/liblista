/**
 * @file errores.c
 * @brief Implementación del manejo de errores para la librería de lista
 */

#include "resultados.h"
#include <stdio.h>
#include <stdlib.h>

const char* resultado_a_string(resultado_t resultado){
    static const char* mensajes[]={
        "EXITO",
        "ERROR_PARAMETRO_NULO",
        "ERROR_MEMORIA_INSUFICIENTE",
        "ERROR_ITERADOR_INVALIDO",
        "ERROR_LISTA_VACIA",
        "ERROR_ELEMENTO_NO_ENCONTRADO",
        "ERROR_OPERACION_INVALIDA",
        "ERROR_ITERADOR_FINALIZADO"
    };
    if(resultado>=EXITO && resultado<=ERROR_ITERADOR_FINALIZADO){
        return mensajes[resultado];
    }
    return "ERROR_DESCONOCIDO";
}

void manejar_error(resultado_t resultado,const char* contexto){
    if(resultado!=EXITO){
        LOG_ERROR("Error en %s: %s",contexto,resultado_a_string(resultado));
    }
}
