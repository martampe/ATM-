#include "configuracionInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include "sistem.h"

enum OPERACION{
    ELIMINARTARJETA,
    CREARTARJETA,
    ELIMINARCUENTA,
    CREARCUENTA
};

int confirmacion(int seleccion, char *mensaje){

    int opcionValida = -1;

    while (opcionValida != 0)
    {
        if (seleccion > 0)
       {
        char bufferConfirmacion[3];
        int confirmacion;   
            do 
            {
                clearScreen();
                printf("%s", mensaje);
                printf("[1] Confirmar operacion\n"
                    "[2] Cancelar operacion\n"
                    "Seleccionar operacion: ");

                fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                confirmacion = leerInteger(bufferConfirmacion);
                
                switch (confirmacion)
                {
                case 1:
                    return 0;
                    break;
                
                case 2:
                    clearScreen();
                    printf("Operacion cancelada\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    return 1;
                    break;
                default:
                    clearScreen();
                    printf("Opcion no valida. Intentelo de nuevo\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    return 1;
                    break;
                    
                }

            } while (confirmacion != 1 && confirmacion != 2);
       } else if (seleccion != 0){
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            return 1;
       }
    }
    

    
}

void eliminarTarjeta(){
    

    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Eliminar tarjeta\n");
        //printear las tarjetas
        printf("[0] Volver a la configuracion\n"
            "Introduzaca la tarjeta a eliminar ('0' para volver a la configuracion): ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        if(seleccion == 0) break;

        char mensaje[30];
        snprintf(mensaje, sizeof(mensaje), "Eliminar tarjeta %d\n", seleccion);

        int confirmada = confirmacion(seleccion, mensaje);

       if (confirmada == 0)
       {
            clearScreen();
            printf("Tarjeta %d eliminada\n", seleccion);
            printf("Persiona enter para continuar...");
            limpiarBuffer();
       }
       
       
       

    } while (seleccion != 0);
}

void crearTarjeta(){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Crear tarjeta\n");
        printf("[0] Volver a la configuracion\n"
            "[1] Crear nueva tarjeta\n"
            "Selecciona operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        
        if(seleccion == 0) break;
        if(seleccion != 1) {
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            break;
        }
        char mensaje[30];
        snprintf(mensaje, sizeof(mensaje), "Crear cuenta\n");

        int confirmada = confirmacion(seleccion, mensaje);

       if (confirmada == 0)
       {
            clearScreen();
            printf("Tarjeta creada. Datos...\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
       }
        
        
       

    } while (seleccion != 0);

}

void eliminarCuenta(){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Eliminar Cuenta\n");
        //printear las cuentas
        printf("[0] Volver a la configuracion\n"
            "Introduzaca la cuenta a eliminar ('0' para volver a la configuracion): ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
       
        if(seleccion == 0) break;

        char mensaje[30];
        snprintf(mensaje, sizeof(mensaje), "Eliminar tarjeta %d\n", seleccion);

        int confirmada = confirmacion(seleccion, mensaje);

       if (confirmada == 0)
       {
            clearScreen();
            printf("Cuenta %d eliminada\n", seleccion);
            printf("Persiona enter para continuar...");
            limpiarBuffer();
       }

    } while (seleccion != 0);
}

void crearCuenta(){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Crear Cuenta\n");
        printf("[0] Volver a la configuracion\n"
            "[1] Crear nueva cuenta\n"
            "Selecciona operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
       
        if(seleccion == 0) break;
        if(seleccion != 1) {
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            break;
        }

        char mensaje[30];
        snprintf(mensaje, sizeof(mensaje), "Crear cuenta\n");

        int confirmada = confirmacion(seleccion, mensaje);

       if (confirmada == 0)
       {
            clearScreen();
            printf("Cuenta creada. Datos...\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
       }

    } while (seleccion != 0);
}


void mostrarConfiguracionInterfaz(){

    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Configuracion\n");
        printf("[1] Eliminar tarjeta\n"
            "[2] Crear tarjeta\n"
            "[3] Eliminar cuenta\n"
            "[4] Crear cuenta\n"
            "[5] Volver al menu principal\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
       
        switch (seleccion)
        {
        case 1:
            eliminarTarjeta();
            break;
        case 2:
            crearTarjeta();
            break;
        case 3:
            eliminarCuenta();
            break;
        case 4:
            crearCuenta();
            break;
        case 5:
            break;
        default:
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            break;
        }

    } while (seleccion != 5);
}