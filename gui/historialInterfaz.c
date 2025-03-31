#include "historialInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include "sistem.h"

void mostrarHistorialInterfaz(void){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Historial de Transacciones\n");
        //printear cuentas
        printf("[0] Volver al menu principal\n"
            "[1] Mostrar más transacciones\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 0:
            printf("Seleccionado volver al menu principal\n");
            
            break;
        case 1:
            printf("Seleccionado mostrar más transacciones\n");
            break;

        default:
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }

    } while (seleccion != 0);

    
}