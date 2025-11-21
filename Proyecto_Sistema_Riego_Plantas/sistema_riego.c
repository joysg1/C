#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLANTAS 100
#define ARCHIVO_DATOS "registro_riego.txt"

// Estructura para almacenar los datos de riego
typedef struct {
    char nombre_planta[50];
    char tipo_planta[30];
    char fecha_riego[11]; // formato: YYYY-MM-DD
    char proximo_riego[11];
    int cantidad_agua; // en ml
    char observaciones[100];
} Riego;

// Prototipos de funciones
void mostrar_menu();
void agregar_registro();
void mostrar_registros();
void buscar_planta();
void eliminar_registro();
void cargar_registros(Riego registros[], int *contador);
void guardar_registros(Riego registros[], int contador);
void obtener_fecha_actual(char *fecha);

int main() {
    int opcion;
    
    printf("=== SISTEMA DE REGISTRO DE RIEGO DE PLANTAS ORNAMENTALES ===\n");
    
    do {
        mostrar_menu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                agregar_registro();
                break;
            case 2:
                mostrar_registros();
                break;
            case 3:
                buscar_planta();
                break;
            case 4:
                eliminar_registro();
                break;
            case 5:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
        }
        
        printf("\n");
    } while(opcion != 5);
    
    return 0;
}

void mostrar_menu() {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Agregar registro de riego\n");
    printf("2. Mostrar todos los registros\n");
    printf("3. Buscar planta por nombre\n");
    printf("4. Eliminar registro\n");
    printf("5. Salir\n");
}

void agregar_registro() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "a");
    Riego nuevo;
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    printf("\n--- NUEVO REGISTRO DE RIEGO ---\n");
    
    printf("Nombre de la planta: ");
    fgets(nuevo.nombre_planta, sizeof(nuevo.nombre_planta), stdin);
    nuevo.nombre_planta[strcspn(nuevo.nombre_planta, "\n")] = 0; // Eliminar salto de línea
    
    printf("Tipo de planta: ");
    fgets(nuevo.tipo_planta, sizeof(nuevo.tipo_planta), stdin);
    nuevo.tipo_planta[strcspn(nuevo.tipo_planta, "\n")] = 0;
    
    printf("Cantidad de agua (ml): ");
    scanf("%d", &nuevo.cantidad_agua);
    getchar(); // Limpiar buffer
    
    printf("Observaciones: ");
    fgets(nuevo.observaciones, sizeof(nuevo.observaciones), stdin);
    nuevo.observaciones[strcspn(nuevo.observaciones, "\n")] = 0;
    
    // Obtener fecha actual
    obtener_fecha_actual(nuevo.fecha_riego);
    
    // Calcular próximo riego (7 días después)
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    tm_info->tm_mday += 7; // Agregar 7 días
    mktime(tm_info);
    strftime(nuevo.proximo_riego, sizeof(nuevo.proximo_riego), "%Y-%m-%d", tm_info);
    
    // Guardar en archivo
    fprintf(archivo, "%s|%s|%s|%s|%d|%s\n",
            nuevo.nombre_planta,
            nuevo.tipo_planta,
            nuevo.fecha_riego,
            nuevo.proximo_riego,
            nuevo.cantidad_agua,
            nuevo.observaciones);
    
    fclose(archivo);
    
    printf("\nRegistro agregado exitosamente!\n");
    printf("Proximo riego programado para: %s\n", nuevo.proximo_riego);
}

void mostrar_registros() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    Riego registro;
    char linea[256];
    int contador = 0;
    
    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }
    
    printf("\n--- TODOS LOS REGISTROS DE RIEGO ---\n");
    printf("=======================================================================================\n");
    printf("No. | Nombre           | Tipo            | Fecha Riego | Proximo Riego | Agua | Observaciones\n");
    printf("=======================================================================================\n");
    
    while (fgets(linea, sizeof(linea), archivo)) {
        // Parsear la línea
        char *token = strtok(linea, "|");
        if (token) strcpy(registro.nombre_planta, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registro.tipo_planta, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registro.fecha_riego, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registro.proximo_riego, token);
        
        token = strtok(NULL, "|");
        if (token) registro.cantidad_agua = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) {
            strcpy(registro.observaciones, token);
            // Eliminar salto de línea si existe
            registro.observaciones[strcspn(registro.observaciones, "\n")] = 0;
        }
        
        contador++;
        printf("%-3d | %-15s | %-15s | %-11s | %-13s | %-4d | %s\n",
               contador,
               registro.nombre_planta,
               registro.tipo_planta,
               registro.fecha_riego,
               registro.proximo_riego,
               registro.cantidad_agua,
               registro.observaciones);
    }
    
    fclose(archivo);
    
    if (contador == 0) {
        printf("No hay registros disponibles.\n");
    } else {
        printf("=======================================================================================\n");
        printf("Total de registros: %d\n", contador);
    }
}

void buscar_planta() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    Riego registro;
    char linea[256];
    char nombre_buscar[50];
    int encontrado = 0;
    
    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }
    
    printf("\n--- BUSCAR PLANTA ---\n");
    printf("Nombre de la planta a buscar: ");
    fgets(nombre_buscar, sizeof(nombre_buscar), stdin);
    nombre_buscar[strcspn(nombre_buscar, "\n")] = 0;
    
    printf("\nResultados de la busqueda:\n");
    printf("=======================================================================================\n");
    printf("No. | Nombre           | Tipo            | Fecha Riego | Proximo Riego | Agua | Observaciones\n");
    printf("=======================================================================================\n");
    
    int contador = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        char temp_linea[256];
        strcpy(temp_linea, linea);
        
        char *token = strtok(temp_linea, "|");
        if (token && strstr(token, nombre_buscar) != NULL) {
            // Parsear la línea completa
            token = strtok(linea, "|");
            if (token) strcpy(registro.nombre_planta, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.tipo_planta, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.fecha_riego, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.proximo_riego, token);
            
            token = strtok(NULL, "|");
            if (token) registro.cantidad_agua = atoi(token);
            
            token = strtok(NULL, "|");
            if (token) {
                strcpy(registro.observaciones, token);
                registro.observaciones[strcspn(registro.observaciones, "\n")] = 0;
            }
            
            contador++;
            printf("%-3d | %-15s | %-15s | %-11s | %-13s | %-4d | %s\n",
                   contador,
                   registro.nombre_planta,
                   registro.tipo_planta,
                   registro.fecha_riego,
                   registro.proximo_riego,
                   registro.cantidad_agua,
                   registro.observaciones);
            encontrado = 1;
        }
    }
    
    fclose(archivo);
    
    if (!encontrado) {
        printf("No se encontraron plantas con el nombre '%s'.\n", nombre_buscar);
    } else {
        printf("=======================================================================================\n");
        printf("Se encontraron %d registro(s).\n", contador);
    }
}

void eliminar_registro() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    FILE *temp = fopen("temp.txt", "w");
    Riego registros[MAX_PLANTAS];
    char linea[256];
    int contador = 0;
    int indice_eliminar;
    
    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }
    
    // Cargar todos los registros
    while (fgets(linea, sizeof(linea), archivo) && contador < MAX_PLANTAS) {
        strcpy(registros[contador].nombre_planta, strtok(linea, "|"));
        strcpy(registros[contador].tipo_planta, strtok(NULL, "|"));
        strcpy(registros[contador].fecha_riego, strtok(NULL, "|"));
        strcpy(registros[contador].proximo_riego, strtok(NULL, "|"));
        registros[contador].cantidad_agua = atoi(strtok(NULL, "|"));
        char *obs = strtok(NULL, "|");
        if (obs) {
            strcpy(registros[contador].observaciones, obs);
            registros[contador].observaciones[strcspn(registros[contador].observaciones, "\n")] = 0;
        }
        contador++;
    }
    fclose(archivo);
    
    if (contador == 0) {
        printf("No hay registros para eliminar.\n");
        fclose(temp);
        remove("temp.txt");
        return;
    }
    
    // Mostrar registros para seleccionar
    printf("\n--- ELIMINAR REGISTRO ---\n");
    mostrar_registros();
    
    printf("Ingrese el numero del registro a eliminar (0 para cancelar): ");
    scanf("%d", &indice_eliminar);
    
    if (indice_eliminar == 0 || indice_eliminar > contador) {
        printf("Operacion cancelada.\n");
        fclose(temp);
        remove("temp.txt");
        return;
    }
    
    // Guardar todos los registros excepto el eliminado
    archivo = fopen(ARCHIVO_DATOS, "w");
    for (int i = 0; i < contador; i++) {
        if (i != indice_eliminar - 1) {
            fprintf(archivo, "%s|%s|%s|%s|%d|%s\n",
                    registros[i].nombre_planta,
                    registros[i].tipo_planta,
                    registros[i].fecha_riego,
                    registros[i].proximo_riego,
                    registros[i].cantidad_agua,
                    registros[i].observaciones);
        }
    }
    fclose(archivo);
    
    printf("Registro eliminado exitosamente!\n");
}

void obtener_fecha_actual(char *fecha) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(fecha, 11, "%Y-%m-%d", tm_info);
}
