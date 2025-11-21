# Sistema de Inventario de Productos

Sistema completo de gestión de inventario desarrollado en C, con almacenamiento persistente en archivos de texto.

## 📋 Características

- ✅ Agregar nuevos productos
- ✅ Listar todos los productos
- ✅ Buscar productos por nombre
- ✅ Modificar información de productos
- ✅ Eliminar productos
- ✅ Almacenamiento persistente en archivo .txt
- ✅ Interfaz de menú interactiva
- ✅ Compatible con Linux (Manjaro, Ubuntu, Debian, Arch, etc.)

## 🔧 Requisitos

- GCC (GNU Compiler Collection)
- Sistema operativo Linux
- Biblioteca estándar de C

## 📦 Instalación

### En Manjaro Linux

```bash
# Instalar GCC si no lo tienes
sudo pacman -S gcc

# Clonar o descargar los archivos del proyecto
# Navegar al directorio del proyecto
cd /ruta/al/proyecto
```

### En Ubuntu/Debian

```bash
sudo apt update
sudo apt install build-essential
```

### En Arch Linux

```bash
sudo pacman -S base-devel
```

## 🚀 Compilación

Para compilar el programa, ejecuta:

```bash
gcc main.c -o inventario
```

O si prefieres usar el Makefile incluido:

```bash
make
```

## ▶️ Ejecución

Una vez compilado, ejecuta el programa:

```bash
./inventario
```

## 📖 Uso del Sistema

### Menú Principal

Al iniciar el programa, verás un menú con las siguientes opciones:

1. **Agregar producto**: Registra un nuevo producto con nombre, categoría, precio y cantidad
2. **Listar productos**: Muestra todos los productos en una tabla ordenada
3. **Buscar producto**: Encuentra productos por nombre (búsqueda parcial)
4. **Modificar producto**: Actualiza la información de un producto existente
5. **Eliminar producto**: Elimina un producto del inventario (con confirmación)
6. **Salir**: Guarda los cambios y cierra el programa

### Ejemplo de Uso

#### Agregar un Producto

```
Nombre del producto: Laptop HP
Categoría: Electrónica
Precio: $850.00
Cantidad en stock: 15
```

#### Buscar Producto

```
Ingrese el nombre del producto: Laptop
```

Mostrará todos los productos que contengan "Laptop" en su nombre.

## 📁 Estructura de Archivos

```
proyecto/
│
├── main.c              # Código fuente principal
├── README.md           # Este archivo
├── Makefile            # Script de compilación (opcional)
└── inventario.txt      # Archivo de datos (se crea automáticamente)
```

## 💾 Formato del Archivo de Datos

El archivo `inventario.txt` almacena los datos en formato de texto plano con el siguiente formato:

```
ID|Nombre|Categoría|Precio|Cantidad
```

Ejemplo:
```
1|Laptop HP|Electrónica|850.00|15
2|Mouse Logitech|Accesorios|25.50|50
```

## 🛠️ Makefile (Opcional)

Crea un archivo llamado `Makefile` con el siguiente contenido:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = inventario
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) inventario.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```

Luego puedes usar:
- `make` - Compilar
- `make run` - Compilar y ejecutar
- `make clean` - Limpiar archivos generados

## 🐛 Solución de Problemas

### Error: "Permission denied"

```bash
chmod +x inventario
```

### Error: "No such file or directory" al compilar

Asegúrate de estar en el directorio correcto:
```bash
ls -la
```

Deberías ver el archivo `main.c`

### El programa no guarda los datos

Verifica los permisos del directorio:
```bash
ls -la
```

Si es necesario, cambia los permisos:
```bash
chmod 755 .
```

## 📝 Notas Importantes

- Los datos se guardan automáticamente después de cada operación de agregar, modificar o eliminar
- El sistema soporta hasta 100 productos (configurable en `MAX_PRODUCTOS`)
- Los IDs se reorganizan automáticamente al eliminar productos
- El archivo `inventario.txt` se crea automáticamente si no existe

## 🔒 Características de Seguridad

- Validación de entrada de datos
- Confirmación antes de eliminar productos
- Manejo de errores en operaciones de archivo
- Límite de caracteres en campos de texto para prevenir desbordamiento

## 🚧 Futuras Mejoras

- Exportación a CSV
- Reportes de bajo stock
- Historial de cambios
- Búsqueda por categoría
- Ordenamiento personalizado
- Estadísticas de inventario

## 👨‍💻 Autor

Sistema desarrollado con fines educativos y prácticos.

## 📄 Licencia

Este proyecto es de código abierto y está disponible bajo la licencia MIT.

---

**¡Gracias por usar el Sistema de Inventario de Productos!**

Para reportar problemas o sugerencias, por favor documenta el error y el contexto en que ocurrió.
