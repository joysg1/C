#include <stdio.h>
#include <string.h>

#define MAX_ESTUDIANTES 50

// Definición de la estructura Estudiante
struct Estudiante {
    int id;
    char nombre[50];
    int edad;
    float promedio;
};

// Variables globales
struct Estudiante estudiantes[MAX_ESTUDIANTES];
int totalEstudiantes = 0;

// Función para mostrar el menú
void mostrarMenu() {
    printf("\n======== MENÚ DE ESTUDIANTES ========\n");
    printf("1. Agregar estudiante\n");
    printf("2. Mostrar todos los estudiantes\n");
    printf("3. Modificar promedio de un estudiante\n");
    printf("4. Salir\n");
    printf("Seleccione una opción: ");
}

// Función para agregar un estudiante
void agregarEstudiante() {
    if (totalEstudiantes >= MAX_ESTUDIANTES) {
        printf("\nNo se pueden agregar más estudiantes. Límite alcanzado.\n");
        return;
    }
    
    struct Estudiante nuevo;
    
    printf("\n--- Agregar Nuevo Estudiante ---\n");
    printf("ID: ");
    scanf("%d", &nuevo.id);
    getchar(); // Limpiar el buffer
    
    printf("Nombre: ");
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0; // Eliminar el salto de línea
    
    printf("Edad: ");
    scanf("%d", &nuevo.edad);
    
    printf("Promedio: ");
    scanf("%f", &nuevo.promedio);
    
    estudiantes[totalEstudiantes] = nuevo;
    totalEstudiantes++;
    
    printf("\n¡Estudiante agregado exitosamente!\n");
}

// Función para mostrar todos los estudiantes
void mostrarTodos() {
    if (totalEstudiantes == 0) {
        printf("\nNo hay estudiantes registrados.\n");
        return;
    }
    
    printf("\n======== LISTA DE ESTUDIANTES ========\n");
    for (int i = 0; i < totalEstudiantes; i++) {
        printf("\nEstudiante %d:\n", i + 1);
        printf("  ID: %d\n", estudiantes[i].id);
        printf("  Nombre: %s\n", estudiantes[i].nombre);
        printf("  Edad: %d\n", estudiantes[i].edad);
        printf("  Promedio: %.2f\n", estudiantes[i].promedio);
    }
}

// Función para modificar el promedio de un estudiante
void modificarPromedio() {
    if (totalEstudiantes == 0) {
        printf("\nNo hay estudiantes registrados.\n");
        return;
    }
    
    int id;
    float nuevoPromedio;
    int encontrado = 0;
    
    printf("\n--- Modificar Promedio ---\n");
    printf("Ingrese el ID del estudiante: ");
    scanf("%d", &id);
    
    for (int i = 0; i < totalEstudiantes; i++) {
        if (estudiantes[i].id == id) {
            printf("Estudiante encontrado: %s\n", estudiantes[i].nombre);
            printf("Promedio actual: %.2f\n", estudiantes[i].promedio);
            printf("Nuevo promedio: ");
            scanf("%f", &nuevoPromedio);
            
            estudiantes[i].promedio = nuevoPromedio;
            printf("\n¡Promedio actualizado exitosamente!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nNo se encontró un estudiante con ID %d\n", id);
    }
}

int main() {
    int opcion;
    
    // Agregar algunos estudiantes de ejemplo
    estudiantes[0] = (struct Estudiante){101, "Juan Pérez", 20, 8.5};
    estudiantes[1] = (struct Estudiante){102, "María García", 21, 9.2};
    estudiantes[2] = (struct Estudiante){103, "Carlos López", 22, 7.8};
    totalEstudiantes = 3;
    
    printf("Bienvenido al Sistema de Gestión de Estudiantes\n");
    
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                agregarEstudiante();
                break;
            case 2:
                mostrarTodos();
                break;
            case 3:
                modificarPromedio();
                break;
            case 4:
                printf("\n¡Hasta luego!\n");
                break;
            default:
                printf("\nOpción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 4);
    
    return 0;
}