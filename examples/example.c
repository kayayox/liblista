/**
 * @file example.c
 * @brief Ejemplo de uso de la librería liblista
 */

#include <stdio.h>
#include <liblista/lista.h>
#include <liblista/iterador.h>
#include <liblista/resultados.h>

// Función para duplicar valores (para mapear)
void duplicar_valor(const void* elemento,void* resultado){
    int valor=*(int*)elemento;
    *(int*)resultado=valor * 2;
}
// Función para filtrar pares
bool filtrar_pares(const void* elemento){
    int valor=*(int*)elemento;
    return (valor%2)==0;
}
// Función para sumar elementos (para reducir)
void sumar_elementos(const void* elemento,void* acumulador){
    int valor=*(int*)elemento;
    *(int*)acumulador+=valor;
}

int main(){
    printf("=== Ejemplo de uso de liblista ===\n");

    lista_t* lista=NULL;
    iterador_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista
    resultado=lista_crear(&lista,sizeof(int));
    if(resultado!=EXITO) {
        printf("Error creando lista: %d\n",resultado);
        return 1;
    }
    // Insertar elementos
    int valores[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        resultado=lista_insertar_final(lista,&valores[i]);
        if(resultado!=EXITO){
            printf("Error insertando elemento: %d\n",resultado);
            lista_liberar(&lista);
            return 1;
        }
    }
    printf("Lista creada con 5 elementos\n");
    // Recorrer con iterador
    iterador_crear(lista,&iterador);
    printf("Elementos de la lista: ");

    int elemento;
    bool tiene_siguiente;
    do{
        iterador_tiene_siguiente(iterador,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_siguiente(iterador,&elemento);
            printf("%d ",elemento);
        }
    }while(tiene_siguiente);
    printf("\n");
    // Ejemplo de mapeo
    lista_t* lista_duplicada=NULL;
    iterador_reiniciar(iterador);
    iterador_mapear(iterador,duplicar_valor,&lista_duplicada);

    printf("Elementos duplicados: ");
    iterador_t* iter_dup;
    iterador_crear(lista_duplicada,&iter_dup);
    do{
        iterador_tiene_siguiente(iter_dup,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_siguiente(iter_dup,&elemento);
            printf("%d ",elemento);
        }
    }while(tiene_siguiente);
    printf("\n");
    // Ejemplo de filtrado
    lista_t* lista_pares=NULL;
    iterador_reiniciar(iterador);
    iterador_filtrar(iterador,filtrar_pares,&lista_pares);

    printf("Elementos pares: ");
    iterador_t* iter_pares;
    iterador_crear(lista_pares,&iter_pares);
    do{
        iterador_tiene_siguiente(iter_pares,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_siguiente(iter_pares,&elemento);
            printf("%d ",elemento);
        }
    }while(tiene_siguiente);
    printf("\n");
    // Ejemplo de reducción
    int suma=0;
    iterador_reiniciar(iterador);
    iterador_reducir(iterador,sumar_elementos,&suma,&suma);

    printf("Suma de todos los elementos: %d\n",suma);
    // Liberar recursos
    iterador_liberar(&iterador);
    iterador_liberar(&iter_dup);
    iterador_liberar(&iter_pares);
    lista_liberar(&lista);
    lista_liberar(&lista_duplicada);
    lista_liberar(&lista_pares);

    printf("Ejemplo completado exitosamente!\n");
    return 0;
}
