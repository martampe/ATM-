#include "cuentasInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include "sistem.h"

void mostrarDetallesCuentaInterfaz(int cuenta){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Detalles de Cuenta <<%d>>\n", cuenta);
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
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }

    } while (seleccion != 0);
}

void mostrarCuentasInterfaz(void){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Cuentas\n");
        //printear cuentas
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
            mostrarDetallesCuentaInterfaz(seleccion); //pasar id de la cuenta
        } else {
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }
        

    } while (seleccion != 0);
}