#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTOS 100
#define ARCHIVO_DATOS "inventario.txt"

// Estructura para los productos
typedef struct {
    int id;
    char nombre[50];
    char categoria[30];
    float precio;
    int cantidad;
} Producto;

// Prototipos de funciones
void mostrarMenu();
void agregarProducto();
void listarProductos();
void buscarProducto();
void modificarProducto();
void eliminarProducto();
void cargarDatos();
void guardarDatos();
void limpiarBuffer();

// Variables globales
Producto inventario[MAX_PRODUCTOS];
int totalProductos = 0;

int main() {
    int opcion;
    
    cargarDatos();
    
    do {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        
        switch(opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                listarProductos();
                break;
            case 3:
                buscarProducto();
                break;
            case 4:
                modificarProducto();
                break;
            case 5:
                eliminarProducto();
                break;
            case 6:
                printf("\n¡Guardando datos y saliendo del sistema!\n");
                guardarDatos();
                break;
            default:
                printf("\n❌ Opción inválida. Intente nuevamente.\n");
        }
        
        if(opcion != 6) {
            printf("\nPresione ENTER para continuar...");
            getchar();
        }
        
    } while(opcion != 6);
    
    return 0;
}

void mostrarMenu() {
    system("clear"); // Para Linux
    printf("╔════════════════════════════════════════╗\n");
    printf("║   SISTEMA DE INVENTARIO DE PRODUCTOS  ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("  1. Agregar producto\n");
    printf("  2. Listar productos\n");
    printf("  3. Buscar producto\n");
    printf("  4. Modificar producto\n");
    printf("  5. Eliminar producto\n");
    printf("  6. Salir\n\n");
}

void agregarProducto() {
    if(totalProductos >= MAX_PRODUCTOS) {
        printf("\n❌ El inventario está lleno.\n");
        return;
    }
    
    Producto nuevo;
    
    printf("\n═══ AGREGAR NUEVO PRODUCTO ═══\n\n");
    
    nuevo.id = totalProductos + 1;
    
    printf("Nombre del producto: ");
    fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;
    
    printf("Categoría: ");
    fgets(nuevo.categoria, sizeof(nuevo.categoria), stdin);
    nuevo.categoria[strcspn(nuevo.categoria, "\n")] = 0;
    
    printf("Precio: $");
    scanf("%f", &nuevo.precio);
    
    printf("Cantidad en stock: ");
    scanf("%d", &nuevo.cantidad);
    limpiarBuffer();
    
    inventario[totalProductos] = nuevo;
    totalProductos++;
    
    guardarDatos();
    
    printf("\n✓ Producto agregado exitosamente.\n");
}

void listarProductos() {
    printf("\n═══ LISTADO DE PRODUCTOS ═══\n\n");
    
    if(totalProductos == 0) {
        printf("No hay productos en el inventario.\n");
        return;
    }
    
    printf("%-5s %-25s %-20s %-12s %-10s\n", "ID", "NOMBRE", "CATEGORÍA", "PRECIO", "STOCK");
    printf("────────────────────────────────────────────────────────────────────────\n");
    
    for(int i = 0; i < totalProductos; i++) {
        printf("%-5d %-25s %-20s $%-11.2f %-10d\n",
               inventario[i].id,
               inventario[i].nombre,
               inventario[i].categoria,
               inventario[i].precio,
               inventario[i].cantidad);
    }
    
    printf("\nTotal de productos: %d\n", totalProductos);
}

void buscarProducto() {
    char busqueda[50];
    int encontrado = 0;
    
    printf("\n═══ BUSCAR PRODUCTO ═══\n\n");
    printf("Ingrese el nombre del producto: ");
    fgets(busqueda, sizeof(busqueda), stdin);
    busqueda[strcspn(busqueda, "\n")] = 0;
    
    printf("\n%-5s %-25s %-20s %-12s %-10s\n", "ID", "NOMBRE", "CATEGORÍA", "PRECIO", "STOCK");
    printf("────────────────────────────────────────────────────────────────────────\n");
    
    for(int i = 0; i < totalProductos; i++) {
        if(strstr(inventario[i].nombre, busqueda) != NULL) {
            printf("%-5d %-25s %-20s $%-11.2f %-10d\n",
                   inventario[i].id,
                   inventario[i].nombre,
                   inventario[i].categoria,
                   inventario[i].precio,
                   inventario[i].cantidad);
            encontrado = 1;
        }
    }
    
    if(!encontrado) {
        printf("No se encontraron productos.\n");
    }
}

void modificarProducto() {
    int id, indice = -1;
    
    printf("\n═══ MODIFICAR PRODUCTO ═══\n\n");
    printf("Ingrese el ID del producto: ");
    scanf("%d", &id);
    limpiarBuffer();
    
    for(int i = 0; i < totalProductos; i++) {
        if(inventario[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if(indice == -1) {
        printf("\n❌ Producto no encontrado.\n");
        return;
    }
    
    printf("\nProducto actual:\n");
    printf("Nombre: %s\n", inventario[indice].nombre);
    printf("Categoría: %s\n", inventario[indice].categoria);
    printf("Precio: $%.2f\n", inventario[indice].precio);
    printf("Stock: %d\n\n", inventario[indice].cantidad);
    
    printf("Nuevo nombre (Enter para mantener): ");
    char temp[50];
    fgets(temp, sizeof(temp), stdin);
    if(temp[0] != '\n') {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(inventario[indice].nombre, temp);
    }
    
    printf("Nueva categoría (Enter para mantener): ");
    fgets(temp, sizeof(temp), stdin);
    if(temp[0] != '\n') {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(inventario[indice].categoria, temp);
    }
    
    printf("Nuevo precio (0 para mantener): $");
    float precio;
    scanf("%f", &precio);
    if(precio > 0) {
        inventario[indice].precio = precio;
    }
    
    printf("Nueva cantidad (0 para mantener): ");
    int cantidad;
    scanf("%d", &cantidad);
    if(cantidad > 0) {
        inventario[indice].cantidad = cantidad;
    }
    limpiarBuffer();
    
    guardarDatos();
    
    printf("\n✓ Producto modificado exitosamente.\n");
}

void eliminarProducto() {
    int id, indice = -1;
    
    printf("\n═══ ELIMINAR PRODUCTO ═══\n\n");
    printf("Ingrese el ID del producto: ");
    scanf("%d", &id);
    limpiarBuffer();
    
    for(int i = 0; i < totalProductos; i++) {
        if(inventario[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if(indice == -1) {
        printf("\n❌ Producto no encontrado.\n");
        return;
    }
    
    printf("\n¿Está seguro de eliminar '%s'? (s/n): ", inventario[indice].nombre);
    char confirmar;
    scanf("%c", &confirmar);
    limpiarBuffer();
    
    if(confirmar == 's' || confirmar == 'S') {
        for(int i = indice; i < totalProductos - 1; i++) {
            inventario[i] = inventario[i + 1];
        }
        totalProductos--;
        
        // Reorganizar IDs
        for(int i = 0; i < totalProductos; i++) {
            inventario[i].id = i + 1;
        }
        
        guardarDatos();
        printf("\n✓ Producto eliminado exitosamente.\n");
    } else {
        printf("\nOperación cancelada.\n");
    }
}

void cargarDatos() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    
    if(archivo == NULL) {
        return;
    }
    
    totalProductos = 0;
    while(fscanf(archivo, "%d|%49[^|]|%29[^|]|%f|%d\n",
                 &inventario[totalProductos].id,
                 inventario[totalProductos].nombre,
                 inventario[totalProductos].categoria,
                 &inventario[totalProductos].precio,
                 &inventario[totalProductos].cantidad) == 5) {
        totalProductos++;
        if(totalProductos >= MAX_PRODUCTOS) break;
    }
    
    fclose(archivo);
}

void guardarDatos() {
    FILE *archivo = fopen(ARCHIVO_DATOS, "w");
    
    if(archivo == NULL) {
        printf("\n❌ Error al guardar los datos.\n");
        return;
    }
    
    for(int i = 0; i < totalProductos; i++) {
        fprintf(archivo, "%d|%s|%s|%.2f|%d\n",
                inventario[i].id,
                inventario[i].nombre,
                inventario[i].categoria,
                inventario[i].precio,
                inventario[i].cantidad);
    }
    
    fclose(archivo);
}

void limpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
