/**
 * @file iterador.c
 * @brief Implementación del iterador de lista
 */

#include "iterador_privada.h"
#include "../include/verificaciones.h"
#include "../lista/lista_privada.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

resultado_t iterador_crear(const lista_t* lista,iterador_t** iterador){
    if(!verificar_lista_valida(lista) || !verificar_puntero_no_nulo(iterador,"iterador")){
        return ERROR_PARAMETRO_NULO;
    }

    *iterador=(iterador_t*)malloc(sizeof(iterador_t));
    if(*iterador==NULL){
        LOG_ERROR("No se pudo asignar memoria para el iterador");
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    void* nodo_cabeza;
    resultado_t resultado=lista_obtener_nodo_cabeza(lista,&nodo_cabeza);
    if(resultado!=EXITO){
        free(*iterador);
        *iterador=NULL;
        return resultado;
    }
    (*iterador)->actual=nodo_cabeza;
    (*iterador)->nodo=nodo_cabeza;
    (*iterador)->prev=NULL;
    (*iterador)->cont=0;
    (*iterador)->num_nodos=lista->cantidad_elementos;
    (*iterador)->tamanio_nodo=lista->tamanio_elemento;
    LOG_DEBUG("Iterador creado exitosamente");
    return EXITO;
}

resultado_t iterador_liberar(iterador_t** iterador){
    if(!verificar_puntero_no_nulo(iterador,"iterador") || !verificar_puntero_no_nulo(*iterador,"*iterador")){
        return ERROR_PARAMETRO_NULO;
    }

    free(*iterador);
    *iterador=NULL;
    LOG_DEBUG("Iterador liberado exitosamente");
    return EXITO;
}

resultado_t iterador_siguiente(iterador_t* iterador,void* elemento){
    if(!verificar_iterador_valido(iterador) || !verificar_puntero_no_nulo(elemento,"elemento")){
        return ERROR_PARAMETRO_NULO;
    }

    if(iterador->actual==NULL){
        LOG_ERROR("Iterador finalizado, no hay más elementos");
        return ERROR_ITERADOR_FINALIZADO;
    }
    memcpy(elemento,iterador->actual->dato,iterador->tamanio_nodo);
    iterador->prev=iterador->actual;
    iterador->actual=iterador->actual->siguiente;
    iterador->cont++;

    return EXITO;
}

resultado_t iterador_tiene_siguiente(const iterador_t* iterador,bool* tiene_siguiente){
    if(!verificar_iterador_valido(iterador) || !verificar_puntero_no_nulo(tiene_siguiente,"tiene_siguiente")){
        return ERROR_PARAMETRO_NULO;
    }

    *tiene_siguiente=(iterador->actual!=NULL);
    return EXITO;
}

resultado_t iterador_elemento_actual(const iterador_t* iterador,void* elemento){
    if(!verificar_iterador_valido(iterador) || !verificar_puntero_no_nulo(elemento,"elemento")){
        return ERROR_PARAMETRO_NULO;
    }

    if(iterador->actual==NULL){
        LOG_ERROR("No hay elemento actual - iterador finalizado");
        return ERROR_ITERADOR_FINALIZADO;
    }
    memcpy(elemento,iterador->actual->dato,iterador->tamanio_nodo);
    return EXITO;
}

resultado_t iterador_insertar_despues(iterador_t* iterador,lista_t* lista,const void* dato){
    if(!verificar_iterador_valido(iterador) || !verificar_puntero_no_nulo(dato,"dato")){
        return ERROR_PARAMETRO_NULO;
    }

    struct nodo_s* incert=crear_nodo_s(lista,dato);
    if(incert==NULL){
        LOG_ERROR("No se pudo asignar memoria para el nodo");
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    incert->siguiente=iterador->actual->siguiente;
    iterador->actual->siguiente=incert;
    iterador->prev=iterador->actual;
    iterador->actual=incert;
    iterador->cont++;
    iterador->num_nodos++;

    return EXITO;
}

resultado_t iterador_insertar_antes(iterador_t* iterador,lista_t* lista,const void* dato){
    if(!verificar_iterador_valido(iterador) || !verificar_puntero_no_nulo(dato,"dato")){
        return ERROR_PARAMETRO_NULO;
    }

    struct nodo_s* incert=crear_nodo_s(lista,dato);
    if(incert==NULL){
        LOG_ERROR("No se pudo asignar memoria para el nodo");
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    if(iterador->prev==NULL){
        incert->siguiente=iterador->actual;
        iterador->nodo=incert;
        iterador->prev=incert;
    }else{
        incert->siguiente=iterador->actual;
        iterador->prev->siguiente=incert;
        iterador->prev=incert;
    }
    iterador->cont++;
    iterador->num_nodos++;
    return EXITO;
}

resultado_t iterador_reiniciar(iterador_t* iterador){
    if(!verificar_iterador_valido(iterador)){
        return ERROR_PARAMETRO_NULO;
    }

    iterador->actual=iterador->nodo;
    iterador->prev=NULL;
    iterador->cont=0;

    LOG_DEBUG("Iterador reiniciado");
    return EXITO;
}

resultado_t iterador_mapear(iterador_t* iterador,iterador_funcion_mapear funcion,lista_t** lista_resultado){
    if(iterador==NULL || funcion==NULL || lista_resultado==NULL)return ERROR_PARAMETRO_NULO;

    if(iterador->actual==NULL)return ERROR_LISTA_VACIA;
    struct nodo_s* actual_orig=iterador->actual;
    struct nodo_s* prev_orig=iterador->prev;
    size_t cont_orig=iterador->cont;
    // Crear nueva lista con las mismas funciones que la original
    lista_t* lista_temp=NULL;
    resultado_t resultado=lista_crear_avanzado(&lista_temp, iterador->tamanio_nodo,NULL,NULL,NULL);
    if(resultado!=EXITO){
        return resultado;
    }
    void* elemento_actual=malloc(iterador->tamanio_nodo);
    void* elemento_mapeado=malloc(iterador->tamanio_nodo);

    if(elemento_actual==NULL || elemento_mapeado==NULL){
        free(elemento_actual);
        free(elemento_mapeado);
        lista_liberar(&lista_temp);
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    while(iterador->actual!=NULL){
        resultado=iterador_siguiente(iterador,elemento_actual);
        if(resultado!=EXITO){
            break;
        }
        funcion(elemento_actual,elemento_mapeado);
        resultado=lista_insertar_final(lista_temp,elemento_mapeado);
        if(resultado!=EXITO){
            break;
        }
    }
    iterador->actual=actual_orig;
    iterador->prev=prev_orig;
    iterador->cont=cont_orig;

    free(elemento_actual);
    free(elemento_mapeado);

    if(resultado!=EXITO){
        lista_liberar(&lista_temp);
        return resultado;
    }
    *lista_resultado=lista_temp;
    return EXITO;
}

resultado_t iterador_filtrar(iterador_t* iterador,iterador_funcion_filtrar predicado,lista_t** lista_resultado){
    if(!verificar_iterador_valido(iterador) || predicado==NULL || lista_resultado==NULL)return ERROR_PARAMETRO_NULO;

    if(iterador->actual==NULL)
        return ERROR_LISTA_VACIA;
    // Guardar estado original del iterador
    struct nodo_s* actual_orig=iterador->actual;
    struct nodo_s* prev_orig=iterador->prev;
    size_t cont_orig=iterador->cont;
    // Crear nueva lista para resultados
    lista_t* lista_nueva=NULL;
    resultado_t resultado=lista_crear(&lista_nueva,iterador->tamanio_nodo);
    if(resultado!=EXITO){
        return resultado;
    }
    // Buffer para datos temporales
    void* elemento_actual=malloc(iterador->tamanio_nodo);
    if(elemento_actual==NULL){
        lista_liberar(&lista_nueva);
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    // Recorrer y filtrar
    while(iterador->actual!=NULL){
        // Obtener elemento actual
        resultado=iterador_siguiente(iterador,elemento_actual);
        if(resultado!=EXITO){
            break;
        }
        // Aplicar predicado de filtro
        if(predicado(elemento_actual)){
            // Insertar en nueva lista si pasa el filtro
            resultado=lista_insertar_final(lista_nueva,elemento_actual);
            if(resultado!=EXITO){
                break;
            }
        }
    }
    // Restaurar estado original del iterador
    iterador->actual=actual_orig;
    iterador->prev=prev_orig;
    iterador->cont=cont_orig;
    // Liberar recursos temporales
    free(elemento_actual);

    if(resultado!=EXITO){
        lista_liberar(&lista_nueva);
        return resultado;
    }
    // Asignar resultado
    *lista_resultado=lista_nueva;
    return EXITO;
}

resultado_t iterador_reducir(iterador_t* iterador,iterador_funcion_reducir funcion,void* valor_inicial,void* resultado){
    if(!verificar_iterador_valido(iterador) || funcion==NULL || valor_inicial==NULL || resultado==NULL)return ERROR_PARAMETRO_NULO;

    if(iterador->actual==NULL)
        return ERROR_LISTA_VACIA;
    // Guardar estado original del iterador
    struct nodo_s* actual_orig=iterador->actual;
    struct nodo_s* prev_orig=iterador->prev;
    size_t cont_orig=iterador->cont;
    // Copiar valor inicial al resultado
    memcpy(resultado,valor_inicial,iterador->tamanio_nodo);
    // Buffer para datos temporales
    void* elemento_actual=malloc(iterador->tamanio_nodo);
    if(elemento_actual==NULL){
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    resultado_t resultado_op=EXITO;
    // Recorrer y reducir
    while(iterador->actual!=NULL){
        // Obtener elemento actual
        resultado_op=iterador_siguiente(iterador,elemento_actual);
        if(resultado_op!=EXITO){
            break;
        }
        // Aplicar función de reducción
        funcion(elemento_actual,resultado);
    }
    // Restaurar estado original del iterador
    iterador->actual=actual_orig;
    iterador->prev=prev_orig;
    iterador->cont=cont_orig;
    // Liberar recursos temporales
    free(elemento_actual);
    return resultado_op;
}
