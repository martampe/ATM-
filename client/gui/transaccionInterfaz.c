#include "transaccionInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include <string.h>
#include "sistem.h"
#include "bd.h"
#include "usuarioHandler.h"


void mostrarTransaccionInterfaz(void){

    char bufferSeleccion[3];
    char bufferIBAN[30];
    char bufferCantidad[10];
    int cantidad;
    int operacionCorrecta = -1;
    int seleccion;

    do{
        clearScreen();

        printf("<<Transaccion>>\n");
        printf("*-------------*\n");
        printf("| Saldo: %2.f |\n", getUsuarioActual()->cuentaActual.saldo);
        printf("*-------------*\n");
        printf("[0] Volver al menu pricipal\n"
            "[1] Realizar transaccion\n"
            "Seleccionar operacion: ");
        
        fgets(bufferSeleccion, sizeof(bufferSeleccion), stdin);

        seleccion = leerInteger(bufferSeleccion);

        switch (seleccion)
        {
        case 1:
            clearScreen();
            printf("Realizando transaccion\n");

            
            int mismoIBAN = 1;
            do
            {
                if (mismoIBAN == 0)
                {
                    clearScreen();
                    printf("No se puede realizar una transaccion a tu misma cuenta\n");
                    printf("Presione enter para continuar...");
                    limpiarBuffer();
                } 
                clearScreen();
                printf("Introduce el ISBN destino: ");
                
            } while (((leerEntradaSegura(bufferIBAN, sizeof(bufferIBAN))) != 1) || (mismoIBAN = strcmp(bufferIBAN, getUsuarioActual()->cuentaActual.numCuenta)) == 0);
            

            
            printf("Introduce la cantidad a transferir: ");
            fgets(bufferCantidad, sizeof(bufferCantidad), stdin);

            cantidad = leerInteger(bufferCantidad);
            if (cantidad > 0)
            {
                operacionCorrecta = realizarTransferencia(getUsuarioActual()->cuentaActual.numCuenta, bufferIBAN, cantidad);
                if (operacionCorrecta != 0)
                {
                    clearScreen();
                    printf("Ha habido un problema al realizar la transaccion\n");
                    printf("Presiona enter para continuar...");
                    limpiarBuffer();
                    return;
                }
                getUsuarioActual()->cuentaActual.saldo -= cantidad;
                clearScreen();
                printf("Operacion realizada a ISBN: %s de %d euros\n", bufferIBAN, cantidad);
                printf("Presiona enter para continuar...");
                limpiarBuffer();
            } else {
                clearScreen();
                printf("Error: No se ha podido realizar la transaccion\n");
                printf("Persiona enter para continuar...");
                limpiarBuffer();
            }
            break;
        case 0:
            break;
        
        default:
            clearScreen();
            printf("Opción no válida. Inténtelo de nuevo.\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            break;
        }
      

        
        

    } while (operacionCorrecta != 0 && seleccion != 0);
}