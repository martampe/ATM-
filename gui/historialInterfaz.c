#include "historialInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include <string.h>
#include "sistem.h"
#include "usuarioHandler.h"

void imprimirTransaccion(Transaccion *transacccion, int num){

    printf("");

}


void mostrarTransacciones(){
    clearScreen();
    printf("Transacciones: \n");
    for (int i = 0; i < getUsuarioActual()->numeroTransacciones; i++)
    {
        imprimirTransaccion(getUsuarioActual()->transaciones[i], i);
    }
    
}

void mostrarHistorialInterfaz(void) {
    char buffer[3];
    int seleccion;

    do {
        clearScreen();
        printf("Historial de Transacciones\n");
        printf("[0] Volver al menu principal\n");
        printf("[1] Mostrar transacciones bancarias\n");
        printf("[2] Mostrar operaciones de tarjeta\n");
        printf("Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);

        switch (seleccion) {
            case 0:
                printf("Seleccionado volver al menu principal\n");
                break;

            case 1: 
                printf("Seleccionado mostrar mis transacciones\n");
                mostrarTransacciones();
                limpiarBuffer();
                break;
            
            case 2:
                printf("Seleccionado mostrar operaciones de tarjeta\n");
                mostrarTransacciones();
                limpiarBuffer();
            break;

            default:
                clearScreen();
                printf("Opcion no valida. Intentelo de nuevo\n");
                printf("Presiona enter para continuar...");
                limpiarBuffer(); 
        }

    } while (seleccion != 0);  
    
}
