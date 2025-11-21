# Sistema de Registro de Matrícula de Estudiantes

## Descripción
Sistema desarrollado en C para el registro y gestión de matrículas de estudiantes organizados por salón. Permite agregar, editar, eliminar y buscar estudiantes, así como listarlos por salón específico.

## Características
- ✅ Gestión completa de estudiantes (CRUD)
- ✅ Organización por salón
- ✅ Persistencia de datos en archivo de texto
- ✅ Búsqueda por ID, nombre o salón
- ✅ Interfaz de menú intuitiva
- ✅ Compatible con Linux (Manjaro, Ubuntu, etc.)

## Estructura del Proyecto
/
├── sistema_matricula.c # Código fuente principal
├── Makefile # Script de compilación
├── README.md # Este archivo
└── estudiantes.txt # Base de datos (se crea automáticamente)

## Requisitos
- Compilador GCC
- Sistema Linux (probado en Manjaro, Ubuntu, Debian)

## Compilación y Ejecución

## Compilación:
```bash
make

## Compilación con opciones de debug:
make debug

## Ejecución:
./sistema_matricula

## Limpiar archivos compilados:
make clean

## Autor

Sistema desarrollado como ejemplo educativo de programación en C.

## Licencia

Uso educativo libre.
