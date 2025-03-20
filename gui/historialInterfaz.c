#include "historialInterfaz.h"
#include "detallesInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>

void mostrarInterfazHistorial(void){
    char buffer[3];
    int seleccion;
    do{
        printf("Historial de Transacciones\n");
        //printear transacciones
        printf("[1] Ver detalles de [n] de transaccion\n"
            "[2] Volver al menu principal\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 1:

            printf("Seleccionado mostrar detalles transaccion\n");
            mostrarDetallesInterfaz();
            
            break;
        case 2:
            printf("Seleccionado volver al menu principal\n");
            break;

        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
        }

    } while (seleccion != 2 || seleccion == -1);

    
}