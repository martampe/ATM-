#include "retirarInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include "sistem.h"

void mostrarRetirarInterfaz(void){

    char buffer[10];
    int cantidad;
    do{
        clearScreen();

        printf("Retirar Dinero\n");
        printf("[0] Volver al menu principal\n"
            "Introduzca la cantidad a retirar ('0' para cancelar): ");
        fgets(buffer, sizeof(buffer), stdin);
        cantidad = leerInteger(buffer);

        switch (cantidad)
        {
        case 0:
            printf("Seleccionado volver al menu principal\n");
            break;
        default:
            
            if (cantidad > 0)
            {
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
                        printf("Retirando %d euros\n", cantidad);
                        printf("Persiona enter para continuar...");
                        limpiarBuffer();
                        break;
                    case 2:
                        clearScreen();
                        printf("Operacion cancelada\n");
                        printf("Persiona enter para continuar...");
                        limpiarBuffer();
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
            
            
            
            
            
            
        }

    } while (cantidad != 0 && cantidad < 0);
}