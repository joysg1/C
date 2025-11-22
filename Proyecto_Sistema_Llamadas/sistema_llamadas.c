#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LLAMADAS 100
#define ARCHIVO_DATOS "llamadas.txt"

// Estructura para representar una llamada telefónica
typedef struct {
    int id;
    char numero[20];
    char fecha[11];  // formato: YYYY-MM-DD
    char hora[9];    // formato: HH:MM:SS
    int duracion;    // en segundos
    char tipo[10];   // "Entrante", "Saliente", "Perdida"
    char contacto[50];
} Llamada;

// Prototipos de funciones
void mostrarMenu();
void agregarLlamada(Llamada llamadas[], int *contador);
void listarLlamadas(Llamada llamadas[], int contador);
void buscarPorNumero(Llamada llamadas[], int contador);
void buscarPorContacto(Llamada llamadas[], int contador);
void guardarDatos(Llamada llamadas[], int contador);
void cargarDatos(Llamada llamadas[], int *contador);
void generarReporte(Llamada llamadas[], int contador);
void obtenerFechaHoraActual(char fecha[], char hora[]);

int main() {
    Llamada llamadas[MAX_LLAMADAS];
    int contador = 0;
    int opcion;
    
    // Cargar datos existentes al iniciar
    cargarDatos(llamadas, &contador);
    
    printf("=== SISTEMA DE REGISTRO DE LLAMADAS TELEFÓNICAS ===\n");
    
    do {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                agregarLlamada(llamadas, &contador);
                break;
            case 2:
                listarLlamadas(llamadas, contador);
                break;
            case 3:
                buscarPorNumero(llamadas, contador);
                break;
            case 4:
                buscarPorContacto(llamadas, contador);
                break;
            case 5:
                generarReporte(llamadas, contador);
                break;
            case 6:
                guardarDatos(llamadas, contador);
                printf("Datos guardados correctamente.\n");
                break;
            case 0:
                guardarDatos(llamadas, contador);
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
        
        printf("\nPresione Enter para continuar...");
        getchar();
        
    } while(opcion != 0);
    
    return 0;
}

void mostrarMenu() {
    printf("\n=== MENÚ PRINCIPAL ===\n");
    printf("1. Agregar nueva llamada\n");
    printf("2. Listar todas las llamadas\n");
    printf("3. Buscar por número telefónico\n");
    printf("4. Buscar por contacto\n");
    printf("5. Generar reporte estadístico\n");
    printf("6. Guardar datos\n");
    printf("0. Salir\n");
    printf("======================\n");
}

void agregarLlamada(Llamada llamadas[], int *contador) {
    if (*contador >= MAX_LLAMADAS) {
        printf("Error: Se ha alcanzado el límite máximo de llamadas.\n");
        return;
    }
    
    Llamada nueva;
    nueva.id = *contador + 1;
    
    printf("\n=== AGREGAR NUEVA LLAMADA ===\n");
    
    printf("Número telefónico: ");
    fgets(nueva.numero, sizeof(nueva.numero), stdin);
    nueva.numero[strcspn(nueva.numero, "\n")] = 0;
    
    printf("Nombre del contacto: ");
    fgets(nueva.contacto, sizeof(nueva.contacto), stdin);
    nueva.contacto[strcspn(nueva.contacto, "\n")] = 0;
    
    printf("Duración (en segundos): ");
    scanf("%d", &nueva.duracion);
    getchar();
    
    printf("Tipo (Entrante/Saliente/Perdida): ");
    fgets(nueva.tipo, sizeof(nueva.tipo), stdin);
    nueva.tipo[strcspn(nueva.tipo, "\n")] = 0;
    
    // Obtener fecha y hora actual
    obtenerFechaHoraActual(nueva.fecha, nueva.hora);
    
    llamadas[*contador] = nueva;
    (*contador)++;
    
    printf("Llamada registrada exitosamente con ID: %d\n", nueva.id);
}

void listarLlamadas(Llamada llamadas[], int contador) {
    if (contador == 0) {
        printf("No hay llamadas registradas.\n");
        return;
    }
    
    printf("\n=== LISTA DE LLAMADAS ===\n");
    printf("ID  | Fecha     | Hora    | Número       | Contacto          | Duración | Tipo\n");
    printf("----|-----------|---------|-------------|------------------|----------|--------\n");
    
    for (int i = 0; i < contador; i++) {
        printf("%-3d | %-9s | %-7s | %-11s | %-16s | %-8d | %s\n",
               llamadas[i].id, llamadas[i].fecha, llamadas[i].hora,
               llamadas[i].numero, llamadas[i].contacto, 
               llamadas[i].duracion, llamadas[i].tipo);
    }
}

void buscarPorNumero(Llamada llamadas[], int contador) {
    if (contador == 0) {
        printf("No hay llamadas registradas.\n");
        return;
    }
    
    char numeroBuscado[20];
    printf("Ingrese el número a buscar: ");
    fgets(numeroBuscado, sizeof(numeroBuscado), stdin);
    numeroBuscado[strcspn(numeroBuscado, "\n")] = 0;
    
    printf("\n=== RESULTADOS DE BÚSQUEDA ===\n");
    int encontradas = 0;
    
    for (int i = 0; i < contador; i++) {
        if (strstr(llamadas[i].numero, numeroBuscado) != NULL) {
            printf("ID: %d, Fecha: %s, Hora: %s, Contacto: %s, Duración: %ds, Tipo: %s\n",
                   llamadas[i].id, llamadas[i].fecha, llamadas[i].hora,
                   llamadas[i].contacto, llamadas[i].duracion, llamadas[i].tipo);
            encontradas++;
        }
    }
    
    if (encontradas == 0) {
        printf("No se encontraron llamadas con ese número.\n");
    }
}

void buscarPorContacto(Llamada llamadas[], int contador) {
    if (contador == 0) {
        printf("No hay llamadas registradas.\n");
        return;
    }
    
    char contactoBuscado[50];
    printf("Ingrese el contacto a buscar: ");
    fgets(contactoBuscado, sizeof(contactoBuscado), stdin);
    contactoBuscado[strcspn(contactoBuscado, "\n")] = 0;
    
    printf("\n=== RESULTADOS DE BÚSQUEDA ===\n");
    int encontradas = 0;
    
    for (int i = 0; i < contador; i++) {
        if (strstr(llamadas[i].contacto, contactoBuscado) != NULL) {
            printf("ID: %d, Fecha: %s, Hora: %s, Número: %s, Duración: %ds, Tipo: %s\n",
                   llamadas[i].id, llamadas[i].fecha, llamadas[i].hora,
                   llamadas[i].numero, llamadas[i].duracion, llamadas[i].tipo);
            encontradas++;
        }
    }
    
    if (encontradas == 0) {
        printf("No se encontraron llamadas con ese contacto.\n");
    }
}

void generarReporte(Llamada llamadas[], int contador) {
    if (contador == 0) {
        printf("No hay llamadas registradas para generar reporte.\n");
        return;
    }
    
    int entrantes = 0, salientes = 0, perdidas = 0;
    int totalDuracion = 0;
    int maxDuracion = 0;
    char contactoMasLlamado[50] = "";
    int llamadasPorContacto[50] = {0};
    char contactos[50][50] = {0};
    int numContactos = 0;
    
    for (int i = 0; i < contador; i++) {
        // Contar por tipo
        if (strcmp(llamadas[i].tipo, "Entrante") == 0) entrantes++;
        else if (strcmp(llamadas[i].tipo, "Saliente") == 0) salientes++;
        else if (strcmp(llamadas[i].tipo, "Perdida") == 0) perdidas++;
        
        // Estadísticas de duración
        totalDuracion += llamadas[i].duracion;
        if (llamadas[i].duracion > maxDuracion) {
            maxDuracion = llamadas[i].duracion;
        }
        
        // Contar llamadas por contacto
        int encontrado = 0;
        for (int j = 0; j < numContactos; j++) {
            if (strcmp(contactos[j], llamadas[i].contacto) == 0) {
                llamadasPorContacto[j]++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(contactos[numContactos], llamadas[i].contacto);
            llamadasPorContacto[numContactos] = 1;
            numContactos++;
        }
    }
    
    // Encontrar contacto más frecuente
    int maxLlamadas = 0;
    int indiceMasLlamado = 0;
    for (int i = 0; i < numContactos; i++) {
        if (llamadasPorContacto[i] > maxLlamadas) {
            maxLlamadas = llamadasPorContacto[i];
            indiceMasLlamado = i;
        }
    }
    
    printf("\n=== REPORTE ESTADÍSTICO ===\n");
    printf("Total de llamadas: %d\n", contador);
    printf("Llamadas entrantes: %d\n", entrantes);
    printf("Llamadas salientes: %d\n", salientes);
    printf("Llamadas perdidas: %d\n", perdidas);
    printf("Duración total: %d segundos\n", totalDuracion);
    printf("Duración promedio: %.2f segundos\n", (float)totalDuracion/contador);
    printf("Duración máxima: %d segundos\n", maxDuracion);
    printf("Contacto más frecuente: %s (%d llamadas)\n", 
           contactos[indiceMasLlamado], maxLlamadas);
}

void guardarDatos(Llamada llamadas[], int contador) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }
    
    for (int i = 0; i < contador; i++) {
        fprintf(archivo, "%d|%s|%s|%s|%d|%s|%s\n",
                llamadas[i].id,
                llamadas[i].numero,
                llamadas[i].contacto,
                llamadas[i].fecha,
                llamadas[i].duracion,
                llamadas[i].tipo,
                llamadas[i].hora);
    }
    
    fclose(archivo);
}

void cargarDatos(Llamada llamadas[], int *contador) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    if (archivo == NULL) {
        printf("No se encontró archivo de datos previo. Se creará uno nuevo.\n");
        return;
    }
    
    *contador = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), archivo) && *contador < MAX_LLAMADAS) {
        // Remover salto de línea
        linea[strcspn(linea, "\n")] = 0;
        
        Llamada llamada;
        char *token = strtok(linea, "|");
        
        if (token) llamada.id = atoi(token);
        token = strtok(NULL, "|");
        if (token) strcpy(llamada.numero, token);
        token = strtok(NULL, "|");
        if (token) strcpy(llamada.contacto, token);
        token = strtok(NULL, "|");
        if (token) strcpy(llamada.fecha, token);
        token = strtok(NULL, "|");
        if (token) llamada.duracion = atoi(token);
        token = strtok(NULL, "|");
        if (token) strcpy(llamada.tipo, token);
        token = strtok(NULL, "|");
        if (token) strcpy(llamada.hora, token);
        
        llamadas[*contador] = llamada;
        (*contador)++;
    }
    
    fclose(archivo);
    printf("Datos cargados: %d llamadas registradas.\n", *contador);
}

void obtenerFechaHoraActual(char fecha[], char hora[]) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    strftime(fecha, 11, "%Y-%m-%d", tm_info);
    strftime(hora, 9, "%H:%M:%S", tm_info);
}
