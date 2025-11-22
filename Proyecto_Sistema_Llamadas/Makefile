# Makefile para Sistema de Registro de Llamadas
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = sistema_llamadas
SOURCE = sistema_llamadas.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET) llamadas.txt

install: $(TARGET)
	@echo "El sistema ha sido compilado exitosamente"
	@echo "Ejecute: ./$(TARGET)"

.PHONY: clean install
