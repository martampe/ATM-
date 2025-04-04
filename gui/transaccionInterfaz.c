#include "transaccionInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include <string.h>
#include "sistem.h"
#include "bd.h"
#include "usuarioHandler.h"


void mostrarTransaccionInterfaz(void){

    char bufferSeleccion[3];
    char bufferISBN[30];
    char bufferCantidad[10];
    int cantidad;
    int operacionCorrecta = -1;
    int seleccion;

    do{
        clearScreen();

        printf("Transaccion\n");
        printf("[0] Volver al menu pricipal\n"
            "[1] Realizar transaccion\n"
            "Seleccionar operacion: ");
        
        fgets(bufferSeleccion, sizeof(bufferSeleccion), stdin);

        seleccion = leerInteger(bufferSeleccion);

        switch (seleccion)
        {
        case 1:
            clearScreen();
            printf("Realizando ransaccion\n");

            printf("Introduce el ISBN destino: ");
            fgets(bufferISBN, sizeof(bufferISBN), stdin);

            int rt = eliminarSaltoLinea(bufferISBN);

            if(rt != 0){
                clearScreen();
                printf("Error: Error al procesar el ISBN\n");
                printf("Persiona enter para continuar...");
                limpiarBuffer();
            }


            printf("Introduce la cantidad a transferir: ");
            fgets(bufferCantidad, sizeof(bufferCantidad), stdin);


            cantidad = leerInteger(bufferCantidad);
            if (cantidad > 0)
            {
                operacionCorrecta = realizarTransferencia(getUsuarioActual()->cuentaActual->numCuenta, bufferISBN, cantidad);
                clearScreen();
                printf("Operacion realizada a ISBN: %s de %d\n", bufferISBN, cantidad);
                printf("Persiona enter para continuar...");
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