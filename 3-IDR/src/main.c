#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int led = 0;       // 0 = apagado, 1 = encendido
    char input;

    printf("Simulación: Presione 'b' para presionar el botón PC13, 'q' para salir.\n");

    while (1) {
        printf("LED PA5: %s\n", led ? "ENCENDIDO" : "APAGADO");
        printf("Presione tecla: ");
        input = getchar();

        // Limpiar buffer
        while(getchar() != '\n');

        if (input == 'q') {
            printf("Saliendo...\n");
            break;
        } else if (input == 'b') {
            led = !led;  // Cambiar estado del LED
            printf("Botón presionado! LED ahora está %s\n", led ? "ENCENDIDO" : "APAGADO");
        } else {
            printf("Tecla no válida. Use 'b' o 'q'\n");
        }
        printf("\n");
    }

    return 0;
}
