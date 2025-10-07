#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 100
#define MAX_TITULO 50
#define MAX_AUTOR 30

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int anio;
    int cantidad;
} Libro;

Libro inventario[MAX_LIBROS];
int indice_libro = 0;

// Función para agregar un libro al inventario
void agregar_libro() {
    if (indice_libro < MAX_LIBROS) {
        printf("Ingrese el título del libro: ");
        fgets(inventario[indice_libro].titulo, MAX_TITULO, stdin);
        inventario[indice_libro].titulo[strcspn(inventario[indice_libro].titulo, "\n")] = 0;

        printf("Ingrese el autor del libro: ");
        fgets(inventario[indice_libro].autor, MAX_AUTOR, stdin);
        inventario[indice_libro].autor[strcspn(inventario[indice_libro].autor, "\n")] = 0;

        printf("Ingrese el año del libro: ");
        scanf("%d", &inventario[indice_libro].anio);
        getchar(); // Consumir el newline

        printf("Ingrese la cantidad del libro: ");
        scanf("%d", &inventario[indice_libro].cantidad);
        getchar(); // Consumir el newline

        indice_libro++;
        printf("Libro agregado con éxito.\n");
    } else {
        printf("Inventario lleno. No se pueden agregar más libros.\n");
    }
}

// Función para eliminar un libro del inventario
void eliminar_libro() {
    char titulo[MAX_TITULO];
    printf("Ingrese el título del libro a eliminar: ");
    fgets(titulo, MAX_TITULO, stdin);
    titulo[strcspn(titulo, "\n")] = 0;

    for (int i = 0; i < indice_libro; i++) {
        if (strcmp(inventario[i].titulo, titulo) == 0) {
            // Mover el último libro al lugar del libro eliminado
            if (i < indice_libro - 1) {
                inventario[i] = inventario[indice_libro - 1];
            }
            indice_libro--;
            printf("Libro eliminado con éxito.\n");
            return;
        }
    }
    printf("Libro no encontrado en el inventario.\n");
}

// Función para listar todos los libros en el inventario
void listar_libros() {
    if (indice_libro == 0) {
        printf("No hay libros en el inventario.\n");
    } else {
        printf("\n=== LISTA DE LIBROS ===\n");
        for (int i = 0; i < indice_libro; i++) {
            printf("Libro #%d:\n", i + 1);
            printf("  Título: %s\n", inventario[i].titulo);
            printf("  Autor: %s\n", inventario[i].autor);
            printf("  Año: %d\n", inventario[i].anio);
            printf("  Cantidad: %d\n\n", inventario[i].cantidad);
        }
    }
}

// Función para buscar un libro por título
void buscar_libro() {
    char titulo[MAX_TITULO];
    printf("Ingrese el título del libro a buscar: ");
    fgets(titulo, MAX_TITULO, stdin);
    titulo[strcspn(titulo, "\n")] = 0;

    for (int i = 0; i < indice_libro; i++) {
        if (strcmp(inventario[i].titulo, titulo) == 0) {
            printf("\n=== LIBRO ENCONTRADO ===\n");
            printf("Título: %s\n", inventario[i].titulo);
            printf("Autor: %s\n", inventario[i].autor);
            printf("Año: %d\n", inventario[i].anio);
            printf("Cantidad: %d\n", inventario[i].cantidad);
            return;
        }
    }
    printf("Libro no encontrado en el inventario.\n");
}

int main() {
    int opcion;
    
    printf("Sistema de Gestión de Biblioteca\n");
    
    do {
        printf("\n=== MENÚ PRINCIPAL ===\n");
        printf("1. Agregar libro\n");
        printf("2. Eliminar libro\n");
        printf("3. Listar libros\n");
        printf("4. Buscar libro\n");
        printf("5. Salir\n");
        printf("Ingrese una opción: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Error: Por favor ingrese un número válido.\n");
            while (getchar() != '\n'); // Limpiar buffer de entrada
            continue;
        }
        getchar(); // Consumir el newline

        switch (opcion) {
            case 1:
                agregar_libro();
                break;
            case 2:
                eliminar_libro();
                break;
            case 3:
                listar_libros();
                break;
            case 4:
                buscar_libro();
                break;
            case 5:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Por favor ingrese un número del 1 al 5.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}

