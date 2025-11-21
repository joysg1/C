# Makefile para Sistema de Riego de Plantas
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = sistema_riego
SOURCE = sistema_riego.c

# Compilación por defecto
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) temp.txt

# Instalar en sistema (opcional)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Desinstalar
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean install uninstall
