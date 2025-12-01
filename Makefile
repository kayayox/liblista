# Makefile para librería estática liblista
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude
AR = ar
ARFLAGS = rcs

# Directorios
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib
INCLUDE_DIR = include
INSTALL_PREFIX ?= /usr/local

# Archivos fuente
LISTA_SRC = lista/lista.c
LISTA_DOBLE_SRC = lista_doble/lista_doble.c
ITERADOR_SRC = iterador/iterador.c
ITERADOR_BI_SRC = iterador_bi/iterador_bi.c
AUX_SRC = auxiliares/errores.c auxiliares/loggin.c auxiliares/verificaciones.c

# Objetos
LISTA_OBJ = $(OBJ_DIR)/lista.o
LISTA_DOBLE_OBJ = $(OBJ_DIR)/lista_doble.o
ITERADOR_OBJ = $(OBJ_DIR)/iterador.o
ITERADOR_BI_OBJ = $(OBJ_DIR)/iterador_bi.o
AUX_OBJ = $(OBJ_DIR)/errores.o $(OBJ_DIR)/loggin.o $(OBJ_DIR)/verificaciones.o
TEST_OBJ = $(OBJ_DIR)/test_liblista.o

# Librería estática
LIBRARY = $(LIB_DIR)/liblista.a

# Ejecutables
TARGET = $(BIN_DIR)/test_liblista
EXAMPLE = $(BIN_DIR)/example
EXAMPLE1 = $(BIN_DIR)/example1

.PHONY: all clean test install uninstall examples

all: $(LIBRARY) $(TARGET)

# Regla para la librería estática
$(LIBRARY): $(LISTA_OBJ) $(LISTA_DOBLE_OBJ) $(ITERADOR_OBJ) $(ITERADOR_BI_OBJ) $(AUX_OBJ) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Librería estática creada: $(LIBRARY)"

# Regla para el ejecutable de pruebas
$(TARGET): $(TEST_OBJ) $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ) -L$(LIB_DIR) -llista
	@echo "Ejecutable de pruebas creado: $(TARGET)"

# Regla para el ejemplo
$(EXAMPLE): examples/example.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ examples/example.c -L$(LIB_DIR) -llista
	@echo "Ejemplo creado: $(EXAMPLE)"

$(EXAMPLE1): examples/example1.c $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ examples/example.c -L$(LIB_DIR) -llista
	@echo "Ejemplo de persona creado: $(EXAMPLE1)"

# Reglas para compilar los archivos de la librería
$(OBJ_DIR)/lista.o: $(LISTA_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/lista_doble.o: $(LISTA_DOBLE_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/iterador.o: $(ITERADOR_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/iterador_bi.o: $(ITERADOR_BI_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/errores.o: auxiliares/errores.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/loggin.o: auxiliares/loggin.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/verificaciones.o: auxiliares/verificaciones.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/test_liblista.o: test/test_liblista.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Creación de directorios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Pruebas
test: $(TARGET)
	@echo "Ejecutando pruebas..."
	./$(TARGET)

# Ejemplos
examples: $(EXAMPLE) $(EXAMPLE1)
	@echo "Compilando ejemplos..."
	@echo "Ejemplo disponible en: $(EXAMPLE) $(EXAMPLE1)"

# Instalación en el sistema
install: $(LIBRARY)
	@echo "Instalando librería en $(INSTALL_PREFIX)..."

	# Instalar headers
	mkdir -p $(INSTALL_PREFIX)/include/liblista
	cp $(INCLUDE_DIR)/*.h $(INSTALL_PREFIX)/include/liblista/
	cp lista_doble/*.h $(INSTALL_PREFIX)/include/liblista/ 2>/dev/null || true
	cp lista/*.h $(INSTALL_PREFIX)/include/liblista/ 2>/dev/null || true
	cp iterador/*.h $(INSTALL_PREFIX)/include/liblista/ 2>/dev/null || true
	cp iterador_bi/*.h $(INSTALL_PREFIX)/include/liblista/ 2>/dev/null || true

	# Instalar librería estática
	mkdir -p $(INSTALL_PREFIX)/lib
	cp $(LIBRARY) $(INSTALL_PREFIX)/lib/

	# Crear archivo pkg-config
	mkdir -p $(INSTALL_PREFIX)/lib/pkgconfig
	@echo "prefix=$(INSTALL_PREFIX)" > $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "exec_prefix=\$${prefix}" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "libdir=\$${exec_prefix}/lib" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "includedir=\$${prefix}/include/liblista" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "Name: liblista" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "Description: Librería de lista enlazada en C" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "Version: 1.0.0" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "Libs: -L\$${libdir} -llista" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "Cflags: -I\$${includedir}" >> $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc

	@echo "Instalación completada."
	@echo "Incluye en tu código: #include <liblista/lista.h>"
	@echo "Incluye en tu código: #include <liblista/lista_doble.h>"
	@echo "Incluye en tu código: #include <liblista/iterador.h>"
	@echo "Incluye en tu código: #include <liblista/iterador_bi.h>"
	@echo "Incluye en tu código: #include <liblista/resultados.h>"
	@echo "#include <liblista/lista.h> y #include <liblista/iterador.h> listas simples"
	@echo "#include <liblista/lista_doble.h> y #include <liblista/iterador_bi.h> listas dobles"
	@echo "#include <liblista/resultados.h> si vas a incluir retornos de funciones"
	@echo "Compila con: gcc -llista tu_programa.c"

# Desinstalar
uninstall:
	@echo "Desinstalando librería..."
	rm -rf $(INSTALL_PREFIX)/include/liblista
	rm -f $(INSTALL_PREFIX)/lib/liblista.a
	rm -f $(INSTALL_PREFIX)/lib/pkgconfig/liblista.pc
	@echo "Desinstalación completada."

# Limpieza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)
	@echo "Limpieza completada."

# Limpieza profunda (incluye archivos de backup)
distclean: clean
	find . -name "*~" -o -name "*.bak" -o -name "*.swp" -delete
	@echo "Limpieza profunda completada."

# Información del proyecto
info:
	@echo "=== Información de liblista ==="
	@echo "Librería: $(LIBRARY)"
	@echo "Pruebas: $(TARGET)"
	@echo "Headers: $(wildcard $(INCLUDE_DIR)/*.h)"
	@echo "Fuentes: $(LISTA_SRC) $(ITERADOR_SRC) $(LISTA_DOBLE_SRC) $(ITERADOR_BI_SRC) $(AUX_SRC)"
	@echo "==============================="

# Ayuda
help:
	@echo "Objetivos disponibles:"
	@echo "  all        - Compila la librería y las pruebas (por defecto)"
	@echo "  lib        - Compila solo la librería estática"
	@echo "  test       - Compila y ejecuta las pruebas"
	@echo "  examples   - Compila los ejemplos"
	@echo "  install    - Instala la librería en el sistema"
	@echo "  uninstall  - Desinstala la librería del sistema"
	@echo "  clean      - Limpia los archivos compilados"
	@echo "  distclean  - Limpieza profunda"
	@echo "  info       - Muestra información del proyecto"
	@echo "  help       - Muestra esta ayuda"

# Alias
lib: $(LIBRARY)
