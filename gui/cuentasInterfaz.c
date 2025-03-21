#include "cuentasInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"

void mostrarDetallesCuentaInterfaz(void){

    char buffer[3];
    int seleccion;
    do{
        printf("Detalles de Cuenta\n");
        //printear transacciones
        printf("[0] Volver al a tus cuentas\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 0:
            printf("Presionado volver a tus cuentas\n");
            break;

        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
        }

    } while (seleccion != 0);
}

void mostrarCuentasInterfaz(void){

    char buffer[3];
    int seleccion;
    do{
        printf("Detalles de Cuentas\n");
        //printear transacciones
        printf("[0] Volver al menu principal\n"
            "Introduzca la cuenta ('0' para cancelar): ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        
        if (seleccion == 0)
        {
            printf("Seleccionado volver al menu principal\n");
            return;
        } else if(seleccion > 0){
            printf("Seleccionado ver cuenta %d\n", seleccion);
            mostrarDetallesCuentaInterfaz(); //pasar id de la cuenta
        } else {
            printf("Opcion no valida. Vuelva a intentar\n");
        }
        

    } while (seleccion != 0);
}