# Makefile para Sistema de Nomina
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = sistema_nomina
SOURCE = sistema_nomina.c

# Compilacion por defecto
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Compilacion para debug
debug: CFLAGS += -g
debug: $(TARGET)

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) *.o

# Instalar (copiar a /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Desinstalar
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean install uninstall debug
