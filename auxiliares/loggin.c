/**
 * @file logging.c
 * @brief Implementación del sistema de logging para la librería
 */

#include "resultados.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

void log_mensaje(nivel_log_t nivel,const char* archivo,int linea,const char* formato,...){
    const char* nivel_str="";
    const char* color="";
    switch(nivel){
        case LOG_DEBUG:
            nivel_str="DEBUG";
            color="\033[36m"; // Cyan
            break;
        case LOG_INFO:
            nivel_str="INFO";
            color="\033[32m"; // Verde
            break;
        case LOG_WARNING:
            nivel_str="WARNING";
            color="\033[33m"; // Amarillo
            break;
        case LOG_ERROR:
            nivel_str="ERROR";
            color="\033[31m"; // Rojo
            break;
    }
    time_t ahora=time(NULL);
    struct tm* tiempo_local=localtime(&ahora);
    char timestamp[20];
    strftime(timestamp,sizeof(timestamp),"%Y-%m-%d %H:%M:%S",tiempo_local);
    // Formatear el mensaje
    char mensaje_formateado[512];
    va_list args;
    va_start(args,formato);
    vsnprintf(mensaje_formateado,sizeof(mensaje_formateado),formato, args);
    va_end(args);

    #ifdef DEBUG
    fprintf(stderr,"%s[%s %s] %s:%d: %s\033[0m\n",
            color,timestamp,nivel_str,archivo,linea, mensaje_formateado);
    #else
    if(nivel>=LOG_WARNING){
        fprintf(stderr,"[%s %s] %s\n",timestamp,nivel_str,mensaje_formateado);
    }
    #endif
}
