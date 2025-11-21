# Makefile para Sistema de Matricula
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = sistema_matricula
SOURCE = sistema_matricula.c

# Compilacion por defecto
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Compilacion para debug
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) *.o

# Instalar en sistema (opcional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Desinstalar
uninstall:
	rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean install uninstall debug
