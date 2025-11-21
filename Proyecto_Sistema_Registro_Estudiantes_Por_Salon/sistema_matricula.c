#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ESTUDIANTES 100
#define MAX_NOMBRE 50
#define MAX_SALON 20
#define ARCHIVO_DATOS "estudiantes.txt"

// Estructura para representar un estudiante
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_NOMBRE];
    int edad;
    char salon[MAX_SALON];
    char carrera[MAX_NOMBRE];
} Estudiante;

// Prototipos de funciones
void mostrarMenu();
void agregarEstudiante();
void listarEstudiantes();
void buscarEstudiante();
void editarEstudiante();
void eliminarEstudiante();
void listarPorSalon();
void listarPorSalonEspecifico(char salon[]);
void guardarEnArchivo(Estudiante estudiantes[], int contador);
int cargarDesdeArchivo(Estudiante estudiantes[]);
int generarId();
void limpiarBuffer();

// Variables globales
Estudiante estudiantes[MAX_ESTUDIANTES];
int contadorEstudiantes = 0;

int main() {
    printf("=== SISTEMA DE REGISTRO DE MATRICULA ===\n");
    printf("Cargando datos desde el archivo...\n");
    
    // Cargar datos existentes
    contadorEstudiantes = cargarDesdeArchivo(estudiantes);
    printf("Datos cargados: %d estudiantes registrados\n\n", contadorEstudiantes);
    
    int opcion;
    
    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        
        switch(opcion) {
            case 1:
                agregarEstudiante();
                break;
            case 2:
                listarEstudiantes();
                break;
            case 3:
                buscarEstudiante();
                break;
            case 4:
                editarEstudiante();
                break;
            case 5:
                eliminarEstudiante();
                break;
            case 6:
                listarPorSalon();
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                printf("Guardando datos...\n");
                guardarEnArchivo(estudiantes, contadorEstudiantes);
                printf("¡Hasta luego!\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
        
        printf("\nPresione Enter para continuar...");
        getchar();
        
    } while(opcion != 0);
    
    return 0;
}

void mostrarMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Agregar estudiante\n");
    printf("2. Listar todos los estudiantes\n");
    printf("3. Buscar estudiante\n");
    printf("4. Editar estudiante\n");
    printf("5. Eliminar estudiante\n");
    printf("6. Listar estudiantes por salon\n");
    printf("0. Salir\n");
    printf("======================\n");
}

void agregarEstudiante() {
    if(contadorEstudiantes >= MAX_ESTUDIANTES) {
        printf("Error: No se pueden agregar mas estudiantes. Capacidad maxima alcanzada.\n");
        return;
    }
    
    Estudiante nuevo;
    
    printf("\n=== AGREGAR NUEVO ESTUDIANTE ===\n");
    
    nuevo.id = generarId();
    
    printf("Nombre: ");
    fgets(nuevo.nombre, MAX_NOMBRE, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;
    
    printf("Apellido: ");
    fgets(nuevo.apellido, MAX_NOMBRE, stdin);
    nuevo.apellido[strcspn(nuevo.apellido, "\n")] = 0;
    
    printf("Edad: ");
    scanf("%d", &nuevo.edad);
    limpiarBuffer();
    
    printf("Salon: ");
    fgets(nuevo.salon, MAX_SALON, stdin);
    nuevo.salon[strcspn(nuevo.salon, "\n")] = 0;
    
    printf("Carrera: ");
    fgets(nuevo.carrera, MAX_NOMBRE, stdin);
    nuevo.carrera[strcspn(nuevo.carrera, "\n")] = 0;
    
    estudiantes[contadorEstudiantes] = nuevo;
    contadorEstudiantes++;
    
    // Guardar inmediatamente en el archivo
    guardarEnArchivo(estudiantes, contadorEstudiantes);
    
    printf("\n¡Estudiante agregado exitosamente!\n");
    printf("ID asignado: %d\n", nuevo.id);
}

void listarEstudiantes() {
    printf("\n=== LISTA DE ESTUDIANTES ===\n");
    
    if(contadorEstudiantes == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    printf("%-5s %-20s %-20s %-5s %-15s %-20s\n", 
           "ID", "Nombre", "Apellido", "Edad", "Salon", "Carrera");
    printf("--------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < contadorEstudiantes; i++) {
        printf("%-5d %-20s %-20s %-5d %-15s %-20s\n",
               estudiantes[i].id,
               estudiantes[i].nombre,
               estudiantes[i].apellido,
               estudiantes[i].edad,
               estudiantes[i].salon,
               estudiantes[i].carrera);
    }
}

void buscarEstudiante() {
    if(contadorEstudiantes == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    int opcion;
    printf("\n=== BUSCAR ESTUDIANTE ===\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por nombre\n");
    printf("3. Buscar por salon\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);
    limpiarBuffer();
    
    switch(opcion) {
        case 1: {
            int id;
            printf("Ingrese ID: ");
            scanf("%d", &id);
            limpiarBuffer();
            
            for(int i = 0; i < contadorEstudiantes; i++) {
                if(estudiantes[i].id == id) {
                    printf("\nEstudiante encontrado:\n");
                    printf("ID: %d\n", estudiantes[i].id);
                    printf("Nombre: %s %s\n", estudiantes[i].nombre, estudiantes[i].apellido);
                    printf("Edad: %d\n", estudiantes[i].edad);
                    printf("Salon: %s\n", estudiantes[i].salon);
                    printf("Carrera: %s\n", estudiantes[i].carrera);
                    return;
                }
            }
            printf("No se encontro estudiante con ID %d\n", id);
            break;
        }
        case 2: {
            char nombre[MAX_NOMBRE];
            printf("Ingrese nombre: ");
            fgets(nombre, MAX_NOMBRE, stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            
            printf("\nResultados de busqueda:\n");
            int encontrados = 0;
            
            for(int i = 0; i < contadorEstudiantes; i++) {
                if(strstr(estudiantes[i].nombre, nombre) != NULL || 
                   strstr(estudiantes[i].apellido, nombre) != NULL) {
                    printf("%d. %s %s (Salon: %s)\n", 
                           estudiantes[i].id, 
                           estudiantes[i].nombre, 
                           estudiantes[i].apellido,
                           estudiantes[i].salon);
                    encontrados++;
                }
            }
            
            if(encontrados == 0) {
                printf("No se encontraron estudiantes con ese nombre.\n");
            }
            break;
        }
        case 3: {
            char salon[MAX_SALON];
            printf("Ingrese salon: ");
            fgets(salon, MAX_SALON, stdin);
            salon[strcspn(salon, "\n")] = 0;
            
            listarPorSalonEspecifico(salon);
            break;
        }
        default:
            printf("Opcion no valida.\n");
    }
}

void listarPorSalonEspecifico(char salon[]) {
    printf("\n=== ESTUDIANTES DEL SALON %s ===\n", salon);
    
    int encontrados = 0;
    for(int i = 0; i < contadorEstudiantes; i++) {
        if(strcmp(estudiantes[i].salon, salon) == 0) {
            printf("%d. %s %s - %d años - %s\n",
                   estudiantes[i].id,
                   estudiantes[i].nombre,
                   estudiantes[i].apellido,
                   estudiantes[i].edad,
                   estudiantes[i].carrera);
            encontrados++;
        }
    }
    
    if(encontrados == 0) {
        printf("No hay estudiantes registrados en este salon.\n");
    }
}

void editarEstudiante() {
    if(contadorEstudiantes == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    int id;
    printf("\n=== EDITAR ESTUDIANTE ===\n");
    printf("Ingrese ID del estudiante a editar: ");
    scanf("%d", &id);
    limpiarBuffer();
    
    for(int i = 0; i < contadorEstudiantes; i++) {
        if(estudiantes[i].id == id) {
            printf("\nEditando estudiante: %s %s\n", 
                   estudiantes[i].nombre, estudiantes[i].apellido);
            
            printf("Nuevo nombre [%s]: ", estudiantes[i].nombre);
            char nuevoNombre[MAX_NOMBRE];
            fgets(nuevoNombre, MAX_NOMBRE, stdin);
            nuevoNombre[strcspn(nuevoNombre, "\n")] = 0;
            if(strlen(nuevoNombre) > 0) {
                strcpy(estudiantes[i].nombre, nuevoNombre);
            }
            
            printf("Nuevo apellido [%s]: ", estudiantes[i].apellido);
            char nuevoApellido[MAX_NOMBRE];
            fgets(nuevoApellido, MAX_NOMBRE, stdin);
            nuevoApellido[strcspn(nuevoApellido, "\n")] = 0;
            if(strlen(nuevoApellido) > 0) {
                strcpy(estudiantes[i].apellido, nuevoApellido);
            }
            
            printf("Nueva edad [%d]: ", estudiantes[i].edad);
            char edadStr[10];
            fgets(edadStr, 10, stdin);
            if(strlen(edadStr) > 1) { // Más que solo el newline
                estudiantes[i].edad = atoi(edadStr);
            }
            
            printf("Nuevo salon [%s]: ", estudiantes[i].salon);
            char nuevoSalon[MAX_SALON];
            fgets(nuevoSalon, MAX_SALON, stdin);
            nuevoSalon[strcspn(nuevoSalon, "\n")] = 0;
            if(strlen(nuevoSalon) > 0) {
                strcpy(estudiantes[i].salon, nuevoSalon);
            }
            
            printf("Nueva carrera [%s]: ", estudiantes[i].carrera);
            char nuevaCarrera[MAX_NOMBRE];
            fgets(nuevaCarrera, MAX_NOMBRE, stdin);
            nuevaCarrera[strcspn(nuevaCarrera, "\n")] = 0;
            if(strlen(nuevaCarrera) > 0) {
                strcpy(estudiantes[i].carrera, nuevaCarrera);
            }
            
            guardarEnArchivo(estudiantes, contadorEstudiantes);
            printf("\n¡Estudiante actualizado exitosamente!\n");
            return;
        }
    }
    
    printf("No se encontro estudiante con ID %d\n", id);
}

void eliminarEstudiante() {
    if(contadorEstudiantes == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    int id;
    printf("\n=== ELIMINAR ESTUDIANTE ===\n");
    printf("Ingrese ID del estudiante a eliminar: ");
    scanf("%d", &id);
    limpiarBuffer();
    
    for(int i = 0; i < contadorEstudiantes; i++) {
        if(estudiantes[i].id == id) {
            printf("\nEstudiante a eliminar:\n");
            printf("ID: %d\n", estudiantes[i].id);
            printf("Nombre: %s %s\n", estudiantes[i].nombre, estudiantes[i].apellido);
            printf("Salon: %s\n", estudiantes[i].salon);
            
            char confirmacion;
            printf("\n¿Esta seguro de eliminar este estudiante? (s/n): ");
            scanf("%c", &confirmacion);
            limpiarBuffer();
            
            if(confirmacion == 's' || confirmacion == 'S') {
                // Mover todos los elementos una posición hacia atrás
                for(int j = i; j < contadorEstudiantes - 1; j++) {
                    estudiantes[j] = estudiantes[j + 1];
                }
                contadorEstudiantes--;
                
                guardarEnArchivo(estudiantes, contadorEstudiantes);
                printf("¡Estudiante eliminado exitosamente!\n");
            } else {
                printf("Eliminacion cancelada.\n");
            }
            return;
        }
    }
    
    printf("No se encontro estudiante con ID %d\n", id);
}

void listarPorSalon() {
    if(contadorEstudiantes == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    printf("\n=== LISTAR POR SALON ===\n");
    
    // Obtener lista única de salones
    char salones[MAX_ESTUDIANTES][MAX_SALON];
    int contadorSalones = 0;
    
    for(int i = 0; i < contadorEstudiantes; i++) {
        int salonExiste = 0;
        for(int j = 0; j < contadorSalones; j++) {
            if(strcmp(estudiantes[i].salon, salones[j]) == 0) {
                salonExiste = 1;
                break;
            }
        }
        if(!salonExiste) {
            strcpy(salones[contadorSalones], estudiantes[i].salon);
            contadorSalones++;
        }
    }
    
    printf("Salones disponibles:\n");
    for(int i = 0; i < contadorSalones; i++) {
        printf("%d. %s\n", i + 1, salones[i]);
    }
    
    if(contadorSalones > 0) {
        int opcion;
        printf("Seleccione salon (1-%d): ", contadorSalones);
        scanf("%d", &opcion);
        limpiarBuffer();
        
        if(opcion >= 1 && opcion <= contadorSalones) {
            listarPorSalonEspecifico(salones[opcion - 1]);
        } else {
            printf("Opcion no valida.\n");
        }
    }
}

void guardarEnArchivo(Estudiante estudiantes[], int contador) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "w");
    if(archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para escritura.\n");
        return;
    }
    
    for(int i = 0; i < contador; i++) {
        fprintf(archivo, "%d,%s,%s,%d,%s,%s\n",
                estudiantes[i].id,
                estudiantes[i].nombre,
                estudiantes[i].apellido,
                estudiantes[i].edad,
                estudiantes[i].salon,
                estudiantes[i].carrera);
    }
    
    fclose(archivo);
}

int cargarDesdeArchivo(Estudiante estudiantes[]) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    if(archivo == NULL) {
        return 0; // Archivo no existe, empezar con 0 estudiantes
    }
    
    int contador = 0;
    char linea[500];
    
    while(fgets(linea, sizeof(linea), archivo) && contador < MAX_ESTUDIANTES) {
        // Remover newline al final
        linea[strcspn(linea, "\n")] = 0;
        
        // Parsear la línea
        char *token = strtok(linea, ",");
        if(token == NULL) continue;
        
        estudiantes[contador].id = atoi(token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(estudiantes[contador].nombre, token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(estudiantes[contador].apellido, token);
        
        token = strtok(NULL, ",");
        if(token) estudiantes[contador].edad = atoi(token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(estudiantes[contador].salon, token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(estudiantes[contador].carrera, token);
        
        contador++;
    }
    
    fclose(archivo);
    return contador;
}

int generarId() {
    static int ultimoId = 0;
    
    if(ultimoId == 0) {
        // Buscar el ID máximo en los estudiantes cargados
        for(int i = 0; i < contadorEstudiantes; i++) {
            if(estudiantes[i].id > ultimoId) {
                ultimoId = estudiantes[i].id;
            }
        }
    }
    
    return ++ultimoId;
}

void limpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
