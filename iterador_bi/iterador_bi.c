/**
 * @file iterador_bi.c
 * @brief Implementación del iterador bidireccional
 */

#include "iterador_bi_privada.h"
#include "../include/verificaciones.h"
#include <stdlib.h>
#include <string.h>

bool iterador_bi_es_valido(const iterador_bi_t* iterador){
    if(iterador==NULL || !iterador->valido){
        return false;
    }
    if(iterador->lista_original!=NULL){
        size_t tam_actual;
        if(lista_doble_obtener_tamanio(iterador->lista_original,&tam_actual)!=EXITO){
            return false;
        }
        if(tam_actual!=iterador->num_nodos_total){
            return false;
        }
    }

    return true;
}

resultado_t iterador_bi_actualizar_estado(iterador_bi_t* iterador){
    if(!verificar_iterador_bi_valido(iterador)){
        return ERROR_ITERADOR_INVALIDO;
    }
    if(iterador->lista_original!=NULL){
        resultado_t res=lista_doble_obtener_tamanio(iterador->lista_original,&iterador->num_nodos_total);
        if(res!=EXITO){
            iterador->valido=false;
            return res;
        }
    }

    return EXITO;
}

resultado_t iterador_bi_mover_a_nodo(iterador_bi_t* iterador,struct nodo_doble_s* nuevo_actual,size_t nueva_posicion){
    if(!verificar_iterador_bi_valido(iterador)){
        return ERROR_ITERADOR_INVALIDO;
    }
    iterador->actual=nuevo_actual;
    iterador->posicion=nueva_posicion;
    return EXITO;
}

resultado_t iterador_bi_encontrar_posicion(const lista_doble_t* lista,const struct nodo_doble_s* nodo,size_t* posicion){
    if(!verificar_lista_doble_valida(lista) || nodo==NULL || posicion==NULL){
        return ERROR_PARAMETRO_NULO;
    }
    struct nodo_doble_s* actual=lista->cabeza;
    size_t pos=0;
    while(actual!=NULL){
        if(actual==nodo){
            *posicion=pos;
            return EXITO;
        }
        actual=actual->siguiente;
        pos++;
    }

    return ERROR_ELEMENTO_NO_ENCONTRADO;
}

resultado_t iterador_bi_encontrar_nodo_en_posicion(const lista_doble_t* lista,size_t posicion,struct nodo_doble_s** nodo_encontrado){
    if(!verificar_lista_doble_valida(lista) || nodo_encontrado==NULL){
        return ERROR_PARAMETRO_NULO;
    }
    if(posicion>=lista->cantidad_elementos){
        return ERROR_OPERACION_INVALIDA;
    }
    if(posicion<lista->cantidad_elementos/2){
        struct nodo_doble_s* actual=lista->cabeza;
        size_t pos=0;
        while(actual!=NULL && pos<posicion){
            actual=actual->siguiente;
            pos++;
        }
        if(actual!=NULL){
            *nodo_encontrado=actual;
            return EXITO;
        }
    }else{
        struct nodo_doble_s* actual=lista->cola;
        size_t pos=lista->cantidad_elementos-1;
        while(actual!=NULL && pos>posicion){
            actual=actual->anterior;
            pos--;
        }
        if(actual!=NULL){
            *nodo_encontrado=actual;
            return EXITO;
        }
    }

    return ERROR_ELEMENTO_NO_ENCONTRADO;
}

resultado_t iterador_bi_crear(const lista_doble_t* lista,iterador_bi_t** iterador){
    if(!verificar_lista_doble_valida(lista) || !verificar_puntero_no_nulo(iterador,"iterador")){
        return ERROR_PARAMETRO_NULO;
    }
    *iterador=(iterador_bi_t*)malloc(sizeof(iterador_bi_t));
    if(*iterador==NULL){
        LOG_ERROR("No se pudo asignar memoria para el iterador bidireccional");
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    (*iterador)->nodo_inicio=lista->cabeza;
    (*iterador)->actual=lista->cabeza;
    (*iterador)->lista_original=lista;
    (*iterador)->posicion=0;
    (*iterador)->tamanio_elemento=lista->tamanio_elemento;
    (*iterador)->direccion_avance=true;
    (*iterador)->valido=true;
    resultado_t res=lista_doble_obtener_tamanio(lista,&(*iterador)->num_nodos_total);
    if(res!=EXITO){
        free(*iterador);
        *iterador=NULL;
        return res;
    }

    LOG_DEBUG("Iterador bidireccional creado exitosamente");
    return EXITO;
}

resultado_t iterador_bi_liberar(iterador_bi_t** iterador){
    if(!verificar_puntero_no_nulo(iterador,"iterador") || !verificar_puntero_no_nulo(*iterador,"*iterador")){
        return ERROR_PARAMETRO_NULO;
    }
    free(*iterador);
    *iterador=NULL;

    LOG_DEBUG("Iterador bidireccional liberado exitosamente");
    return EXITO;
}

resultado_t iterador_bi_siguiente(iterador_bi_t* iterador,void* elemento){
    if(!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(elemento,"elemento")){
        return ERROR_PARAMETRO_NULO;
    }
    if(iterador->actual==NULL){
        LOG_ERROR("Iterador finalizado, no hay más elementos");
        return ERROR_ITERADOR_FINALIZADO;
    }
    memcpy(elemento,iterador->actual->dato,iterador->tamanio_elemento);

    iterador->actual=iterador->actual->siguiente;
    iterador->posicion++;
    iterador->direccion_avance=true;
    return EXITO;
}

resultado_t iterador_bi_anterior(iterador_bi_t* iterador,void* elemento){
    if(!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(elemento,"elemento")){
        return ERROR_PARAMETRO_NULO;
    }
    if(iterador->actual==iterador->nodo_inicio){
        LOG_ERROR("No hay elemento anterior - iterador al inicio");
        return ERROR_ITERADOR_FINALIZADO;
    }
    if(iterador->actual==NULL){
        if(iterador->lista_original->cola==NULL){
            return ERROR_ITERADOR_FINALIZADO;
        }
        iterador->actual=iterador->lista_original->cola;
    }else{
        iterador->actual=iterador->actual->anterior;
    }
    if(iterador->actual==NULL){
        return ERROR_ITERADOR_FINALIZADO;
    }
    memcpy(elemento,iterador->actual->dato,iterador->tamanio_elemento);
    iterador->posicion--;
    iterador->direccion_avance=false;
    return EXITO;
}

resultado_t iterador_bi_tiene_siguiente(const iterador_bi_t* iterador,bool* tiene_siguiente){
    if(!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(tiene_siguiente,"tiene_siguiente")){
        return ERROR_PARAMETRO_NULO;
    }
    *tiene_siguiente=(iterador->actual!=NULL);
    return EXITO;
}

resultado_t iterador_bi_tiene_anterior(const iterador_bi_t* iterador, bool* tiene_anterior){
    if(!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(tiene_anterior,"tiene_anterior")){
        return ERROR_PARAMETRO_NULO;
    }
    *tiene_anterior=(iterador->actual!=iterador->nodo_inicio && iterador->lista_original->cabeza!=NULL);
    return EXITO;
}

resultado_t iterador_bi_elemento_actual(const iterador_bi_t* iterador,void* elemento){
    if(!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(elemento,"elemento")){
        return ERROR_PARAMETRO_NULO;
    }
    if(iterador->actual==NULL){
        LOG_ERROR("No hay elemento actual - iterador finalizado");
        return ERROR_ITERADOR_FINALIZADO;
    }
    memcpy(elemento,iterador->actual->dato,iterador->tamanio_elemento);
    return EXITO;
}

// Continuación del archivo iterador_bi.c

resultado_t iterador_bi_insertar_despues(iterador_bi_t* iterador, const void* dato) {
    if (!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(dato, "dato")) {
        return ERROR_PARAMETRO_NULO;
    }

    if (iterador->actual == NULL) {
        // Insertar al final si estamos al final de la lista
        return lista_doble_insertar_final((lista_doble_t*)iterador->lista_original, dato);
    }

    // Crear nuevo nodo
    struct nodo_doble_s* nuevo = lista_doble_crear_nodo((lista_doble_t*)iterador->lista_original, dato);
    if (nuevo == NULL) {
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    // Configurar enlaces del nuevo nodo
    nuevo->siguiente = iterador->actual->siguiente;
    nuevo->anterior = iterador->actual;

    // Actualizar enlaces de nodos vecinos
    if (iterador->actual->siguiente != NULL) {
        iterador->actual->siguiente->anterior = nuevo;
    } else {
        // Si no hay siguiente, actualizar cola de la lista
        ((lista_doble_t*)iterador->lista_original)->cola = nuevo;
    }

    iterador->actual->siguiente = nuevo;

    // Actualizar contadores
    ((lista_doble_t*)iterador->lista_original)->cantidad_elementos++;
    iterador->num_nodos_total++;

    LOG_DEBUG("Elemento insertado después de la posición actual");
    return EXITO;
}

resultado_t iterador_bi_insertar_antes(iterador_bi_t* iterador, const void* dato) {
    if (!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(dato, "dato")) {
        return ERROR_PARAMETRO_NULO;
    }

    if (iterador->actual == iterador->nodo_inicio) {
        // Insertar al inicio si estamos al inicio de la lista
        return lista_doble_insertar_inicio((lista_doble_t*)iterador->lista_original, dato);
    }

    // Crear nuevo nodo
    struct nodo_doble_s* nuevo = lista_doble_crear_nodo((lista_doble_t*)iterador->lista_original, dato);
    if (nuevo == NULL) {
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    // Configurar enlaces del nuevo nodo
    nuevo->siguiente = iterador->actual;
    nuevo->anterior = iterador->actual->anterior;

    // Actualizar enlaces de nodos vecinos
    if (iterador->actual->anterior != NULL) {
        iterador->actual->anterior->siguiente = nuevo;
    } else {
        // Si no hay anterior, actualizar cabeza de la lista
        ((lista_doble_t*)iterador->lista_original)->cabeza = nuevo;
        iterador->nodo_inicio = nuevo;
    }

    iterador->actual->anterior = nuevo;

    // Actualizar contadores
    ((lista_doble_t*)iterador->lista_original)->cantidad_elementos++;
    iterador->num_nodos_total++;

    LOG_DEBUG("Elemento insertado antes de la posición actual");
    return EXITO;
}

resultado_t iterador_bi_eliminar_actual(iterador_bi_t* iterador) {
    if (!verificar_iterador_bi_valido(iterador)) {
        return ERROR_ITERADOR_INVALIDO;
    }

    if (iterador->actual == NULL) {
        LOG_ERROR("No hay elemento actual para eliminar");
        return ERROR_ITERADOR_FINALIZADO;
    }

    // Guardar referencia al nodo a eliminar
    struct nodo_doble_s* nodo_a_eliminar = iterador->actual;

    // Reconectar nodos vecinos
    if (nodo_a_eliminar->anterior != NULL) {
        nodo_a_eliminar->anterior->siguiente = nodo_a_eliminar->siguiente;
    } else {
        // Era el primer nodo, actualizar cabeza
        ((lista_doble_t*)iterador->lista_original)->cabeza = nodo_a_eliminar->siguiente;
        iterador->nodo_inicio = nodo_a_eliminar->siguiente;
    }

    if (nodo_a_eliminar->siguiente != NULL) {
        nodo_a_eliminar->siguiente->anterior = nodo_a_eliminar->anterior;
    } else {
        // Era el último nodo, actualizar cola
        ((lista_doble_t*)iterador->lista_original)->cola = nodo_a_eliminar->anterior;
    }

    // Mover iterador al siguiente nodo (o anterior si no hay siguiente)
    if (nodo_a_eliminar->siguiente != NULL) {
        iterador->actual = nodo_a_eliminar->siguiente;
    } else {
        iterador->actual = nodo_a_eliminar->anterior;
        if (iterador->actual != NULL) {
            iterador->posicion--;
        }
    }

    // Liberar memoria del nodo eliminado
    if (((lista_doble_t*)iterador->lista_original)->liberar_dato != NULL) {
        ((lista_doble_t*)iterador->lista_original)->liberar_dato(nodo_a_eliminar->dato);
    } else {
        free(nodo_a_eliminar->dato);
    }
    free(nodo_a_eliminar);

    // Actualizar contadores
    ((lista_doble_t*)iterador->lista_original)->cantidad_elementos--;
    iterador->num_nodos_total--;

    LOG_DEBUG("Elemento actual eliminado");
    return EXITO;
}

resultado_t iterador_bi_reiniciar(iterador_bi_t* iterador) {
    if (!verificar_iterador_bi_valido(iterador)) {
        return ERROR_ITERADOR_INVALIDO;
    }

    iterador->actual = iterador->nodo_inicio;
    iterador->posicion = 0;
    iterador->direccion_avance = true;

    LOG_DEBUG("Iterador reiniciado al inicio");
    return EXITO;
}

resultado_t iterador_bi_ir_final(iterador_bi_t* iterador) {
    if (!verificar_iterador_bi_valido(iterador)) {
        return ERROR_ITERADOR_INVALIDO;
    }

    iterador->actual = ((lista_doble_t*)iterador->lista_original)->cola;
    iterador->posicion = iterador->num_nodos_total > 0 ? iterador->num_nodos_total - 1 : 0;
    iterador->direccion_avance = false;

    LOG_DEBUG("Iterador movido al final");
    return EXITO;
}

resultado_t iterador_bi_obtener_posicion(const iterador_bi_t* iterador, size_t* posicion) {
    if (!verificar_iterador_bi_valido(iterador) || !verificar_puntero_no_nulo(posicion, "posicion")) {
        return ERROR_PARAMETRO_NULO;
    }

    *posicion = iterador->posicion;
    return EXITO;
}

resultado_t iterador_bi_ir_a_posicion(iterador_bi_t* iterador, size_t posicion) {
    if (!verificar_iterador_bi_valido(iterador)) {
        return ERROR_ITERADOR_INVALIDO;
    }

    if (posicion >= iterador->num_nodos_total) {
        LOG_ERROR("Posición %zu fuera de rango (tamaño: %zu)", posicion, iterador->num_nodos_total);
        return ERROR_OPERACION_INVALIDA;
    }

    // Optimización: buscar desde el inicio o final según la posición
    if (posicion < iterador->num_nodos_total / 2) {
        // Buscar desde el inicio
        iterador->actual = iterador->nodo_inicio;
        iterador->posicion = 0;

        while (iterador->posicion < posicion && iterador->actual != NULL) {
            iterador->actual = iterador->actual->siguiente;
            iterador->posicion++;
        }
    } else {
        // Buscar desde el final
        iterador->actual = ((lista_doble_t*)iterador->lista_original)->cola;
        iterador->posicion = iterador->num_nodos_total - 1;

        while (iterador->posicion > posicion && iterador->actual != NULL) {
            iterador->actual = iterador->actual->anterior;
            iterador->posicion--;
        }
    }

    if (iterador->actual == NULL) {
        LOG_ERROR("Error al buscar posición %zu", posicion);
        return ERROR_OPERACION_INVALIDA;
    }

    iterador->direccion_avance = true;
    LOG_DEBUG("Iterador movido a posición %zu", posicion);
    return EXITO;
}

resultado_t iterador_bi_mapear(iterador_bi_t* iterador, iterador_bi_funcion_mapear funcion, lista_doble_t** lista_resultado) {
    if (!verificar_iterador_bi_valido(iterador) || funcion == NULL || lista_resultado == NULL) {
        return ERROR_PARAMETRO_NULO;
    }

    // Crear nueva lista con las mismas funciones
    resultado_t resultado = lista_doble_crear_avanzado(lista_resultado,
                                                      iterador->tamanio_elemento,
                                                      ((lista_doble_t*)iterador->lista_original)->copiar_dato,
                                                      ((lista_doble_t*)iterador->lista_original)->liberar_dato,
                                                      ((lista_doble_t*)iterador->lista_original)->comparar_dato);
    if (resultado != EXITO) {
        return resultado;
    }

    // Guardar estado actual del iterador
    struct nodo_doble_s* actual_original = iterador->actual;
    size_t posicion_original = iterador->posicion;
    bool direccion_original = iterador->direccion_avance;

    // Reiniciar iterador para recorrer toda la lista
    iterador_bi_reiniciar(iterador);

    // Buffer para datos temporales
    void* elemento_actual = malloc(iterador->tamanio_elemento);
    void* elemento_mapeado = malloc(iterador->tamanio_elemento);

    if (elemento_actual == NULL || elemento_mapeado == NULL) {
        free(elemento_actual);
        free(elemento_mapeado);
        lista_doble_liberar(lista_resultado);
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    // Recorrer y mapear
    while (iterador->actual != NULL) {
        resultado = iterador_bi_elemento_actual(iterador, elemento_actual);
        if (resultado != EXITO) {
            break;
        }

        // Aplicar función de mapeo
        funcion(elemento_actual, elemento_mapeado);

        // Insertar en lista resultado
        resultado = lista_doble_insertar_final(*lista_resultado, elemento_mapeado);
        if (resultado != EXITO) {
            break;
        }

        // Avanzar
        resultado = iterador_bi_siguiente(iterador, elemento_actual);
        if (resultado != EXITO && resultado != ERROR_ITERADOR_FINALIZADO) {
            break;
        }
    }

    // Restaurar estado original del iterador
    iterador->actual = actual_original;
    iterador->posicion = posicion_original;
    iterador->direccion_avance = direccion_original;

    // Liberar buffers temporales
    free(elemento_actual);
    free(elemento_mapeado);

    if (resultado != EXITO && resultado != ERROR_ITERADOR_FINALIZADO) {
        lista_doble_liberar(lista_resultado);
        return resultado;
    }

    LOG_DEBUG("Mapeo completado exitosamente");
    return EXITO;
}

resultado_t iterador_bi_filtrar(iterador_bi_t* iterador, iterador_bi_funcion_filtrar predicado, lista_doble_t** lista_resultado) {
    if (!verificar_iterador_bi_valido(iterador) || predicado == NULL || lista_resultado == NULL) {
        return ERROR_PARAMETRO_NULO;
    }

    // Crear nueva lista con las mismas funciones
    resultado_t resultado = lista_doble_crear_avanzado(lista_resultado,
                                                      iterador->tamanio_elemento,
                                                      ((lista_doble_t*)iterador->lista_original)->copiar_dato,
                                                      ((lista_doble_t*)iterador->lista_original)->liberar_dato,
                                                      ((lista_doble_t*)iterador->lista_original)->comparar_dato);
    if (resultado != EXITO) {
        return resultado;
    }

    // Guardar estado actual del iterador
    struct nodo_doble_s* actual_original = iterador->actual;
    size_t posicion_original = iterador->posicion;
    bool direccion_original = iterador->direccion_avance;

    // Reiniciar iterador para recorrer toda la lista
    iterador_bi_reiniciar(iterador);

    // Buffer para datos temporales
    void* elemento_actual = malloc(iterador->tamanio_elemento);
    if (elemento_actual == NULL) {
        lista_doble_liberar(lista_resultado);
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    // Recorrer y filtrar
    resultado_t resultado_iteracion;
    do {
        resultado_iteracion = iterador_bi_elemento_actual(iterador, elemento_actual);
        if (resultado_iteracion != EXITO) {
            break;
        }

        // Aplicar predicado de filtro
        if (predicado(elemento_actual)) {
            resultado = lista_doble_insertar_final(*lista_resultado, elemento_actual);
            if (resultado != EXITO) {
                break;
            }
        }

        // Avanzar
        resultado_iteracion = iterador_bi_siguiente(iterador, elemento_actual);
    } while (resultado_iteracion == EXITO);

    // Restaurar estado original del iterador
    iterador->actual = actual_original;
    iterador->posicion = posicion_original;
    iterador->direccion_avance = direccion_original;

    // Liberar buffer temporal
    free(elemento_actual);

    if (resultado != EXITO) {
        lista_doble_liberar(lista_resultado);
        return resultado;
    }

    LOG_DEBUG("Filtrado completado exitosamente");
    return EXITO;
}

resultado_t iterador_bi_reducir(iterador_bi_t* iterador, iterador_bi_funcion_reducir funcion, void* valor_inicial, void* resultado) {
    if (!verificar_iterador_bi_valido(iterador) || funcion == NULL ||
        !verificar_puntero_no_nulo(valor_inicial, "valor_inicial") ||
        !verificar_puntero_no_nulo(resultado, "resultado")) {
        return ERROR_PARAMETRO_NULO;
    }

    // Guardar estado actual del iterador
    struct nodo_doble_s* actual_original = iterador->actual;
    size_t posicion_original = iterador->posicion;
    bool direccion_original = iterador->direccion_avance;

    // Reiniciar iterador para recorrer toda la lista
    iterador_bi_reiniciar(iterador);

    // Copiar valor inicial al resultado
    memcpy(resultado, valor_inicial, iterador->tamanio_elemento);

    // Buffer para datos temporales
    void* elemento_actual = malloc(iterador->tamanio_elemento);
    if (elemento_actual == NULL) {
        return ERROR_MEMORIA_INSUFICIENTE;
    }

    // Recorrer y reducir
    resultado_t resultado_op = EXITO;
    resultado_t resultado_iteracion;

    do {
        resultado_iteracion = iterador_bi_elemento_actual(iterador, elemento_actual);
        if (resultado_iteracion != EXITO) {
            if (resultado_iteracion != ERROR_ITERADOR_FINALIZADO) {
                resultado_op = resultado_iteracion;
            }
            break;
        }

        // Aplicar función de reducción
        funcion(elemento_actual, resultado);

        // Avanzar
        resultado_iteracion = iterador_bi_siguiente(iterador, elemento_actual);
    } while (resultado_iteracion == EXITO);

    // Restaurar estado original del iterador
    iterador->actual = actual_original;
    iterador->posicion = posicion_original;
    iterador->direccion_avance = direccion_original;

    // Liberar buffer temporal
    free(elemento_actual);

    LOG_DEBUG("Reducción completada exitosamente");
    return resultado_op;
}
