#include "retirarInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
void mostrarRetirarInterfaz(void){

    char buffer[10];
    int cantidad;
    do{
        printf("Retirar Dinero\n");
        printf("[0] Volver al menu principal\n"
            "Introduzca la cantidad a retirar ('0' para cancelar): ");
        fgets(buffer, sizeof(buffer), stdin);
        cantidad = leerInteger(buffer);

        switch (cantidad)
        {
        case 0:
            printf("Seleccionado volver al menu principal\n");
        default:
            
            if (cantidad > 0)
            {
                int confirmacion;
                char bufferConfimacion[3];
                do 
                {   
                    printf("[1] Confirmar operacion\n"
                        "[2] Cancelar transaccion\n"
                        "Seleccionar operacion: ");
                    
                    fgets(bufferConfimacion, sizeof(bufferConfimacion), stdin);
                    confirmacion = leerInteger(bufferConfimacion);
                    
                    
                    switch (confirmacion)
                    {
                    case 1:
                        printf("Retirando %d euros\n", cantidad);
                        break;
                    case 2:
                        printf("Operacion cancelada\n");
                        break;
                    default:
                        printf("Opción no válida. Inténtelo de nuevo.\n");
                        break;
                    }
                    

                } while (confirmacion != 1 && confirmacion != 2);
            } else {
                printf("Solo se puede retirar una cantidad positiva de dinero\n");
            }
            
            
            
            
            
            
        }

    } while (cantidad != 0 && cantidad < 0);
}