#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_REGISTROS 200
#define ARCHIVO_DATOS "registro_alimentacion.txt"
#define ARCHIVO_INVENTARIO "inventario_alimentos.txt"

// Estructura para almacenar los datos de alimentación
typedef struct {
    char fecha[11];
    char tipo_alimento[50];
    float cantidad_kg;
    int numero_gallinas;
    char etapa_produccion[20];
    char observaciones[100];
    char proveedor[50];
    float costo;
} Alimentacion;

// Estructura para inventario
typedef struct {
    char tipo_alimento[50];
    float stock_kg;
    float precio_kg;
    char fecha_compra[11];
    char fecha_vencimiento[11];
} Inventario;

// Prototipos de funciones
void mostrar_menu_principal();
void mostrar_menu_inventario();
void registrar_alimentacion();
void mostrar_registros();
void buscar_registros();
void generar_reporte();
void gestionar_inventario();
void agregar_alimento_inventario();
void mostrar_inventario();
void buscar_alimento_inventario();
void actualizar_stock();
void obtener_fecha_actual(char *fecha);
void calcular_consumo_promedio();
void recomendar_alimentacion();
void eliminar_registro();

int main() {
    int opcion;
    
    printf("=== SISTEMA DE REGISTRO DE ALIMENTACIÓN DE GALLINAS ===\n");
    printf("            🐔 Granja Avícola Integral 🥚\n\n");
    
    do {
        mostrar_menu_principal();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer
        
        switch(opcion) {
            case 1:
                registrar_alimentacion();
                break;
            case 2:
                mostrar_registros();
                break;
            case 3:
                buscar_registros();
                break;
            case 4:
                gestionar_inventario();
                break;
            case 5:
                generar_reporte();
                break;
            case 6:
                calcular_consumo_promedio();
                break;
            case 7:
                recomendar_alimentacion();
                break;
            case 8:
                eliminar_registro();
                break;
            case 9:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
        
        printf("\n");
    } while(opcion != 9);
    
    return 0;
}

void mostrar_menu_principal() {
    printf("\n--- MENÚ PRINCIPAL ---\n");
    printf("1. Registrar alimentación diaria\n");
    printf("2. Mostrar todos los registros\n");
    printf("3. Buscar registros\n");
    printf("4. Gestión de inventario\n");
    printf("5. Generar reporte mensual\n");
    printf("6. Calcular consumo promedio\n");
    printf("7. Recomendaciones de alimentación\n");
    printf("8. Eliminar registro\n");
    printf("9. Salir\n");
}

void mostrar_menu_inventario() {
    printf("\n--- GESTIÓN DE INVENTARIO ---\n");
    printf("1. Agregar alimento al inventario\n");
    printf("2. Mostrar inventario completo\n");
    printf("3. Buscar alimento\n");
    printf("4. Actualizar stock\n");
    printf("5. Volver al menú principal\n");
}

void registrar_alimentacion() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "a");
    Alimentacion nuevo;
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    
    printf("\n--- REGISTRO DE ALIMENTACIÓN DIARIA ---\n");
    
    // Obtener fecha actual
    obtener_fecha_actual(nuevo.fecha);
    printf("Fecha: %s\n", nuevo.fecha);
    
    printf("Tipo de alimento: ");
    fgets(nuevo.tipo_alimento, sizeof(nuevo.tipo_alimento), stdin);
    nuevo.tipo_alimento[strcspn(nuevo.tipo_alimento, "\n")] = 0;
    
    printf("Cantidad (kg): ");
    scanf("%f", &nuevo.cantidad_kg);
    
    printf("Número de gallinas: ");
    scanf("%d", &nuevo.numero_gallinas);
    getchar();
    
    printf("Etapa de producción (polla, desarrollo, postura, engorde): ");
    fgets(nuevo.etapa_produccion, sizeof(nuevo.etapa_produccion), stdin);
    nuevo.etapa_produccion[strcspn(nuevo.etapa_produccion, "\n")] = 0;
    
    printf("Proveedor: ");
    fgets(nuevo.proveedor, sizeof(nuevo.proveedor), stdin);
    nuevo.proveedor[strcspn(nuevo.proveedor, "\n")] = 0;
    
    printf("Costo total: $");
    scanf("%f", &nuevo.costo);
    getchar();
    
    printf("Observaciones: ");
    fgets(nuevo.observaciones, sizeof(nuevo.observaciones), stdin);
    nuevo.observaciones[strcspn(nuevo.observaciones, "\n")] = 0;
    
    // Guardar en archivo
    fprintf(archivo, "%s|%s|%.2f|%d|%s|%s|%.2f|%s\n",
            nuevo.fecha,
            nuevo.tipo_alimento,
            nuevo.cantidad_kg,
            nuevo.numero_gallinas,
            nuevo.etapa_produccion,
            nuevo.proveedor,
            nuevo.costo,
            nuevo.observaciones);
    
    fclose(archivo);
    
    printf("\n✅ Registro agregado exitosamente!\n");
    printf("📊 Consumo por gallina: %.3f kg\n", nuevo.cantidad_kg / nuevo.numero_gallinas);
}

void mostrar_registros() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    Alimentacion registro;
    char linea[256];
    int contador = 0;
    float total_kg = 0, total_costo = 0;
    
    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }
    
    printf("\n--- TODOS LOS REGISTROS DE ALIMENTACIÓN ---\n");
    printf("============================================================================================================\n");
    printf("No. | Fecha     | Alimento           | Cantidad | Gallinas | Etapa    | Proveedor      | Costo  | Observaciones\n");
    printf("============================================================================================================\n");
    
    while (fgets(linea, sizeof(linea), archivo)) {
        // Parsear la línea
        char *token = strtok(linea, "|");
        if (token) strcpy(registro.fecha, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registro.tipo_alimento, token);
        
        token = strtok(NULL, "|");
        if (token) registro.cantidad_kg = atof(token);
        
        token = strtok(NULL, "|");
        if (token) registro.numero_gallinas = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registro.etapa_produccion, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registro.proveedor, token);
        
        token = strtok(NULL, "|");
        if (token) registro.costo = atof(token);
        
        token = strtok(NULL, "|");
        if (token) {
            strcpy(registro.observaciones, token);
            registro.observaciones[strcspn(registro.observaciones, "\n")] = 0;
        }
        
        contador++;
        total_kg += registro.cantidad_kg;
        total_costo += registro.costo;
        
        printf("%-3d | %-9s | %-18s | %-8.2f | %-8d | %-8s | %-13s | $%-5.2f | %s\n",
               contador,
               registro.fecha,
               registro.tipo_alimento,
               registro.cantidad_kg,
               registro.numero_gallinas,
               registro.etapa_produccion,
               registro.proveedor,
               registro.costo,
               registro.observaciones);
    }
    
    fclose(archivo);
    
    if (contador == 0) {
        printf("No hay registros disponibles.\n");
    } else {
        printf("============================================================================================================\n");
        printf("Total registros: %d | Total kg: %.2f | Total costo: $%.2f | Promedio diario: $%.2f\n", 
               contador, total_kg, total_costo, total_costo/contador);
    }
}

void buscar_registros() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    Alimentacion registro;
    char linea[256];
    char criterio[50];
    int opcion, encontrado = 0;
    float total_kg = 0, total_costo = 0;
    
    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }
    
    printf("\n--- BUSCAR REGISTROS ---\n");
    printf("1. Por tipo de alimento\n");
    printf("2. Por etapa de producción\n");
    printf("3. Por fecha\n");
    printf("4. Por proveedor\n");
    printf("Seleccione criterio de búsqueda: ");
    scanf("%d", &opcion);
    getchar();
    
    printf("Ingrese término de búsqueda: ");
    fgets(criterio, sizeof(criterio), stdin);
    criterio[strcspn(criterio, "\n")] = 0;
    
    printf("\nResultados de la búsqueda:\n");
    printf("============================================================================================================\n");
    printf("No. | Fecha     | Alimento           | Cantidad | Gallinas | Etapa    | Proveedor      | Costo  | Observaciones\n");
    printf("============================================================================================================\n");
    
    int contador = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        char temp_linea[256];
        strcpy(temp_linea, linea);
        
        char *token = strtok(temp_linea, "|");
        char fecha[11], alimento[50], etapa[20], proveedor[50];
        
        if (token) strcpy(fecha, token);
        token = strtok(NULL, "|");
        if (token) strcpy(alimento, token);
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        if (token) strcpy(etapa, token);
        token = strtok(NULL, "|");
        if (token) strcpy(proveedor, token);
        
        int coincide = 0;
        switch(opcion) {
            case 1: coincide = (strstr(alimento, criterio) != NULL); break;
            case 2: coincide = (strstr(etapa, criterio) != NULL); break;
            case 3: coincide = (strstr(fecha, criterio) != NULL); break;
            case 4: coincide = (strstr(proveedor, criterio) != NULL); break;
        }
        
        if (coincide) {
            // Parsear la línea completa
            token = strtok(linea, "|");
            if (token) strcpy(registro.fecha, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.tipo_alimento, token);
            
            token = strtok(NULL, "|");
            if (token) registro.cantidad_kg = atof(token);
            
            token = strtok(NULL, "|");
            if (token) registro.numero_gallinas = atoi(token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.etapa_produccion, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.proveedor, token);
            
            token = strtok(NULL, "|");
            if (token) registro.costo = atof(token);
            
            token = strtok(NULL, "|");
            if (token) {
                strcpy(registro.observaciones, token);
                registro.observaciones[strcspn(registro.observaciones, "\n")] = 0;
            }
            
            contador++;
            total_kg += registro.cantidad_kg;
            total_costo += registro.costo;
            encontrado = 1;
            
            printf("%-3d | %-9s | %-18s | %-8.2f | %-8d | %-8s | %-13s | $%-5.2f | %s\n",
                   contador,
                   registro.fecha,
                   registro.tipo_alimento,
                   registro.cantidad_kg,
                   registro.numero_gallinas,
                   registro.etapa_produccion,
                   registro.proveedor,
                   registro.costo,
                   registro.observaciones);
        }
    }
    
    fclose(archivo);
    
    if (!encontrado) {
        printf("No se encontraron registros.\n");
    } else {
        printf("============================================================================================================\n");
        printf("Encontrados: %d | Total kg: %.2f | Total costo: $%.2f\n", contador, total_kg, total_costo);
    }
}

void generar_reporte() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    Alimentacion registro;
    char linea[256];
    char mes_buscar[8]; // Formato: YYYY-MM
    int anio, mes;
    int encontrado = 0;
    
    // Variables para estadísticas
    float total_kg = 0, total_costo = 0;
    int total_gallinas = 0, total_dias = 0;
    int conteo_etapas[4] = {0}; // polla, desarrollo, postura, engorde
    float costo_por_etapa[4] = {0};
    float kg_por_etapa[4] = {0};
    
    // Arrays para nombres de etapas
    char *nombres_etapas[] = {"polla", "desarrollo", "postura", "engorde"};
    char *nombres_meses[] = {"", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", 
                            "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }

    printf("\n--- GENERAR REPORTE MENSUAL ---\n");
    printf("Ingrese el año (YYYY): ");
    scanf("%d", &anio);
    printf("Ingrese el mes (1-12): ");
    scanf("%d", &mes);
    getchar();

    if (mes < 1 || mes > 12) {
        printf("Mes no válido.\n");
        fclose(archivo);
        return;
    }

    // Formatear mes para búsqueda
    sprintf(mes_buscar, "%04d-%02d", anio, mes);

    printf("\n📊 REPORTE MENSUAL: %s %d\n", nombres_meses[mes], anio);
    printf("==========================================\n");

    // Leer y procesar registros
    while (fgets(linea, sizeof(linea), archivo)) {
        char *token = strtok(linea, "|");
        if (token) strcpy(registro.fecha, token);
        
        // Verificar si el registro corresponde al mes buscado
        if (strncmp(registro.fecha, mes_buscar, 7) == 0) {
            token = strtok(NULL, "|");
            if (token) strcpy(registro.tipo_alimento, token);
            
            token = strtok(NULL, "|");
            if (token) registro.cantidad_kg = atof(token);
            
            token = strtok(NULL, "|");
            if (token) registro.numero_gallinas = atoi(token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.etapa_produccion, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(registro.proveedor, token);
            
            token = strtok(NULL, "|");
            if (token) registro.costo = atof(token);
            
            token = strtok(NULL, "|");
            if (token) {
                strcpy(registro.observaciones, token);
                registro.observaciones[strcspn(registro.observaciones, "\n")] = 0;
            }

            encontrado = 1;
            total_kg += registro.cantidad_kg;
            total_costo += registro.costo;
            total_gallinas += registro.numero_gallinas;
            total_dias++;

            // Clasificar por etapa de producción
            for (int i = 0; i < 4; i++) {
                if (strcmp(registro.etapa_produccion, nombres_etapas[i]) == 0) {
                    conteo_etapas[i]++;
                    costo_por_etapa[i] += registro.costo;
                    kg_por_etapa[i] += registro.cantidad_kg;
                    break;
                }
            }

            // Mostrar registro individual
            printf("📅 %s | 🥣 %-15s | ⚖️ %5.1f kg | 🐔 %3d | 💰 $%6.2f\n",
                   registro.fecha,
                   registro.tipo_alimento,
                   registro.cantidad_kg,
                   registro.numero_gallinas,
                   registro.costo);
        }
    }

    fclose(archivo);

    if (!encontrado) {
        printf("No se encontraron registros para %s %d.\n", nombres_meses[mes], anio);
        return;
    }

    // Mostrar estadísticas detalladas
    printf("\n==========================================\n");
    printf("📈 ESTADÍSTICAS DEL MES\n");
    printf("==========================================\n");
    printf("📅 Días con registro: %d\n", total_dias);
    printf("🐔 Gallinas promedio: %d\n", total_gallinas / total_dias);
    printf("🌾 Total alimento consumido: %.1f kg\n", total_kg);
    printf("💰 Total gastado en alimento: $%.2f\n", total_costo);
    printf("📊 Consumo promedio diario: %.1f kg\n", total_kg / total_dias);
    printf("💵 Costo promedio diario: $%.2f\n", total_costo / total_dias);
    
    if (total_gallinas > 0) {
        printf("🥚 Consumo por gallina/día: %.2f kg\n", total_kg / total_gallinas);
        printf("🏷️  Costo por gallina/día: $%.3f\n", total_costo / total_gallinas);
    }

    printf("\n==========================================\n");
    printf("🐓 DISTRIBUCIÓN POR ETAPA DE PRODUCCIÓN\n");
    printf("==========================================\n");
    
    for (int i = 0; i < 4; i++) {
        if (conteo_etapas[i] > 0) {
            float porcentaje = (conteo_etapas[i] * 100.0) / total_dias;
            printf("%-12s: %2d días (%5.1f%%) | %6.1f kg | $%7.2f\n",
                   nombres_etapas[i],
                   conteo_etapas[i],
                   porcentaje,
                   kg_por_etapa[i],
                   costo_por_etapa[i]);
        }
    }

    // Análisis de costos y recomendaciones
    printf("\n==========================================\n");
    printf("💡 ANÁLISIS Y RECOMENDACIONES\n");
    printf("==========================================\n");
    
    float costo_por_kg = total_costo / total_kg;
    printf("📊 Costo por kg de alimento: $%.2f\n", costo_por_kg);
    
    // Recomendaciones basadas en costos
    if (costo_por_kg > 2.5) {
        printf("⚠️  Costo elevado. Considerar:\n");
        printf("   • Cambiar proveedor\n");
        printf("   • Comprar al por mayor\n");
        printf("   • Evaluar alternativas de alimento\n");
    } else if (costo_por_kg < 1.5) {
        printf("✅ Costo eficiente. Buen manejo.\n");
    } else {
        printf("📈 Costo dentro del rango esperado.\n");
    }

    // Recomendaciones basadas en consumo
    float consumo_por_gallina = total_kg / total_gallinas;
    printf("📊 Consumo mensual por gallina: %.1f kg\n", consumo_por_gallina);
    
    if (consumo_por_gallina > 4.0) {
        printf("⚠️  Consumo alto. Verificar:\n");
        printf("   • Desperdicio en comederos\n");
        printf("   • Presencia de plagas\n");
        printf("   • Eficiencia alimenticia\n");
    } else if (consumo_por_gallina < 2.5) {
        printf("⚠️  Consumo bajo. Verificar:\n");
        printf("   • Salud de las gallinas\n");
        printf("   • Calidad del alimento\n");
        printf("   • Espacio en comederos\n");
    } else {
        printf("✅ Consumo dentro de parámetros normales.\n");
    }

    // Proyección para el próximo mes
    printf("\n==========================================\n");
    printf("🔮 PROYECCIÓN PRÓXIMO MES\n");
    printf("==========================================\n");
    printf("🌾 Alimento necesario: %.0f kg\n", total_kg);
    printf("💰 Presupuesto estimado: $%.0f\n", total_costo);
    printf("📦 Inventario recomendado:\n");
    printf("   • Maíz: %.0f kg\n", total_kg * 0.6);
    printf("   • Concentrado: %.0f kg\n", total_kg * 0.3);
    printf("   • Suplementos: %.0f kg\n", total_kg * 0.1);
}

void gestionar_inventario() {
    int opcion;
    
    do {
        mostrar_menu_inventario();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();
        
        switch(opcion) {
            case 1:
                agregar_alimento_inventario();
                break;
            case 2:
                mostrar_inventario();
                break;
            case 3:
                buscar_alimento_inventario();
                break;
            case 4:
                actualizar_stock();
                break;
            case 5:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while(opcion != 5);
}

void agregar_alimento_inventario() {
    FILE *archivo = fopen(ARCHIVO_INVENTARIO, "a");
    Inventario nuevo;
    
    if (archivo == NULL) {
        printf("Error al abrir el archivo de inventario.\n");
        return;
    }
    
    printf("\n--- AGREGAR ALIMENTO AL INVENTARIO ---\n");
    
    printf("Tipo de alimento: ");
    fgets(nuevo.tipo_alimento, sizeof(nuevo.tipo_alimento), stdin);
    nuevo.tipo_alimento[strcspn(nuevo.tipo_alimento, "\n")] = 0;
    
    printf("Stock actual (kg): ");
    scanf("%f", &nuevo.stock_kg);
    
    printf("Precio por kg: $");
    scanf("%f", &nuevo.precio_kg);
    getchar();
    
    printf("Fecha de compra (YYYY-MM-DD): ");
    fgets(nuevo.fecha_compra, sizeof(nuevo.fecha_compra), stdin);
    nuevo.fecha_compra[strcspn(nuevo.fecha_compra, "\n")] = 0;
    
    printf("Fecha de vencimiento (YYYY-MM-DD): ");
    fgets(nuevo.fecha_vencimiento, sizeof(nuevo.fecha_vencimiento), stdin);
    nuevo.fecha_vencimiento[strcspn(nuevo.fecha_vencimiento, "\n")] = 0;
    
    fprintf(archivo, "%s|%.2f|%.2f|%s|%s\n",
            nuevo.tipo_alimento,
            nuevo.stock_kg,
            nuevo.precio_kg,
            nuevo.fecha_compra,
            nuevo.fecha_vencimiento);
    
    fclose(archivo);
    
    printf("✅ Alimento agregado al inventario exitosamente!\n");
}

void mostrar_inventario() {
    FILE *archivo = fopen(ARCHIVO_INVENTARIO, "r");
    Inventario item;
    char linea[256];
    int contador = 0;
    float valor_total = 0;
    
    if (archivo == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }
    
    printf("\n--- INVENTARIO DE ALIMENTOS ---\n");
    printf("==================================================================================\n");
    printf("No. | Alimento           | Stock (kg) | Precio/kg | Compra    | Vencimiento | Valor\n");
    printf("==================================================================================\n");
    
    while (fgets(linea, sizeof(linea), archivo)) {
        char *token = strtok(linea, "|");
        if (token) strcpy(item.tipo_alimento, token);
        
        token = strtok(NULL, "|");
        if (token) item.stock_kg = atof(token);
        
        token = strtok(NULL, "|");
        if (token) item.precio_kg = atof(token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(item.fecha_compra, token);
        
        token = strtok(NULL, "|");
        if (token) {
            strcpy(item.fecha_vencimiento, token);
            item.fecha_vencimiento[strcspn(item.fecha_vencimiento, "\n")] = 0;
        }
        
        contador++;
        float valor = item.stock_kg * item.precio_kg;
        valor_total += valor;
        
        printf("%-3d | %-18s | %-10.2f | $%-8.2f | %-9s | %-11s | $%-5.2f\n",
               contador,
               item.tipo_alimento,
               item.stock_kg,
               item.precio_kg,
               item.fecha_compra,
               item.fecha_vencimiento,
               valor);
    }
    
    fclose(archivo);
    
    if (contador == 0) {
        printf("El inventario está vacío.\n");
    } else {
        printf("==================================================================================\n");
        printf("Total items: %d | Valor total del inventario: $%.2f\n", contador, valor_total);
    }
}

void buscar_alimento_inventario() {
    FILE *archivo = fopen(ARCHIVO_INVENTARIO, "r");
    Inventario item;
    char linea[256];
    char criterio[50];
    int encontrado = 0;
    
    if (archivo == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }
    
    printf("\n--- BUSCAR EN INVENTARIO ---\n");
    printf("Ingrese nombre del alimento a buscar: ");
    fgets(criterio, sizeof(criterio), stdin);
    criterio[strcspn(criterio, "\n")] = 0;
    
    printf("\nResultados de la búsqueda:\n");
    printf("==================================================================================\n");
    printf("No. | Alimento           | Stock (kg) | Precio/kg | Compra    | Vencimiento | Valor\n");
    printf("==================================================================================\n");
    
    int contador = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        char temp_linea[256];
        strcpy(temp_linea, linea);
        
        char *token = strtok(temp_linea, "|");
        if (token && strstr(token, criterio) != NULL) {
            // Parsear la línea completa
            token = strtok(linea, "|");
            if (token) strcpy(item.tipo_alimento, token);
            
            token = strtok(NULL, "|");
            if (token) item.stock_kg = atof(token);
            
            token = strtok(NULL, "|");
            if (token) item.precio_kg = atof(token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(item.fecha_compra, token);
            
            token = strtok(NULL, "|");
            if (token) {
                strcpy(item.fecha_vencimiento, token);
                item.fecha_vencimiento[strcspn(item.fecha_vencimiento, "\n")] = 0;
            }
            
            contador++;
            encontrado = 1;
            float valor = item.stock_kg * item.precio_kg;
            
            printf("%-3d | %-18s | %-10.2f | $%-8.2f | %-9s | %-11s | $%-5.2f\n",
                   contador,
                   item.tipo_alimento,
                   item.stock_kg,
                   item.precio_kg,
                   item.fecha_compra,
                   item.fecha_vencimiento,
                   valor);
        }
    }
    
    fclose(archivo);
    
    if (!encontrado) {
        printf("No se encontraron alimentos con el nombre '%s'.\n", criterio);
    } else {
        printf("==================================================================================\n");
        printf("Se encontraron %d alimento(s).\n", contador);
    }
}

void actualizar_stock() {
    FILE *archivo = fopen(ARCHIVO_INVENTARIO, "r");
    FILE *temp = fopen("temp_inventario.txt", "w");
    Inventario inventario[MAX_REGISTROS];
    char linea[256];
    int contador = 0;
    int indice_actualizar;
    float nuevo_stock;
    
    if (archivo == NULL) {
        printf("El inventario está vacío.\n");
        return;
    }
    
    // Cargar todo el inventario
    while (fgets(linea, sizeof(linea), archivo) && contador < MAX_REGISTROS) {
        char *token = strtok(linea, "|");
        if (token) strcpy(inventario[contador].tipo_alimento, token);
        
        token = strtok(NULL, "|");
        if (token) inventario[contador].stock_kg = atof(token);
        
        token = strtok(NULL, "|");
        if (token) inventario[contador].precio_kg = atof(token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(inventario[contador].fecha_compra, token);
        
        token = strtok(NULL, "|");
        if (token) {
            strcpy(inventario[contador].fecha_vencimiento, token);
            inventario[contador].fecha_vencimiento[strcspn(inventario[contador].fecha_vencimiento, "\n")] = 0;
        }
        contador++;
    }
    fclose(archivo);
    
    if (contador == 0) {
        printf("No hay items en el inventario.\n");
        fclose(temp);
        remove("temp_inventario.txt");
        return;
    }
    
    // Mostrar inventario para seleccionar
    printf("\n--- ACTUALIZAR STOCK ---\n");
    mostrar_inventario();
    
    printf("Ingrese el número del item a actualizar (0 para cancelar): ");
    scanf("%d", &indice_actualizar);
    
    if (indice_actualizar == 0 || indice_actualizar > contador) {
        printf("Operación cancelada.\n");
        fclose(temp);
        remove("temp_inventario.txt");
        return;
    }
    
    printf("Nuevo stock para '%s' (kg): ", inventario[indice_actualizar-1].tipo_alimento);
    scanf("%f", &nuevo_stock);
    
    // Actualizar el stock
    inventario[indice_actualizar-1].stock_kg = nuevo_stock;
    
    // Guardar todo el inventario actualizado
    archivo = fopen(ARCHIVO_INVENTARIO, "w");
    for (int i = 0; i < contador; i++) {
        fprintf(archivo, "%s|%.2f|%.2f|%s|%s\n",
                inventario[i].tipo_alimento,
                inventario[i].stock_kg,
                inventario[i].precio_kg,
                inventario[i].fecha_compra,
                inventario[i].fecha_vencimiento);
    }
    fclose(archivo);
    
    printf("✅ Stock actualizado exitosamente!\n");
    fclose(temp);
    remove("temp_inventario.txt");
}

void calcular_consumo_promedio() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    char linea[256];
    int total_gallinas = 0, total_dias = 0;
    float total_kg = 0, total_costo = 0;
    
    if (archivo == NULL) {
        printf("No hay datos para calcular.\n");
        return;
    }
    
    while (fgets(linea, sizeof(linea), archivo)) {
        char *token = strtok(linea, "|");
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        if (token) total_kg += atof(token);
        token = strtok(NULL, "|");
        if (token) total_gallinas += atoi(token);
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        token = strtok(NULL, "|");
        if (token) total_costo += atof(token);
        total_dias++;
    }
    
    fclose(archivo);
    
    if (total_dias > 0) {
        printf("\n--- CONSUMO PROMEDIO ---\n");
        printf("📊 Días analizados: %d\n", total_dias);
        printf("🐔 Gallinas totales: %d\n", total_gallinas);
        printf("🌾 Consumo total: %.2f kg\n", total_kg);
        printf("💰 Costo total: $%.2f\n", total_costo);
        printf("📈 Consumo promedio diario: %.2f kg\n", total_kg / total_dias);
        printf("💵 Costo promedio diario: $%.2f\n", total_costo / total_dias);
        
        if (total_gallinas > 0) {
            printf("🥚 Consumo por gallina/día: %.3f kg\n", total_kg / total_gallinas);
            printf("🏷️  Costo por gallina/día: $%.3f\n", total_costo / total_gallinas);
        }
    } else {
        printf("No hay suficientes datos para calcular.\n");
    }
}

void recomendar_alimentacion() {
    printf("\n--- RECOMENDACIONES DE ALIMENTACIÓN ---\n");
    printf("🐔 POLLITAS (0-8 semanas):\n");
    printf("   • Iniciador: 20-22%% proteína\n");
    printf("   • Consumo: 1.8-2.0 kg por ave hasta 8 semanas\n");
    printf("   • Alimento medicado con coccidiostato\n");
    printf("   • Frecuencia: 4-6 veces al día\n\n");
    
    printf("🐔 GALLINAS JÓVENES (8-18 semanas):\n");
    printf("   • Crecimiento: 16-18%% proteína\n");
    printf("   • Consumo: 5.5-6.5 kg por ave hasta 18 semanas\n");
    printf("   • Calcio: 1.0-1.2%%\n");
    printf("   • Control de peso semanal\n\n");
    
    printf("🥚 GALLINAS EN POSTURA (18+ semanas):\n");
    printf("   • Postura: 16-18%% proteína\n");
    printf("   • Consumo: 100-120 g/gallina/día\n");
    printf("   • Calcio: 3.5-4.5%% para cáscaras fuertes\n");
    printf("   • Fósforo: 0.4-0.5%%\n\n");
    
    printf("🍗 ENGORDE:\n");
    printf("   • Finalizador: 14-16%% proteína\n");
    printf("   • Consumo: 120-150 g/gallina/día\n");
    printf("   • Alta energía para ganancia de peso\n");
    printf("   • Evitar exceso de grasa\n");
}

void eliminar_registro() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    FILE *temp = fopen("temp.txt", "w");
    Alimentacion registros[MAX_REGISTROS];
    char linea[256];
    int contador = 0;
    int indice_eliminar;
    
    if (archivo == NULL) {
        printf("No hay registros disponibles.\n");
        return;
    }
    
    // Cargar todos los registros
    while (fgets(linea, sizeof(linea), archivo) && contador < MAX_REGISTROS) {
        char *token = strtok(linea, "|");
        if (token) strcpy(registros[contador].fecha, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registros[contador].tipo_alimento, token);
        
        token = strtok(NULL, "|");
        if (token) registros[contador].cantidad_kg = atof(token);
        
        token = strtok(NULL, "|");
        if (token) registros[contador].numero_gallinas = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registros[contador].etapa_produccion, token);
        
        token = strtok(NULL, "|");
        if (token) strcpy(registros[contador].proveedor, token);
        
        token = strtok(NULL, "|");
        if (token) registros[contador].costo = atof(token);
        
        token = strtok(NULL, "|");
        if (token) {
            strcpy(registros[contador].observaciones, token);
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
    
    printf("Ingrese el número del registro a eliminar (0 para cancelar): ");
    scanf("%d", &indice_eliminar);
    
    if (indice_eliminar == 0 || indice_eliminar > contador) {
        printf("Operación cancelada.\n");
        fclose(temp);
        remove("temp.txt");
        return;
    }
    
    // Guardar todos los registros excepto el eliminado
    archivo = fopen(ARCHIVO_DATOS, "w");
    for (int i = 0; i < contador; i++) {
        if (i != indice_eliminar - 1) {
            fprintf(archivo, "%s|%s|%.2f|%d|%s|%s|%.2f|%s\n",
                    registros[i].fecha,
                    registros[i].tipo_alimento,
                    registros[i].cantidad_kg,
                    registros[i].numero_gallinas,
                    registros[i].etapa_produccion,
                    registros[i].proveedor,
                    registros[i].costo,
                    registros[i].observaciones);
        }
    }
    fclose(archivo);
    
    printf("✅ Registro eliminado exitosamente!\n");
    fclose(temp);
    remove("temp.txt");
}

void obtener_fecha_actual(char *fecha) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(fecha, 11, "%Y-%m-%d", tm_info);
}