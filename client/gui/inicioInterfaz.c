#include <stdio.h>
#include <stdlib.h>
#include "inicioInterfaz.h"
#include "leerConsola.h"
#include "historialInterfaz.h"
#include "retirarInterfaz.h"
#include "ingresarInterfaz.h"
#include "transaccionInterfaz.h"
#include "cuentasInterfaz.h"
#include "configuracionInterfaz.h"
#include "sistem.h"
#include "usuarioHandler.h"
#include "bd.h"
void mostrarInicioInterfaz(void){

  
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("<<Menu principal>>\n");
        printf("*-------------*\n");
        printf("| Saldo: %2.f |\n", getUsuarioActual()->cuentaActual.saldo);
        printf("*-------------*\n");
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
            mostrarHistorialInterfaz();
            break;
        case 2:
            printf("Seleccionado retirar dinero\n");
            mostrarRetirarInterfaz();
            break;
        case 3:
            printf("Seleccionado ingresar dinero\n");
            mostrarIngresarInterfaz();
            break;
        case 4:
            printf("Seleccionado realizar transaccion\n");
            mostrarTransaccionInterfaz();
            break;
        case 5:
            printf("Seleccionado mostrar cuentas\n");
            mostrarCuentasInterfaz();
            break;
        case 6:
            printf("Seleccionado configuracion\n");
            mostrarConfiguracionInterfaz();
            break;
        case 7:
            printf("Saliendo del programa...\n");
            liberarMemoria();
            break;
        default:
            clearScreen();
            printf("Opción no válida. Inténtelo de nuevo.\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }

    } while (seleccion != 7 || seleccion == -1);

    exit(0);
}