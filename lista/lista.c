/**
 * @file lista.c
 * @brief Implementación de la lista enlazada
 */

#include "lista_privada.h"
#include "verificaciones.h"
#include <stdlib.h>
#include <string.h>

resultado_t lista_crear(lista_t** lista,size_t tamanio_elemento){
    return lista_crear_avanzado(lista,tamanio_elemento,NULL,NULL,NULL);
}

resultado_t lista_crear_avanzado(lista_t** lista,size_t tamanio_elemento,
                                lista_funcion_copiar copiar,
                                lista_funcion_liberar liberar,
                                lista_funcion_comparar comparar){
    if(!verificar_puntero_no_nulo(lista,"lista")){
        return ERROR_PARAMETRO_NULO;
    }
    if(tamanio_elemento==0){
        LOG_ERROR("Tamaño de elemento debe ser mayor a 0");
        return ERROR_PARAMETRO_NULO;
    }
    *lista=(lista_t*)malloc(sizeof(lista_t));
    if(*lista==NULL){
        LOG_ERROR("No se pudo asignar memoria para la lista");
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    (*lista)->cabeza=NULL;
    (*lista)->cola=NULL;
    (*lista)->cantidad_elementos=0;
    (*lista)->tamanio_elemento=tamanio_elemento;
    (*lista)->copiar_dato=copiar;
    (*lista)->liberar_dato=liberar;
    (*lista)->comparar_dato=comparar;

    LOG_DEBUG("Lista creada exitosamente");
    return EXITO;
}

resultado_t lista_establecer_funciones(lista_t* lista,
                                      lista_funcion_copiar copiar,
                                      lista_funcion_liberar liberar,
                                      lista_funcion_comparar comparar){
    if(!verificar_lista_valida(lista)){
        return ERROR_PARAMETRO_NULO;
    }
    lista->copiar_dato=copiar;
    lista->liberar_dato=liberar;
    lista->comparar_dato=comparar;

    LOG_DEBUG("Funciones personalizadas establecidas para la lista");
    return EXITO;
}

resultado_t lista_liberar(lista_t** lista){
    if(!verificar_puntero_no_nulo(lista,"lista") || !verificar_puntero_no_nulo(*lista,"*lista")){
        return ERROR_PARAMETRO_NULO;
    }
    struct nodo_s* actual=(*lista)->cabeza;
    struct nodo_s* siguiente;
    while(actual!=NULL){
        siguiente=actual->siguiente;
        // Usar función personalizada de liberación si está disponible
        if((*lista)->liberar_dato!=NULL){
            (*lista)->liberar_dato(actual->dato);
        }else{
            free(actual->dato);
        }
        free(actual);
        actual=siguiente;
    }
    free(*lista);
    *lista=NULL;

    LOG_DEBUG("Lista liberada exitosamente");
    return EXITO;
}

struct nodo_s* crear_nodo_s(lista_t* lista,const void* dato){
    if(!verificar_lista_valida(lista) || !verificar_puntero_no_nulo(dato,"dato")){
        return NULL;
    }
    struct nodo_s* temp=(struct nodo_s*)malloc(sizeof(struct nodo_s));
    if(temp==NULL){
        LOG_ERROR("No se pudo asignar memoria para el nodo");
        return NULL;
    }
    // Usar función personalizada de copia si está disponible
    if(lista->copiar_dato!=NULL){
        temp->dato=lista->copiar_dato(dato);
        if(temp->dato==NULL){
            LOG_ERROR("Función de copia personalizada retornó NULL");
            free(temp);
            return NULL;
        }
    }else{
        temp->dato=malloc(lista->tamanio_elemento);
        if(temp->dato==NULL){
            LOG_ERROR("No se pudo asignar memoria para los datos del nodo");
            free(temp);
            return NULL;
        }
        memcpy(temp->dato,dato,lista->tamanio_elemento);
    }
    temp->siguiente=NULL;
    return temp;
}

resultado_t lista_insertar_final(lista_t* lista,const void* dato){
    resultado_t resultado=verificar_parametros_lista(lista,dato);
    if(resultado!=EXITO){
        return resultado;
    }
    struct nodo_s* nuevo=crear_nodo_s(lista,dato);
    if(nuevo==NULL){
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    if(lista->cabeza==NULL){
        lista->cabeza=nuevo;
        lista->cola=nuevo;
    }else{
        lista->cola->siguiente=nuevo;
        lista->cola=nuevo;
    }
    lista->cantidad_elementos++;
    LOG_DEBUG("Elemento insertado al final");
    return EXITO;
}

resultado_t lista_insertar_inicio(lista_t* lista,const void* dato){
    resultado_t resultado=verificar_parametros_lista(lista,dato);
    if(resultado!=EXITO){
        return resultado;
    }
    struct nodo_s* nuevo=crear_nodo_s(lista,dato);
    if(nuevo==NULL){
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    if(lista->cabeza==NULL){
        lista->cabeza=nuevo;
        lista->cola=nuevo;
    }else{
        nuevo->siguiente=lista->cabeza;
        lista->cabeza=nuevo;
    }
    lista->cantidad_elementos++;
    LOG_DEBUG("Elemento insertado al inicio");
    return EXITO;
}

resultado_t lista_eliminar_valor(lista_t* lista,const void* dato){
    resultado_t resultado=verificar_parametros_lista(lista,dato);
    if(resultado!=EXITO){
        return resultado;
    }
    if(lista->cantidad_elementos==0){
        LOG_ERROR("No se puede eliminar de una lista vacía");
        return ERROR_LISTA_VACIA;
    }
    struct nodo_s* actual=lista->cabeza;
    struct nodo_s* anterior=NULL;
    while(actual!=NULL){
        int son_iguales;
        // Usar función personalizada de comparación si está disponible
        if(lista->comparar_dato!=NULL){
            son_iguales=(lista->comparar_dato(actual->dato,dato)==0);
        }else{
            son_iguales=(memcmp(actual->dato,dato,lista->tamanio_elemento)==0);
        }
        if(son_iguales){
            if(anterior==NULL){
                // Eliminar cabeza
                lista->cabeza=actual->siguiente;
                if(lista->cabeza==NULL){
                    lista->cola=NULL;
                }
            }else{
                anterior->siguiente=actual->siguiente;
                if(actual==lista->cola){
                    lista->cola=anterior;
                }
            }
            // Usar función personalizada de liberación si está disponible
            if(lista->liberar_dato!=NULL){
                lista->liberar_dato(actual->dato);
            }else{
                free(actual->dato);
            }
            free(actual);
            lista->cantidad_elementos--;
            LOG_DEBUG("Elemento eliminado de la lista");
            return EXITO;
        }
        anterior=actual;
        actual=actual->siguiente;
    }
    LOG_DEBUG("Elemento no encontrado para eliminar");
    return ERROR_ELEMENTO_NO_ENCONTRADO;
}

resultado_t lista_obtener_tamanio(const lista_t* lista,size_t* tamanio){
    if(!verificar_lista_valida(lista) || !verificar_puntero_no_nulo(tamanio,"tamanio")){
        return ERROR_PARAMETRO_NULO;
    }
    *tamanio=lista->cantidad_elementos;
    return EXITO;
}

resultado_t lista_obtener_cabeza(const lista_t* lista,void** dato_cabeza){
    if(!verificar_lista_valida(lista) || !verificar_puntero_no_nulo(dato_cabeza,"dato_cabeza")){
        return ERROR_PARAMETRO_NULO;
    }
    if(lista->cabeza==NULL){
        LOG_ERROR("No se puede obtener cabeza de lista vacía");
        return ERROR_LISTA_VACIA;
    }
    *dato_cabeza=lista->cabeza->dato;
    return EXITO;
}

resultado_t lista_obtener_nodo_cabeza(const lista_t* lista,void** nodo_cabeza){
    if(!verificar_lista_valida(lista) || !verificar_puntero_no_nulo(nodo_cabeza,"nodo_cabeza")){
        return ERROR_PARAMETRO_NULO;
    }
    if(lista->cabeza==NULL){
        LOG_ERROR("No se puede obtener nodo cabeza de lista vacía");
        return ERROR_LISTA_VACIA;
    }
    *nodo_cabeza=lista->cabeza;
    return EXITO;
}
