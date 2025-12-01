/**
 * @file verificaciones.c
 * @brief Implementación de verificaciones de seguridad y validaciones
 */
#include "../include/verificaciones.h"
#include "../iterador/iterador_privada.h"
#include "../lista/lista_privada.h"
#include "../lista_doble/lista_doble_privada.h"
#include "../iterador_bi/iterador_bi_privada.h"
#include <stdlib.h>

bool verificar_puntero_no_nulo(const void* puntero,const char* nombre){
    if(puntero==NULL){
        LOG_ERROR("Puntero nulo detectado: %s",nombre);
        return false;
    }
    return true;
}

bool verificar_lista_valida(const lista_t* lista){
    if(!verificar_puntero_no_nulo(lista,"lista")){
        return false;
    }
    if(lista->tamanio_elemento==0){
        LOG_ERROR("Tamaño de elemento inválido: 0");
        return false;
    }
    return true;
}

bool verificar_iterador_valido(const iterador_t* iterador){
    if(!verificar_puntero_no_nulo(iterador,"iterador")){
        return false;
    }
    if(iterador->tamanio_nodo==0){
        LOG_ERROR("Tamaño de nodo inválido en iterador: 0");
        return false;
    }
    return true;
}

resultado_t verificar_parametros_lista(const lista_t* lista,const void* dato){
    if(!verificar_lista_valida(lista)){
        return ERROR_PARAMETRO_NULO;
    }
    if(!verificar_puntero_no_nulo(dato,"dato")){
        return ERROR_PARAMETRO_NULO;
    }
    return EXITO;
}

bool verificar_lista_doble_valida(const lista_doble_t* lista) {
    if (!verificar_puntero_no_nulo(lista, "lista_doble")) {
        return false;
    }

    if (lista->tamanio_elemento == 0) {
        LOG_ERROR("Tamaño de elemento inválido en lista doble: 0");
        return false;
    }

    // Verificación de consistencia estructural (solo en DEBUG)
    #ifdef DEBUG
    if (!lista_doble_verificar_integridad(lista)) {
        LOG_ERROR("Lista doble falló verificación de integridad estructural");
        return false;
    }
    #endif

    return true;
}

bool verificar_iterador_bi_valido(const iterador_bi_t* iterador) {
    if (!verificar_puntero_no_nulo(iterador, "iterador_bi")) {
        return false;
    }

    if (iterador->tamanio_elemento == 0) {
        LOG_ERROR("Tamaño de elemento inválido en iterador bi: 0");
        return false;
    }

    if (!iterador->valido) {
        LOG_ERROR("Iterador bidireccional marcado como inválido");
        return false;
    }

    #ifdef DEBUG
    if (!iterador_bi_es_valido(iterador)) {
        LOG_ERROR("Iterador bidireccional no es válido (lista modificada externamente)");
        return false;
    }
    #endif

    return true;
}

resultado_t verificar_parametros_lista_doble(const lista_doble_t* lista, const void* dato) {
    if (!verificar_lista_doble_valida(lista)) {
        return ERROR_PARAMETRO_NULO;
    }

    if (!verificar_puntero_no_nulo(dato, "dato")) {
        return ERROR_PARAMETRO_NULO;
    }

    return EXITO;
}

#ifdef DEBUG
bool verificar_nodo_pertenece_a_lista(const lista_doble_t* lista, const struct nodo_doble_s* nodo) {
    if (!verificar_lista_doble_valida(lista) || !verificar_puntero_no_nulo(nodo, "nodo")) {
        return false;
    }

    // Recorrer la lista para verificar que el nodo pertenece a ella
    struct nodo_doble_s* actual = lista->cabeza;
    while (actual != NULL) {
        if (actual == nodo) {
            return true;
        }
        actual = actual->siguiente;
    }

    LOG_ERROR("Nodo no pertenece a la lista doble especificada");
    return false;
}
#endif
