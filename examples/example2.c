/**
 * @file ejemplo_persona.c
 * @brief Ejemplo de uso de liblista con structs complejos y lista doble
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <liblista/lista_doble.h>
#include <liblista/iterador_bi.h>

typedef struct{
    char* nombre;
    int edad;
    double salario;
}Persona;

// Función para copiar una Persona
void* copiar_persona(const void* dato){
    const Persona* original=(const Persona*)dato;
    Persona* copia=malloc(sizeof(Persona));

    copia->nombre=malloc(strlen(original->nombre)+1);
    strcpy(copia->nombre,original->nombre);
    copia->edad=original->edad;
    copia->salario=original->salario;

    return copia;
}
// Función para liberar una Persona
void liberar_persona(void* dato){
    Persona* persona=(Persona*)dato;
    free(persona->nombre);
    free(persona);
}
// Función para comparar Personas (por nombre)
int comparar_persona(const void* a,const void* b){
    const Persona* pa=(const Persona*)a;
    const Persona* pb=(const Persona*)b;
    return strcmp(pa->nombre,pb->nombre);
}
// Función para imprimir una Persona
void imprimir_persona(const Persona* persona){
    printf("Nombre: %s, Edad: %d, Salario: %.2f\n",
           persona->nombre,persona->edad,persona->salario);
}

int main(){
    printf("=== Ejemplo con struct Persona ===\n");

    lista_doble_t* lista=NULL;
    iterador_bi_t* iterador=NULL;
    resultado_t resultado;
    // Crear lista con funciones personalizadas
    resultado=lista_doble_crear_avanzado(&lista,sizeof(Persona),copiar_persona,liberar_persona,comparar_persona);
    if(resultado!=EXITO){
        printf("Error creando lista: %d\n",resultado);
        return 1;
    }
    // Crear algunas personas
    Persona personas[]={
        {"Juan Pérez",30,50000.0},
        {"María García",25,45000.0},
        {"Carlos López",35,60000.0}
    };
    // Insertar personas en la lista
    for(int i=0;i<3;i++){
        resultado=lista_doble_insertar_final(lista,&personas[i]);
        if(resultado!=EXITO){
            printf("Error insertando persona: %d\n",resultado);
            lista_doble_liberar(&lista);
            return 1;
        }
    }
    printf("Personas en la lista:\n");
    // Recorrer lista con iterador
    iterador_bi_crear(lista,&iterador);
    Persona persona_actual;
    bool tiene_siguiente;
    do{
        iterador_bi_tiene_siguiente(iterador,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_bi_siguiente(iterador,&persona_actual);
            imprimir_persona(&persona_actual);
        }
    }while(tiene_siguiente);
    do{
        iterador_bi_tiene_anterior(iterador,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_bi_anterior(iterador,&persona_actual);
            imprimir_persona(&persona_actual);
        }
    }while(tiene_siguiente);
    // Buscar y eliminar una persona
    Persona persona_a_eliminar={"María García",0,0};
    resultado=lista_doble_eliminar_valor(lista,&persona_a_eliminar);
    if(resultado==EXITO){
        printf("\nPersona eliminada exitosamente\n");
    }else{
        printf("\nNo se pudo eliminar la persona: %d\n",resultado);
    }
    // Mostrar lista después de eliminar
    printf("\nLista después de eliminar:\n");
    iterador_bi_reiniciar(iterador);
    do{
        iterador_bi_tiene_siguiente(iterador,&tiene_siguiente);
        if(tiene_siguiente){
            iterador_bi_siguiente(iterador,&persona_actual);
            imprimir_persona(&persona_actual);
        }
    }while(tiene_siguiente);
    // Liberar recursos
    iterador_bi_liberar(&iterador);
    lista_doble_liberar(&lista);
    printf("Ejemplo completado exitosamente!\n");
    return 0;
}
