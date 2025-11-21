# Makefile para Sistema de Alimentación de Gallinas
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = sistema_gallinas
SOURCE = sistema_gallinas.c

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
