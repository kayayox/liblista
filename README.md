# Librería de Lista Enlazada en C

Una implementación profesional de lista enlazada simple en C con iteradores y operaciones funcionales.

## Características

- **Lista enlazada simple** con almacenamiento genérico de datos
- **Iterador seguro simple** con recorrido simple
- **Lista enlazada doble** con almacenamiento genérico de datos
- **Iterador seguro** con recorrido bidireccional
- **Operaciones funcionales**: map, filter, reduce
- **Manejo robusto de errores** con códigos de retorno
- **Sistema de logging** configurable
- **Verificaciones de seguridad** en tiempo de ejecución
- **Documentación completa** en formato Doxygen

## Estructura del proyecto
txt.
liblista/
├── include/                 # Headers públicos
│   ├── lista.h             # Lista simple
│   ├── lista_doble.h       # Lista doblemente enlazada
│   ├── iterador.h          # Iterador simple
│   ├── iterador_bi.h       # Iterador bidireccional
│   ├── resultados.h        # Códigos de error y logging
│   └── verificaciones.h    # Verificaciones de seguridad
├── src/                    # Implementación
│   ├── lista/              # Implementación lista simple
│   │   ├── lista.c
│   │   └── lista_privada.h
│   ├── lista_doble/        # Implementación lista doble
│   │   ├── lista_doble.c
│   │   └── lista_doble_privada.h
│   ├── iterador/           # Iterador simple
│   │   ├── iterador.c
│   │   └── iterador_privada.h
│   ├── iterador_bi/        # Iterador bidireccional
│   │   ├── iterador_bi.c
│   │   └── iterador_bi_privada.h
│   ├── errores.c           # Manejo de errores
│   ├── logging.c           # Sistema de logging
│   └── verificaciones.c    # Verificaciones
├── test/                   # Pruebas unitarias
│   ├── test_lista_simple.c
│   ├── test_lista_doble.c
│   └── test_iteradores.c
├── examples/               # Ejemplos de uso
│   ├── ejemplo_simple.c
│   ├── ejemplo_complejo.c
│   └── ejemplo_persona.c
└── README.md
txt.
## Uso básico

### Creación de lista

```c
#include "include/lista.h"
#include "include/iterador.h"

lista_t* lista;
resultado_t res = lista_crear(&lista, sizeof(int));API Principal

Lista

    lista_crear() - Crear nueva lista

    lista_liberar() - Liberar recursos

    lista_insertar_final() - Insertar al final

    lista_insertar_inicio() - Insertar al inicio

    lista_eliminar_valor() - Eliminar por valor

    lista_obtener_tamanio() - Obtener tamaño

    lista_obtener_cabeza() - Obtener elemento cabeza

Iterador

    iterador_crear() - Crear iterador

    iterador_liberar() - Liberar iterador

    iterador_siguiente() - Avanzar y obtener elemento

    iterador_tiene_siguiente() - Verificar si hay más elementos

    iterador_elemento_actual() - Obtener elemento actual

    iterador_reiniciar() - Reiniciar iterador

    iterador_mapear() - Transformar elementos

    iterador_filtrar() - Filtrar elementos

    iterador_reducir() - Reducir a un valor


    Todas las funciones retornan resultado_t con los siguientes códigos:

    EXITO: Operación exitosa

    ERROR_PARAMETRO_NULO: Parámetro nulo no permitido

    ERROR_MEMORIA_INSUFICIENTE: Falta de memoria

    ERROR_LISTA_VACIA: Operación en lista vacía

    ERROR_ELEMENTO_NO_ENCONTRADO: Elemento no existe

    ERROR_ITERADOR_FINALIZADO: Iterador sin más elementos
