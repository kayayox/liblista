Uso Basico
Lista Simple
c

#include <liblista/lista.h>
#include <liblista/iterador.h>

lista_t* lista;
resultado_t res = lista_crear(&lista, sizeof(int));

// Insertar elementos
int valores[] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    lista_insertar_final(lista, &valores[i]);
}

// Recorrer con iterador
iterador_t* iter;
iterador_crear(lista, &iter);

int elemento;
bool tiene_siguiente;
do {
    iterador_tiene_siguiente(iter, &tiene_siguiente);
    if (tiene_siguiente) {
        iterador_siguiente(iter, &elemento);
        printf("%d ", elemento);
    }
} while (tiene_siguiente);

// Liberar recursos
iterador_liberar(&iter);
lista_liberar(&lista);

Lista Doblemente Enlazada
c

#include <liblista/lista_doble.h>
#include <liblista/iterador_bi.h>

lista_doble_t* lista;
resultado_t res = lista_doble_crear(&lista, sizeof(int));

// Insertar elementos
int valores[] = {10, 20, 30, 40, 50};
for (int i = 0; i < 5; i++) {
    lista_doble_insertar_final(lista, &valores[i]);
}

// Recorrer bidireccionalmente
iterador_bi_t* iter_bi;
iterador_bi_crear(lista, &iter_bi);

// Avanzar
int elemento;
while (iterador_bi_siguiente(iter_bi, &elemento) == EXITO) {
    printf("%d ", elemento);
}

// Retroceder
iterador_bi_ir_final(iter_bi);
while (iterador_bi_anterior(iter_bi, &elemento) == EXITO) {
    printf("%d ", elemento);
}

// Liberar recursos
iterador_bi_liberar(&iter_bi);
lista_doble_liberar(&lista);

Estructuras Personalizadas
c

typedef struct {
    char* nombre;
    int edad;
    double salario;
} Persona;

// Funciones personalizadas para la lista
void* copiar_persona(const void* dato) {
    const Persona* original = (const Persona*)dato;
    Persona* copia = malloc(sizeof(Persona));
    copia->nombre = strdup(original->nombre);
    copia->edad = original->edad;
    copia->salario = original->salario;
    return copia;
}

void liberar_persona(void* dato) {
    Persona* persona = (Persona*)dato;
    free(persona->nombre);
    free(persona);
}

int comparar_persona(const void* a, const void* b) {
    const Persona* pa = (const Persona*)a;
    const Persona* pb = (const Persona*)b;
    return strcmp(pa->nombre, pb->nombre);
}

// Uso con funciones personalizadas
lista_t* lista_personas;
lista_crear_avanzado(&lista_personas, sizeof(Persona),
                     copiar_persona, liberar_persona, comparar_persona);

API Principal

Lista Simple
Función	Descripción	Complejidad
lista_crear()	Crear nueva lista	O(1)
lista_crear_avanzado()	Crear lista con funciones personalizadas	O(1)
lista_liberar()	Liberar recursos	O(n)
lista_insertar_final()	Insertar al final	O(1)
lista_insertar_inicio()	Insertar al inicio	O(1)
lista_eliminar_valor()	Eliminar por valor	O(n)
lista_obtener_tamanio()	Obtener tamaño	O(1)
lista_obtener_cabeza()	Obtener elemento cabeza	O(1)

Lista Doblemente Enlazada
Función	Descripcion	Complejidad
lista_doble_crear()	Crear nueva lista doble	O(1)
lista_doble_crear_avanzado()	Crear lista doble con funciones personalizadas	O(1)
lista_doble_liberar()	Liberar recursos	O(n)
lista_doble_insertar_final()	Insertar al final	O(1)
lista_doble_insertar_inicio()	Insertar al inicio	O(1)
lista_doble_eliminar_valor()	Eliminar por valor	O(n)
lista_doble_obtener_tamanio()	Obtener tamaño	O(1)
lista_doble_obtener_cabeza()	Obtener elemento cabeza	O(1)
lista_doble_obtener_cola()	Obtener elemento cola	O(1)

Iterador Simple
Función	Descripcion	Complejidad
iterador_crear()	Crear iterador	O(1)
iterador_liberar()	Liberar iterador	O(1)
iterador_siguiente()	Avanzar y obtener elemento	O(1)
iterador_tiene_siguiente()	Verificar si hay más elementos	O(1)
iterador_elemento_actual()	Obtener elemento actual	O(1)
iterador_insertar_despues()	Insertar después del actual	O(1)
iterador_insertar_antes()	Insertar antes del actual	O(1)
iterador_reiniciar()	Reiniciar iterador	O(1)
iterador_mapear()	Transformar elementos (map)	O(n)
iterador_filtrar()	Filtrar elementos (filter)	O(n)
iterador_reducir()	Reducir a un valor (reduce)	O(n)

Iterador Bidireccional
Función	Descripcion	Complejidad
iterador_bi_crear()	Crear iterador bidireccional	O(1)
iterador_bi_liberar()	Liberar iterador	O(1)
iterador_bi_siguiente()	Avanzar y obtener elemento	O(1)
iterador_bi_anterior()	Retroceder y obtener elemento	O(1)
iterador_bi_tiene_siguiente()	Verificar elementos siguientes	O(1)
iterador_bi_tiene_anterior()	Verificar elementos anteriores	O(1)
iterador_bi_elemento_actual()	Obtener elemento actual	O(1)
iterador_bi_insertar_despues()	Insertar después del actual	O(1)
iterador_bi_insertar_antes()	Insertar antes del actual	O(1)
iterador_bi_eliminar_actual()	Eliminar elemento actual	O(1)
iterador_bi_reiniciar()	Reiniciar al inicio	O(1)
iterador_bi_ir_final()	Ir al final de la lista	O(1)
iterador_bi_obtener_posicion()	Obtener posición actual	O(1)
iterador_bi_ir_a_posicion()	Ir a posición específica	O(n/2)
iterador_bi_mapear()	Transformar elementos	O(n)
iterador_bi_filtrar()	Filtrar elementos	O(n)
iterador_bi_reducir()	Reducir a un valor	O(n)

Códigos de Resultado (resultado_t)
Código	Descripcion
EXITO	Operación exitosa
ERROR_PARAMETRO_NULO	Parámetro nulo no permitido
ERROR_MEMORIA_INSUFICIENTE	Falta de memoria
ERROR_ITERADOR_INVALIDO	Iterador en estado inválido
ERROR_LISTA_VACIA	Operación en lista vacía
ERROR_ELEMENTO_NO_ENCONTRADO	Elemento no existe
ERROR_OPERACION_INVALIDA	Operación no válida
ERROR_ITERADOR_FINALIZADO	Iterador sin más elementos
Sistema de Logging
c

// Niveles de logging disponibles
LOG_DEBUG("Mensaje de depuracion: %d", variable);
LOG_INFO("Información general");
LOG_WARNING("Advertencia");
LOG_ERROR("Error crítico");

// En modo DEBUG se muestran todos los niveles
// En modo producción solo WARNING y ERROR

Compilación y Uso
Compilación con debug
bash

gcc -DDEBUG -I./include src/*.c src/lista/*.c src/lista_doble/*.c src/iterador/*.c src/iterador_bi/*.c -o programa

Compilación para producción
bash

gcc -I./include src/*.c src/lista/*.c src/lista_doble/*.c src/iterador/*.c src/iterador_bi/*.c -o programa

Copilacion con Makefile incluido
bash

make
all        - Compila la librería y las pruebas (por defecto)"
lib        - Compila solo la librería estática"
test       - Compila y ejecuta las pruebas"
examples   - Compila los ejemplos"
install    - Instala la librería en el sistema"     ///puede requerir root (sudo)
uninstall  - Desinstala la librería del sistema"    ///puede requerir root (sudo)
clean      - Limpia los archivos compilados"
distclean  - Limpieza profunda"
info       - Muestra información del proyecto"
help       - Muestra esta ayuda"



Características Avanzadas
    Seguridad y Robustez

    Verificacion exhaustiva de parametros

    Proteccion contra operaciones invalidas

    Manejo seguro de memoria

    Deteccion de corrupcion de datos

    Optimizacion

    Operaciones O(1) para inserciones/eliminaciones en extremos

    Búsqueda optimizada en listas dobles (desde inicio o fin)

    Iteradores de alto rendimiento

    Gestión eficiente de memoria

    Flexibilidad

    Soporte para tipos de datos personalizados

    Funciones de callback configurables

    Múltiples estrategias de iteracion

    API consistente y predecible

Ejemplos Adicionales

Consulte la carpeta examples/ para ejemplos más detallados incluyendo:

    Uso avanzado con estructuras complejas

    Operaciones funcionales anidadas

    Manejo de errores comprehensivo

    Patrones de uso recomendados
