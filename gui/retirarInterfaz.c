#include "retirarInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include "sistem.h"
#include "bd.h"
#include "usuarioHandler.h"

void mostrarRetirarInterfaz(void){

    char buffer[10];
    int cantidad;
    int operacionCorrecta = -1;
    do{
        clearScreen();

        printf("<<Retirar Dinero>>\n");
        printf("*-------------*\n");
        printf("| Saldo: %2.f |\n", getUsuarioActual()->cuentaActual.saldo);
        printf("*-------------*\n");
        printf("[0] Volver al menu principal\n"
            "Introduzca la cantidad a retirar ('0' para cancelar): ");
        fgets(buffer, sizeof(buffer), stdin);
        cantidad = leerInteger(buffer);
        
        if (cantidad == 0)
        {
            operacionCorrecta = -1;
            break;
        } else if (cantidad > 0){

            int confirmacion;
            char bufferConfimacion[3];
            do 
            {   
                clearScreen();

                printf("Retiro de %d euros:\n"
                    "[1] Confirmar operacion\n"
                    "[2] Cancelar transaccion\n"
                    "Seleccionar operacion: ", cantidad);
                
                fgets(bufferConfimacion, sizeof(bufferConfimacion), stdin);
                confirmacion = leerInteger(bufferConfimacion);
                
                
                switch (confirmacion)
                {
                case 1:
                    clearScreen();
                    operacionCorrecta = retirarDinero(getUsuarioActual()->cuentaActual.numCuenta, cantidad);
                    if (operacionCorrecta != 0)
                    {
                        printf("Error en la retirada de dinero\n");
                    }
                    
                    printf("Retirando %d euros\n", cantidad);
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    break;
                case 2:
                    clearScreen();
                    printf("Operacion cancelada\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    return;
                    break;
                default:
                    clearScreen();
                    printf("Opción no válida. Inténtelo de nuevo.\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }
                

            } while (confirmacion != 1 && confirmacion != 2);
        } else {
            clearScreen();
            printf("No se puede retirar una cantidad negativa de dinero\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }
         
            

    } while (operacionCorrecta != 0);
}