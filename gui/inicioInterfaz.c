#include <stdio.h>
#include <stdlib.h>
#include "inicioInterfaz.h"
#include "leerConsola.h"
#include "historialInterfaz.h"
#include "retirarInterfaz.h"

void mostrarInterfazInicio(void){

    //historial
    //retirar
    //ingresar
    //transaccion
    //cuentas
    //configuracion

    char buffer[3];
    int seleccion;
    do{
        printf("Menu principal\n");
        printf("[1] Mostrar historial\n"
            "[2] Retirar dinero\n"
            "[3] Ingresar dinero\n"
            "[4] Realizar transaccion\n"
            "[5] Mostrar cuentas\n"
            "[6] Configuracion\n"
            "[7] Salir\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 1:

            printf("Seleccionado mostrar historial\n");
            mostrarInterfazHistorial();
            break;
        case 2:
            printf("Seleccionado retirar dinero\n");
            mostrarRetirarInterfaz();
            break;
        case 3:
            printf("Seleccionado ingresar dinero\n");
            break;
        case 4:
            printf("Seleccionado realizar transaccion\n");
            break;
        case 5:
            printf("Seleccionado mostrar cuentas\n");
            break;
        case 6:
            printf("Seleccionado configuracion\n");
            break;
        case 7:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
        }

    } while (seleccion != 7 || seleccion == -1);

    exit(0);
}