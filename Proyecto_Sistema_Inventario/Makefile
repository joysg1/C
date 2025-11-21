# Makefile para Sistema de Inventario de Productos
# Compatible con Linux (Manjaro, Ubuntu, Arch, Debian, etc.)

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c11 -O2

# Flags de depuración (opcional)
DEBUGFLAGS = -g -DDEBUG

# Nombre del ejecutable
TARGET = inventario

# Archivos fuente
SRC = main.c

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Archivo de datos
DATAFILE = inventario.txt

# Colores para output (opcional)
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Regla por defecto
all: $(TARGET)
	@echo "$(GREEN)✓ Compilación exitosa!$(NC)"
	@echo "$(YELLOW)Ejecuta './$(TARGET)' para iniciar el programa$(NC)"

# Compilar el programa
$(TARGET): $(SRC)
	@echo "$(YELLOW)Compilando $(TARGET)...$(NC)"
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Compilar con símbolos de depuración
debug: $(SRC)
	@echo "$(YELLOW)Compilando en modo debug...$(NC)"
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(SRC) -o $(TARGET)
	@echo "$(GREEN)✓ Compilación debug exitosa!$(NC)"

# Compilar y ejecutar
run: $(TARGET)
	@echo "$(GREEN)Ejecutando $(TARGET)...$(NC)"
	@./$(TARGET)

# Limpiar archivos generados
clean:
	@echo "$(RED)Limpiando archivos generados...$(NC)"
	rm -f $(TARGET) $(OBJ) *~
	@echo "$(GREEN)✓ Limpieza completada$(NC)"

# Limpiar todo incluyendo datos
cleanall: clean
	@echo "$(RED)Eliminando archivo de datos...$(NC)"
	rm -f $(DATAFILE)
	@echo "$(GREEN)✓ Limpieza completa$(NC)"

# Instalar (copiar a /usr/local/bin)
install: $(TARGET)
	@echo "$(YELLOW)Instalando $(TARGET) en /usr/local/bin...$(NC)"
	@sudo cp $(TARGET) /usr/local/bin/
	@sudo chmod 755 /usr/local/bin/$(TARGET)
	@echo "$(GREEN)✓ Instalación exitosa!$(NC)"
	@echo "$(YELLOW)Ahora puedes ejecutar '$(TARGET)' desde cualquier lugar$(NC)"

# Desinstalar
uninstall:
	@echo "$(RED)Desinstalando $(TARGET)...$(NC)"
	@sudo rm -f /usr/local/bin/$(TARGET)
	@echo "$(GREEN)✓ Desinstalación completada$(NC)"

# Verificar sintaxis sin compilar
check:
	@echo "$(YELLOW)Verificando sintaxis...$(NC)"
	$(CC) $(CFLAGS) -fsyntax-only $(SRC)
	@echo "$(GREEN)✓ Sin errores de sintaxis$(NC)"

# Crear backup del código y datos
backup:
	@echo "$(YELLOW)Creando backup...$(NC)"
	@mkdir -p backups
	@tar -czf backups/inventario_backup_$$(date +%Y%m%d_%H%M%S).tar.gz $(SRC) Makefile README.md $(DATAFILE) 2>/dev/null || true
	@echo "$(GREEN)✓ Backup creado en carpeta backups/$(NC)"

# Información del sistema
info:
	@echo "$(YELLOW)=== Información del Sistema ===$(NC)"
	@echo "Compilador: $(CC)"
	@echo "Versión: $$($(CC) --version | head -n1)"
	@echo "Flags: $(CFLAGS)"
	@echo "Target: $(TARGET)"
	@echo "Fuente: $(SRC)"
	@echo "Sistema: $$(uname -s)"
	@echo "Arquitectura: $$(uname -m)"

# Ayuda
help:
	@echo "$(GREEN)=== Sistema de Inventario - Makefile ===$(NC)"
	@echo ""
	@echo "$(YELLOW)Comandos disponibles:$(NC)"
	@echo "  make              - Compila el programa"
	@echo "  make run          - Compila y ejecuta el programa"
	@echo "  make debug        - Compila con símbolos de depuración"
	@echo "  make clean        - Elimina archivos compilados"
	@echo "  make cleanall     - Elimina todo (incluyendo datos)"
	@echo "  make install      - Instala en /usr/local/bin (requiere sudo)"
	@echo "  make uninstall    - Desinstala del sistema"
	@echo "  make check        - Verifica sintaxis sin compilar"
	@echo "  make backup       - Crea backup del proyecto"
	@echo "  make info         - Muestra información del sistema"
	@echo "  make help         - Muestra esta ayuda"
	@echo ""
	@echo "$(YELLOW)Ejemplos:$(NC)"
	@echo "  make && ./inventario    # Compilar y ejecutar manualmente"
	@echo "  make run                # Compilar y ejecutar automáticamente"
	@echo "  make clean && make      # Limpiar y recompilar"

# Declarar targets que no son archivos
.PHONY: all debug run clean cleanall install uninstall check backup info help
