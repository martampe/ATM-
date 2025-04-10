#include "ingresarInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include "sistem.h"
#include "bd.h"
#include "usuarioHandler.h"
void mostrarIngresarInterfaz(void){
    char buffer[10];
    int cantidad;
    int operacionCorrecta = -1;
    do{
        clearScreen();

        printf("<<Ingresar Dinero>>\n");
        printf("*-------------*\n");
        printf("| Saldo: %2.f |\n", getUsuarioActual()->cuentaActual.saldo);
        printf("*-------------*\n");
        printf("[0] Volver al menu principal\n"
               "Introduzca la cantidad a ingresar ('0' para cancelar): ");
        fgets(buffer, sizeof(buffer), stdin);
        cantidad = leerInteger(buffer);
        
        if (cantidad == 0)
        {
            printf("Seleccionado volver al menu principal\n");
            operacionCorrecta = -1;
            break;
        } else if(cantidad > 0){

            int confirmacion;
            char bufferConfimacion[3];
            do 
            {   
                clearScreen();
                printf("Ingreso de %d euros:\n"
                    "[1] Confirmar operacion\n"
                    "[2] Cancelar transaccion\n"
                    "Seleccionar operacion: ", cantidad);
                    
                fgets(bufferConfimacion, sizeof(bufferConfimacion), stdin);
                confirmacion = leerInteger(bufferConfimacion);
                    
                    
                switch (confirmacion)
                {
                    case 1:
                        clearScreen();
                        operacionCorrecta = ingresarDinero(getUsuarioActual()->cuentaActual.numCuenta, cantidad);

                        if (operacionCorrecta != 0)
                        {
                            printf("Error: Ha surgido un error en la retirada de dinero\n");
                            break;
                        }
                        getUsuarioActual()->cuentaActual.saldo += cantidad;
                        printf("Ingreso de %d euros realizado correctamente\n", cantidad);
                        printf("Persiona enter para continuar...");
                        limpiarBuffer();
                        break;
                    case 2:
                        operacionCorrecta = -1;
                        clearScreen();
                        printf("Operacion cancelada\n");
                        printf("Persiona enter para continuar...");
                        limpiarBuffer();
                        return;
                        break;
                    default:
                        operacionCorrecta = -1;
                        clearScreen();
                        printf("Opción no válida. Inténtelo de nuevo.\n");
                        printf("Persiona enter para continuar...");
                        limpiarBuffer();
                        break;
                }
                    

                } while (confirmacion != 1 && confirmacion != 2);
    
        } else {
            clearScreen();
            printf("No se puede ingresar una cantidad negativa de dinero\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }
        

    } while (operacionCorrecta != 0);
}