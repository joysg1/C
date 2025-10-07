#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

// Códigos de color ANSI
#define ROJO "\033[1;31m"
#define ROJO_SUAVE "\033[0;31m"
#define RESET "\033[0m"

void dibujarCorazonAnimado(int n, int desplazamiento, int ciclo) {
    int i, j;
    
    // Limpiar pantalla
    printf("\033[2J\033[H");
    
    printf(ROJO "❤️  Corazón rojo en movimiento  ❤️\n\n" RESET);
    
    // Efecto de latido cambiando el color ligeramente
    const char* color = (ciclo % 4 < 2) ? ROJO : ROJO_SUAVE;
    
    // Parte superior del corazón
    for (i = n/2; i <= n; i += 2) {
        // Espacios para el desplazamiento
        for (int k = 0; k < desplazamiento; k++) {
            printf(" ");
        }
        
        // Espacios para centrar
        for (j = 1; j < n - i; j += 2) {
            printf(" ");
        }
        
        // Parte izquierda del corazón
        printf("%s", color);
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf(RESET);
        
        // Espacio del medio
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }
        
        // Parte derecha del corazón
        printf("%s", color);
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf(RESET);
        
        printf("\n");
    }
    
    // Parte inferior del corazón
    for (i = n; i >= 1; i--) {
        // Espacios para el desplazamiento
        for (int k = 0; k < desplazamiento; k++) {
            printf(" ");
        }
        
        // Espacios para centrar
        for (j = i; j < n; j++) {
            printf(" ");
        }
        
        // Caracteres del corazón
        printf("%s", color);
        for (j = 1; j <= (i * 2) - 1; j++) {
            printf("*");
        }
        printf(RESET);
        
        printf("\n");
    }
    
    // Información de control
    printf("\n%sDesplazamiento: %d | Velocidad: Media%s\n", ROJO, desplazamiento, RESET);
    printf("%sPresiona Ctrl+C para salir%s\n", ROJO, RESET);
}

int main() {
    int n = 10;
    int max_desplazamiento = 40;
    int velocidad = 60000; // Microsegundos
    int ciclo = 0;
    
    printf("Iniciando animación del corazón en 2 segundos...\n");
    sleep(2);
    
    // Animación continua
    while (1) {
        ciclo++;
        
        // Movimiento hacia la derecha
        for (int desplazamiento = 0; desplazamiento <= max_desplazamiento; desplazamiento++) {
            dibujarCorazonAnimado(n, desplazamiento, ciclo);
            usleep(velocidad);
        }
        
        // Movimiento hacia la izquierda
        for (int desplazamiento = max_desplazamiento; desplazamiento >= 0; desplazamiento--) {
            dibujarCorazonAnimado(n, desplazamiento, ciclo);
            usleep(velocidad);
        }
    }
    
    return 0;
}