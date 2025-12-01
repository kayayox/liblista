/**
 * @file lista_doble.c
 * @brief Implementación de la lista doblemente enlazada
 */

#include <stdio.h>
#include "lista_doble_privada.h"

struct nodo_doble_s* lista_doble_crear_nodo(lista_doble_t* lista,const void* dato){
    if(!verificar_lista_doble_valida(lista) || !verificar_puntero_no_nulo(dato,"dato")){
        return NULL;
    }
    struct nodo_doble_s* temp=(struct nodo_doble_s*)malloc(sizeof(struct nodo_doble_s));
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
    temp->anterior=NULL;
    return temp;
}

struct nodo_doble_s* lista_doble_buscar_nodo(const lista_doble_t* lista,const void* dato){
    if(verificar_parametros_lista_doble(lista,dato)!=EXITO){
        return NULL;
    }
    struct nodo_doble_s* temp=lista->cabeza;
    if(temp==NULL){
        LOG_ERROR("No se puede obtener cabeza de lista vacía");
        return NULL;
    }
    while(temp!=NULL){
        if(lista->comparar_dato!=NULL){
            if(lista->comparar_dato(temp->dato,dato)==0)return temp;
        }else{
            if(memcmp(temp->dato,dato,lista->tamanio_elemento)==0)return temp;
        }
        temp=temp->siguiente;
    }
    LOG_DEBUG("Elemento no encontrado");
    return NULL;
}

resultado_t lista_doble_crear(lista_doble_t** lista, size_t tamanio_elemento){
    return lista_doble_crear_avanzado(lista,tamanio_elemento,NULL,NULL,NULL);
}

resultado_t lista_doble_crear_avanzado(lista_doble_t** lista, size_t tamanio_elemento,
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
    *lista=(lista_doble_t*)malloc(sizeof(lista_doble_t));
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

resultado_t lista_doble_liberar(lista_doble_t** lista){
    if(!verificar_puntero_no_nulo(lista,"lista") || !verificar_puntero_no_nulo(*lista,"*lista")){
        return ERROR_PARAMETRO_NULO;
    }
    struct nodo_doble_s* actual=(*lista)->cabeza;
    struct nodo_doble_s* siguiente;
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

resultado_t lista_doble_insertar_final(lista_doble_t* lista, const void* dato){
    resultado_t resultado=verificar_parametros_lista_doble(lista,dato);
    if(resultado!=EXITO){
        return resultado;
    }
    struct nodo_doble_s* nuevo=lista_doble_crear_nodo(lista,dato);
    if(nuevo==NULL){
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    if(lista->cabeza==NULL){
        lista->cabeza=nuevo;
        lista->cola=nuevo;
    }else{
        lista->cola->siguiente=nuevo;
        nuevo->anterior=lista->cola;
        lista->cola=nuevo;
    }
    lista->cantidad_elementos++;
    LOG_DEBUG("Elemento insertado al final");
    return EXITO;
}

resultado_t lista_doble_insertar_inicio(lista_doble_t* lista, const void* dato){
    resultado_t resultado=verificar_parametros_lista_doble(lista,dato);
    if(resultado!=EXITO){
        return resultado;
    }
    struct nodo_doble_s* nuevo=lista_doble_crear_nodo(lista,dato);
    if(nuevo==NULL){
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    if(lista->cabeza==NULL){
        lista->cabeza=nuevo;
        lista->cola=nuevo;
    }else{
        nuevo->siguiente=lista->cabeza;
        lista->cabeza->anterior=nuevo;
        lista->cabeza=nuevo;
    }
    lista->cantidad_elementos++;
    LOG_DEBUG("Elemento insertado al inicio");
    return EXITO;
}

resultado_t lista_doble_eliminar_valor(lista_doble_t* lista, const void* dato){
    resultado_t resultado=verificar_parametros_lista_doble(lista,dato);
    if(resultado!=EXITO){
        return resultado;
    }
    if(lista->cantidad_elementos==0){
        LOG_ERROR("No se puede eliminar de una lista vacía");
        return ERROR_LISTA_VACIA;
    }
    struct nodo_doble_s* actual=lista->cabeza;
    struct nodo_doble_s* anterior=NULL;
    while(actual!=NULL){
        int son_iguales;
        if(lista->comparar_dato!=NULL){
            son_iguales=(lista->comparar_dato(actual->dato,dato)==0);
        }else{
            son_iguales=(memcmp(actual->dato,dato,lista->tamanio_elemento)==0);
        }
        if(son_iguales){
            if(anterior==NULL){
                lista->cabeza=actual->siguiente;
                if(lista->cabeza!=NULL){
                    lista->cabeza->anterior=NULL;
                }
            }else{
                anterior->siguiente=actual->siguiente;
                if(actual->siguiente!=NULL){
                    actual->siguiente->anterior=anterior;
                }
            }
            if(actual==lista->cola){
                lista->cola=anterior;
            }
            if(lista->liberar_dato!=NULL){
                lista->liberar_dato(actual->dato);
            }else{
                free(actual->dato);
            }
            free(actual);
            lista->cantidad_elementos--;
            LOG_DEBUG("Elemento eliminado de lista doble");
            return EXITO;
        }
        anterior=actual;
        actual=actual->siguiente;
    }
    LOG_DEBUG("Elemento no encontrado en lista doble");
    return ERROR_ELEMENTO_NO_ENCONTRADO;
}

resultado_t lista_doble_obtener_tamanio(const lista_doble_t* lista, size_t* tamanio){
    if(!verificar_lista_doble_valida(lista) || !verificar_puntero_no_nulo(tamanio,"tamanio"))return ERROR_PARAMETRO_NULO;
    *tamanio=lista->cantidad_elementos;
    return EXITO;
}

resultado_t lista_doble_obtener_cabeza(const lista_doble_t* lista, void** dato_cabeza){
    if(!verificar_lista_doble_valida(lista) || !verificar_puntero_no_nulo(dato_cabeza,"dato_cabeza"))return ERROR_PARAMETRO_NULO;
    if(lista->cabeza==NULL)return ERROR_LISTA_VACIA;
    *dato_cabeza=lista->cabeza->dato;
    return EXITO;
}

resultado_t lista_doble_obtener_cola(const lista_doble_t* lista, void** dato_cola){
    if(!verificar_lista_doble_valida(lista) || !verificar_puntero_no_nulo(dato_cola,"dato_cola"))return ERROR_PARAMETRO_NULO;
    if(lista->cola==NULL)return ERROR_LISTA_VACIA;
    *dato_cola=lista->cola->dato;
    return EXITO;
}
