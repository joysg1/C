#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLEADOS 100
#define ARCHIVO_DATOS "empleados.txt"

// Estructura para almacenar datos del empleado
typedef struct {
    int id;
    char nombre[50];
    char apellido[50];
    char cargo[30];
    float salario_base;
    float horas_trabajadas;
    float salario_neto;
    char fecha_contratacion[11]; // formato: YYYY-MM-DD
} Empleado;

// Prototipos de funciones
void mostrarMenu();
void agregarEmpleado();
void listarEmpleados();
void buscarEmpleado();
void calcularNomina();
void guardarEnArchivo(Empleado emp);
void cargarDesdeArchivo();
int generarId();
void limpiarBuffer();

// Array global para almacenar empleados
Empleado empleados[MAX_EMPLEADOS];
int totalEmpleados = 0;

int main() {
    printf("=== SISTEMA DE NOMINA ===\n");
    
    // Cargar datos existentes al iniciar
    cargarDesdeArchivo();
    
    int opcion;
    
    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        
        switch(opcion) {
            case 1:
                agregarEmpleado();
                break;
            case 2:
                listarEmpleados();
                break;
            case 3:
                buscarEmpleado();
                break;
            case 4:
                calcularNomina();
                break;
            case 5:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
        
        printf("\nPresione Enter para continuar...");
        getchar();
        
    } while(opcion != 5);
    
    return 0;
}

void mostrarMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Agregar empleado\n");
    printf("2. Listar empleados\n");
    printf("3. Buscar empleado\n");
    printf("4. Calcular nomina\n");
    printf("5. Salir\n");
    printf("======================\n");
}

void agregarEmpleado() {
    if(totalEmpleados >= MAX_EMPLEADOS) {
        printf("Error: No se pueden agregar mas empleados. Limite alcanzado.\n");
        return;
    }
    
    Empleado nuevo;
    
    nuevo.id = generarId();
    
    printf("\n=== AGREGAR NUEVO EMPLEADO ===\n");
    
    printf("Nombre: ");
    fgets(nuevo.nombre, 50, stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;
    
    printf("Apellido: ");
    fgets(nuevo.apellido, 50, stdin);
    nuevo.apellido[strcspn(nuevo.apellido, "\n")] = 0;
    
    printf("Cargo: ");
    fgets(nuevo.cargo, 30, stdin);
    nuevo.cargo[strcspn(nuevo.cargo, "\n")] = 0;
    
    printf("Salario base: ");
    scanf("%f", &nuevo.salario_base);
    
    printf("Horas trabajadas: ");
    scanf("%f", &nuevo.horas_trabajadas);
    
    limpiarBuffer();
    
    printf("Fecha de contratacion (YYYY-MM-DD): ");
    fgets(nuevo.fecha_contratacion, 11, stdin);
    nuevo.fecha_contratacion[strcspn(nuevo.fecha_contratacion, "\n")] = 0;
    
    // Calcular salario neto (simplificado)
    nuevo.salario_neto = nuevo.salario_base * nuevo.horas_trabajadas;
    
    // Guardar en array y archivo
    empleados[totalEmpleados] = nuevo;
    guardarEnArchivo(nuevo);
    totalEmpleados++;
    
    printf("\nEmpleado agregado exitosamente!\n");
    printf("ID asignado: %d\n", nuevo.id);
}

void listarEmpleados() {
    if(totalEmpleados == 0) {
        printf("No hay empleados registrados.\n");
        return;
    }
    
    printf("\n=== LISTA DE EMPLEADOS ===\n");
    printf("%-5s %-15s %-15s %-15s %-12s %-8s %-12s %-15s\n", 
           "ID", "Nombre", "Apellido", "Cargo", "Salario Base", "Horas", "Salario Neto", "Fecha Contrato");
    printf("---------------------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < totalEmpleados; i++) {
        printf("%-5d %-15s %-15s %-15s %-12.2f %-8.1f %-12.2f %-15s\n",
               empleados[i].id,
               empleados[i].nombre,
               empleados[i].apellido,
               empleados[i].cargo,
               empleados[i].salario_base,
               empleados[i].horas_trabajadas,
               empleados[i].salario_neto,
               empleados[i].fecha_contratacion);
    }
}

void buscarEmpleado() {
    if(totalEmpleados == 0) {
        printf("No hay empleados registrados.\n");
        return;
    }
    
    int opcion;
    printf("\n=== BUSCAR EMPLEADO ===\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por apellido\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);
    limpiarBuffer();
    
    if(opcion == 1) {
        int id_buscar;
        printf("Ingrese ID a buscar: ");
        scanf("%d", &id_buscar);
        
        for(int i = 0; i < totalEmpleados; i++) {
            if(empleados[i].id == id_buscar) {
                printf("\nEmpleado encontrado:\n");
                printf("ID: %d\n", empleados[i].id);
                printf("Nombre: %s %s\n", empleados[i].nombre, empleados[i].apellido);
                printf("Cargo: %s\n", empleados[i].cargo);
                printf("Salario base: %.2f\n", empleados[i].salario_base);
                printf("Horas trabajadas: %.1f\n", empleados[i].horas_trabajadas);
                printf("Salario neto: %.2f\n", empleados[i].salario_neto);
                printf("Fecha contratacion: %s\n", empleados[i].fecha_contratacion);
                return;
            }
        }
        printf("Empleado con ID %d no encontrado.\n", id_buscar);
        
    } else if(opcion == 2) {
        char apellido_buscar[50];
        printf("Ingrese apellido a buscar: ");
        fgets(apellido_buscar, 50, stdin);
        apellido_buscar[strcspn(apellido_buscar, "\n")] = 0;
        
        int encontrados = 0;
        for(int i = 0; i < totalEmpleados; i++) {
            if(strcasecmp(empleados[i].apellido, apellido_buscar) == 0) {
                if(encontrados == 0) {
                    printf("\nEmpleados encontrados:\n");
                }
                printf("%d - %s %s (%s)\n", 
                       empleados[i].id, 
                       empleados[i].nombre, 
                       empleados[i].apellido,
                       empleados[i].cargo);
                encontrados++;
            }
        }
        
        if(encontrados == 0) {
            printf("No se encontraron empleados con el apellido '%s'.\n", apellido_buscar);
        }
    } else {
        printf("Opcion no valida.\n");
    }
}

void calcularNomina() {
    if(totalEmpleados == 0) {
        printf("No hay empleados registrados.\n");
        return;
    }
    
    float nomina_total = 0;
    
    printf("\n=== CALCULO DE NOMINA ===\n");
    printf("%-5s %-15s %-15s %-12s %-8s %-12s\n", 
           "ID", "Nombre", "Apellido", "Salario Base", "Horas", "Salario Neto");
    printf("----------------------------------------------------------------\n");
    
    for(int i = 0; i < totalEmpleados; i++) {
        printf("%-5d %-15s %-15s %-12.2f %-8.1f %-12.2f\n",
               empleados[i].id,
               empleados[i].nombre,
               empleados[i].apellido,
               empleados[i].salario_base,
               empleados[i].horas_trabajadas,
               empleados[i].salario_neto);
        nomina_total += empleados[i].salario_neto;
    }
    
    printf("\nTOTAL NOMINA: %.2f\n", nomina_total);
}

void guardarEnArchivo(Empleado emp) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "a");
    if(archivo == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    
    fprintf(archivo, "%d,%s,%s,%s,%.2f,%.1f,%.2f,%s\n",
            emp.id,
            emp.nombre,
            emp.apellido,
            emp.cargo,
            emp.salario_base,
            emp.horas_trabajadas,
            emp.salario_neto,
            emp.fecha_contratacion);
    
    fclose(archivo);
}

void cargarDesdeArchivo() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    if(archivo == NULL) {
        printf("No se encontro archivo de datos existente. Se creara uno nuevo.\n");
        return;
    }
    
    totalEmpleados = 0;
    char linea[256];
    
    while(fgets(linea, sizeof(linea), archivo) && totalEmpleados < MAX_EMPLEADOS) {
        Empleado emp;
        
        char *token = strtok(linea, ",");
        if(token == NULL) continue;
        
        emp.id = atoi(token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(emp.nombre, token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(emp.apellido, token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(emp.cargo, token);
        
        token = strtok(NULL, ",");
        if(token) emp.salario_base = atof(token);
        
        token = strtok(NULL, ",");
        if(token) emp.horas_trabajadas = atof(token);
        
        token = strtok(NULL, ",");
        if(token) emp.salario_neto = atof(token);
        
        token = strtok(NULL, ",");
        if(token) {
            strcpy(emp.fecha_contratacion, token);
            // Eliminar salto de línea si existe
            emp.fecha_contratacion[strcspn(emp.fecha_contratacion, "\n")] = 0;
        }
        
        empleados[totalEmpleados] = emp;
        totalEmpleados++;
    }
    
    fclose(archivo);
    printf("Datos cargados: %d empleados encontrados.\n", totalEmpleados);
}

int generarId() {
    static int ultimoId = 0;
    
    if(ultimoId == 0) {
        // Buscar el ID más alto en los datos cargados
        for(int i = 0; i < totalEmpleados; i++) {
            if(empleados[i].id > ultimoId) {
                ultimoId = empleados[i].id;
            }
        }
    }
    
    return ++ultimoId;
}

void limpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
