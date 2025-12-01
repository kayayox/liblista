#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/lista.h"
#include "../include/iterador.h"
#include "../include/resultados.h"

// Función auxiliar para imprimir resultados de pruebas
void imprimir_resultado(const char* prueba,resultado_t resultado){
    const char* mensajes[]={
        "EXITO",
        "ERROR_PARAMETRO_NULO",
        "ERROR_MEMORIA_INSUFICIENTE",
        "ERROR_ITERADOR_INVALIDO",
        "ERROR_LISTA_VACIA",
        "ERROR_ELEMENTO_NO_ENCONTRADO",
        "ERROR_OPERACION_INVALIDA",
        "ERROR_ITERADOR_FINALIZADO"
    };
    printf("Prueba: %s -> %s\n",prueba, mensajes[resultado]);
}
// Pruebas básicas de la lista
void prueba_lista_crear_liberar(){
    printf("\n=== Prueba: Crear y Liberar Lista ===\n");

    lista_t* lista=NULL;
    resultado_t resultado;
    // Prueba creación
    resultado=lista_crear(&lista,sizeof(int));
    imprimir_resultado("Crear lista con enteros",resultado);
    assert(resultado==EXITO);
    assert(lista!=NULL);
    // Prueba liberación
    resultado=lista_liberar(&lista);
    imprimir_resultado("Liberar lista",resultado);
    assert(resultado==EXITO);
    assert(lista==NULL);
    // Prueba parámetros nulos
    resultado=lista_crear(NULL,sizeof(int));
    imprimir_resultado("Crear lista con NULL",resultado);
    assert(resultado==ERROR_PARAMETRO_NULO);
}

void prueba_lista_insertar_elementos(){
    printf("\n=== Prueba: Insertar Elementos ===\n");

    lista_t* lista=NULL;
    resultado_t resultado;
    resultado=lista_crear(&lista,sizeof(int));
    assert(resultado==EXITO);
    // Insertar elementos al final
    int valores[]={10,20,30,40,50};
    for(int i=0;i<5;i++){
        resultado=lista_insertar_final(lista,&valores[i]);
        printf("Insertar %d al final: ",valores[i]);
        imprimir_resultado("",resultado);
        assert(resultado==EXITO);
    }
    // Insertar elementos al inicio
    int primer_valor=5;
    resultado=lista_insertar_inicio(lista,&primer_valor);
    imprimir_resultado("Insertar 5 al inicio",resultado);
    assert(resultado==EXITO);
    // Verificar tamaño
    size_t tamanio;
    resultado=lista_obtener_tamanio(lista,&tamanio);
    imprimir_resultado("Obtener tamaño",resultado);
    assert(resultado==EXITO);
    assert(tamanio==6);
    printf("Tamaño de la lista: %zu\n",tamanio);

    lista_liberar(&lista);
}

void prueba_lista_obtener_cabeza(){
    printf("\n=== Prueba: Obtener Cabeza ===\n");

    lista_t* lista=NULL;
    resultado_t resultado;
    resultado=lista_crear(&lista,sizeof(int));
    assert(resultado==EXITO);
    // Prueba con lista vacía
    int* dato_cabeza=NULL;
    resultado=lista_obtener_cabeza(lista,(void**)&dato_cabeza);
    imprimir_resultado("Obtener cabeza (lista vacía)",resultado);
    assert(resultado==ERROR_LISTA_VACIA);
    // Insertar elementos
    int valor1=100,valor2=200;
    lista_insertar_final(lista,&valor1);
    lista_insertar_final(lista,&valor2);
    // Obtener cabeza
    resultado=lista_obtener_cabeza(lista,(void**)&dato_cabeza);
    imprimir_resultado("Obtener cabeza",resultado);
    assert(resultado==EXITO);
    assert(dato_cabeza!=NULL);
    assert(*dato_cabeza==100);
    printf("Valor de la cabeza: %d\n",*dato_cabeza);

    lista_liberar(&lista);
}

void prueba_lista_eliminar_elemento(){
    printf("\n=== Prueba: Eliminar Elemento ===\n");

    lista_t* lista=NULL;
    resultado_t resultado;
    resultado=lista_crear(&lista,sizeof(int));
    assert(resultado==EXITO);
    // Insertar elementos
    int valores[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Eliminar elemento existente
    int valor_a_eliminar=3;
    resultado=lista_eliminar_valor(lista,&valor_a_eliminar);
    imprimir_resultado("Eliminar valor 3",resultado);
    assert(resultado==EXITO);
    // Verificar tamaño después de eliminar
    size_t tamanio;
    lista_obtener_tamanio(lista,&tamanio);
    assert(tamanio==4);
    printf("Tamaño después de eliminar: %zu\n",tamanio);
    // Intentar eliminar elemento no existente
    int valor_inexistente=99;
    resultado=lista_eliminar_valor(lista,&valor_inexistente);
    imprimir_resultado("Eliminar valor 99 (no existe)",resultado);
    assert(resultado==ERROR_ELEMENTO_NO_ENCONTRADO);

    lista_liberar(&lista);
}
// Pruebas del iterador
void prueba_iterador_crear_liberar(){
    printf("\n=== Prueba: Crear y Liberar Iterador ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista con elementos
    lista_crear(&lista,sizeof(int));
    int valores[]={10,20,30};
    for(int i=0;i<3;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Crear iterador
    resultado=iterador_crear(lista,&iterador);
    imprimir_resultado("Crear iterador",resultado);
    assert(resultado==EXITO);
    assert(iterador!=NULL);
    // Liberar iterador
    resultado=iterador_liberar(&iterador);
    imprimir_resultado("Liberar iterador",resultado);
    assert(resultado==EXITO);
    assert(iterador==NULL);
    // Prueba con parámetros nulos
    resultado=iterador_crear(NULL,&iterador);
    imprimir_resultado("Crear iterador con lista NULL",resultado);
    assert(resultado==ERROR_PARAMETRO_NULO);

    lista_liberar(&lista);
}

void prueba_iterador_recorrido(){
    printf("\n=== Prueba: Recorrido con Iterador ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista con elementos
    lista_crear(&lista,sizeof(int));
    int valores[]={1,2,3,4,5};
    for(int i=0;i<256;i++){
        int* x=&i;
        lista_insertar_final(lista,x);
    }
    // Crear iterador
    iterador_crear(lista,&iterador);
    // Recorrer la lista
    printf("Recorriendo lista:\n");
    int elemento=0;
    bool tiene_siguiente=true;
    while(tiene_siguiente){
        iterador_tiene_siguiente(iterador,&tiene_siguiente);
        if(tiene_siguiente){
            resultado=iterador_siguiente(iterador,&elemento);
            if(resultado==EXITO){
                printf("  Elemento: %d\n",elemento);
            }
        }
    }
    // Verificar que el iterador está al final
    iterador_tiene_siguiente(iterador,&tiene_siguiente);
    assert(!tiene_siguiente);
    // Intentar obtener siguiente cuando ya terminó
    resultado=iterador_siguiente(iterador,&elemento);
    imprimir_resultado("Obtener siguiente (iterador finalizado)",resultado);
    assert(resultado==ERROR_ITERADOR_FINALIZADO);

    iterador_liberar(&iterador);
    lista_liberar(&lista);
}

void prueba_iterador_elemento_actual(){
    printf("\n=== Prueba: Elemento Actual del Iterador ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista con elementos
    lista_crear(&lista,sizeof(int));
    int valores[]={100,200,300};
    for(int i=0;i<3;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Crear iterador
    iterador_crear(lista,&iterador);
    // Obtener elemento actual (debería ser el primero)
    int elemento;
    resultado=iterador_elemento_actual(iterador,&elemento);
    imprimir_resultado("Obtener elemento actual",resultado);
    assert(resultado==EXITO);
    assert(elemento==100);
    printf("Elemento actual: %d\n",elemento);
    // Avanzar y verificar elemento actual
    iterador_siguiente(iterador,&elemento); // Avanzar al segundo
    iterador_elemento_actual(iterador,&elemento);
    assert(elemento==200);
    printf("Elemento actual después de avanzar: %d\n",elemento);

    iterador_liberar(&iterador);
    lista_liberar(&lista);
}

void prueba_iterador_reiniciar(){
    printf("\n=== Prueba: Reiniciar Iterador ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista con elementos
    lista_crear(&lista,sizeof(int));
    int valores[]={1,2,3};
    for(int i=0;i<3;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Crear iterador y recorrer
    iterador_crear(lista,&iterador);
    int elemento;
    for(int i=0;i<3;i++){
        iterador_siguiente(iterador,&elemento);
    }
    // Verificar que llegamos al final
    bool tiene_siguiente;
    iterador_tiene_siguiente(iterador,&tiene_siguiente);
    assert(!tiene_siguiente);
    // Reiniciar iterador
    resultado=iterador_reiniciar(iterador);
    imprimir_resultado("Reiniciar iterador",resultado);
    assert(resultado==EXITO);
    // Verificar que podemos recorrer de nuevo
    iterador_tiene_siguiente(iterador,&tiene_siguiente);
    assert(tiene_siguiente);
    iterador_siguiente(iterador,&elemento);
    assert(elemento==1);
    printf("Primer elemento después de reiniciar: %d\n",elemento);

    iterador_liberar(&iterador);
    lista_liberar(&lista);
}

void prueba_lista_con_strings(){
    printf("\n=== Prueba: Lista con Strings ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista para strings
    resultado=lista_crear(&lista,sizeof(char*));
    imprimir_resultado("Crear lista para strings",resultado);
    assert(resultado==EXITO);
    // Insertar strings
    char* strings[]={"Hola","Mundo","Programación","C"};
    for(int i=0;i<4;i++){
        resultado=lista_insertar_final(lista,&strings[i]);
        printf("Insertar string: %s -> ",strings[i]);
        imprimir_resultado("",resultado);
        assert(resultado==EXITO);
    }
    // Recorrer con iterador
    iterador_crear(lista,&iterador);
    printf("Strings en la lista:\n");
    char* str;
    bool tiene_siguiente=true;
    while(tiene_siguiente){
        iterador_tiene_siguiente(iterador,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_siguiente(iterador,&str);
            printf("  %s\n",str);
        }
    }
    iterador_liberar(&iterador);
    lista_liberar(&lista);
}

void duplicar_valor(const void* elemento,void* resultado){
    int valor=*(int*)elemento;
    *(int*)resultado=valor*2;
    printf("Mapeando %d -> %d\n",valor,valor*2);
}
// Función de mapeo: cuadrado
void elevar_cuadrado(const void* elemento,void* resultado){
    int valor=*(int*)elemento;
    *(int*)resultado=valor*valor;
    printf("Mapeando %d -> %d\n",valor,valor*valor);
}
// Función de filtro: solo pares
bool filtrar_pares(const void* elemento){
    int valor=*(int*)elemento;
    return (valor%2)==0;
}
// Función de filtro: mayores que 2
bool filtrar_mayores_que_dos(const void* elemento){
    int valor=*(int*)elemento;
    return valor>2;
}
// Función de reducción: sumar
void sumar_elementos(const void* elemento,void* acumulador){
    int valor=*(int*)elemento;
    *(int*)acumulador+=valor;
}

void prueba_iterador_mapear(){
    printf("\n=== Prueba: Iterador Mapear ===\n");

    lista_t* lista=NULL;
    lista_t* lista_mapeada=NULL;
    iterador_t* iterador=NULL;
    // Crear lista con datos de prueba
    lista_crear(&lista,sizeof(int));
    int valores[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Crear iterador y mapear usando la función definida
    iterador_crear(lista,&iterador);
    resultado_t resultado=iterador_mapear(iterador,elevar_cuadrado,&lista_mapeada);

    imprimir_resultado("Mapear (duplicar valores)",resultado);
    assert(resultado==EXITO);
    assert(lista_mapeada!=NULL);
    // Verificar resultados
    size_t tamanio;
    lista_obtener_tamanio(lista_mapeada,&tamanio);
    assert(tamanio==5);
    printf("Mapeo completado - tamaño lista resultado: %zu\n",tamanio);
    // Verificar valores mapeados
    iterador_t* iter_mapeado;
    iterador_crear(lista_mapeada,&iter_mapeado);
    int valor;
    for(int i=0;i<5;i++){
        iterador_siguiente(iter_mapeado,&valor);
        assert(valor==valores[i]*valores[i]);
        printf("Valor %d: %d (esperado: %d)\n",i,valor,valores[i]*valores[i]);
    }
    iterador_liberar(&iterador);
    iterador_liberar(&iter_mapeado);
    lista_liberar(&lista);
    lista_liberar(&lista_mapeada);
}

void prueba_iterador_filtrar(){
    printf("\n=== Prueba: Iterador Filtrar ===\n");

    lista_t* lista=NULL;
    lista_t* lista_filtrada=NULL;
    iterador_t* iterador=NULL;
    // Crear lista con datos de prueba
    lista_crear(&lista,sizeof(int));
    int valores[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Crear iterador y filtrar
    iterador_crear(lista,&iterador);
    resultado_t resultado=iterador_filtrar(iterador,filtrar_pares,&lista_filtrada);
    imprimir_resultado("Filtrar (solo pares)",resultado);
    assert(resultado==EXITO);
    assert(lista_filtrada!=NULL);
    // Verificar resultados - deberían quedar solo 2 y 4
    size_t tamanio;
    lista_obtener_tamanio(lista_filtrada,&tamanio);
    assert(tamanio==2);
    printf("Filtrado completado - elementos filtrados: %zu\n",tamanio);

    iterador_liberar(&iterador);
    lista_liberar(&lista);
    lista_liberar(&lista_filtrada);
}

void prueba_iterador_reducir(){
    printf("\n=== Prueba: Iterador Reducir ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    // Crear lista con datos de prueba
    lista_crear(&lista,sizeof(int));
    int valores[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        lista_insertar_final(lista,&valores[i]);
    }
    // Crear iterador y reducir
    iterador_crear(lista,&iterador);
    int resultado_suma=0;
    resultado_t resultado=iterador_reducir(iterador,sumar_elementos,&resultado_suma,&resultado_suma);
    imprimir_resultado("Reducir (sumar elementos)",resultado);
    assert(resultado==EXITO);
    assert(resultado_suma==15); // 1+2+3+4+5 = 15
    printf("Reducción completada - suma total: %d\n",resultado_suma);

    iterador_liberar(&iterador);
    lista_liberar(&lista);
}

int main(){
    printf("=== INICIANDO PRUEBAS DE LIBLISTA ===\n");

    // Ejecutar pruebas
    prueba_lista_crear_liberar();
    prueba_lista_insertar_elementos();
    prueba_lista_obtener_cabeza();
    prueba_lista_eliminar_elemento();

    prueba_iterador_crear_liberar();
    prueba_iterador_recorrido();
    prueba_iterador_elemento_actual();
    prueba_iterador_reiniciar();

    prueba_iterador_mapear();
    prueba_iterador_filtrar();
    prueba_iterador_reducir();

    prueba_lista_con_strings();

    printf("\n=== TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE ===\n");
    return 0;
}
