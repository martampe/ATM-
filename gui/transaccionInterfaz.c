#include "transaccionInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include <string.h>


void mostrarTransaccionInterfaz(void){

    char bufferSeleccion[3];
    char bufferISBN[20];
    char bufferCantidad[10];
    int cantidad;
    int operacionCorrecta = -1;

    do{

        printf("Transaccion\n");
        printf("[1] Realizar transaccion\n"
            "[2] Volver al menu pricipal\n"
            "Seleccionar operacion: ");
        
        fgets(bufferSeleccion, sizeof(bufferSeleccion), stdin);

        int seleccion = leerInteger(bufferSeleccion);

        switch (seleccion)
        {
        case 1:

            printf("Introduce el ISBN destino: ");
            fgets(bufferISBN, sizeof(bufferISBN), stdin);

            if (strchr(bufferISBN, '\n') != NULL)
            {
                bufferISBN[strcspn(bufferISBN, "\n")] = '\0';
                //Comprobar ISB
            } else {
                printf("Error: Error al procesar el ISBN\n");
            }
            

            printf("Introduce la cantidad a transferir: ");
            fgets(bufferCantidad, sizeof(bufferCantidad), stdin);


            cantidad = leerInteger(bufferCantidad);
            if (cantidad > 0)
            {
                operacionCorrecta = 0; //Implementar realizar transacion
                printf("Operacion realizada a ISBN: %s de %d\n", bufferISBN, cantidad);
            } else {
                printf("Error: No se ha podido realizar la transaccion\n");
            }
            break;
        case 2:
            return;
            break;
        
        default:
            break;
        }
      

        
        

    } while (operacionCorrecta != 0);
}