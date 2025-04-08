#include "historialInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include <string.h>
#include "sistem.h"

void mostrarHistorialInterfaz(void) {
    char buffer[3];
    int seleccion;

    do {
        clearScreen();
        printf("Historial de Transacciones\n");
        printf("[0] Volver al menu principal\n");
        printf("[1] Mostrar mis transacciones\n");
        printf("Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);

        switch (seleccion) {
            case 0:
                printf("Seleccionado volver al menu principal\n");
                break;

            case 1: {
                printf("Seleccionado mostrar mis transacciones\n");

                char numCuenta[25];
                printf("Introduce tu numero de cuenta: ");
                fgets(numCuenta, sizeof(numCuenta), stdin);

                numCuenta[strcspn(numCuenta, "\n")] = '\0'; 

                if (cargarCuenta(numCuenta)) {
                    mostrarTransaccionesCuenta(numCuenta);
                } else {
                    printf("Cuenta no encontrada.\n");
                }
                limpiarBuffer();
                break;
            }

            default:
                clearScreen();
                printf("Opcion no valida. Intentelo de nuevo\n");
                printf("Presiona enter para continuar...");
                limpiarBuffer(); 
        }

    } while (seleccion != 0);  
    
}
