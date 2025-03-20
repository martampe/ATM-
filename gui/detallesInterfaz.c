#include "detallesInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>

void mostrarDetallesInterfaz(void){

    char buffer[3];
    int seleccion;
    do{
        printf("Detalles de Transaccion\n");
        //printear transacciones
        printf("[1] Volver al historial de transaccion\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 1:

            printf("Seleccionado volver al historial de transaccion\n");
            
            break;

        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
        }

    } while (seleccion != 1 || seleccion == -1);
}