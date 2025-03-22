#include "configuracionInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include "sistem.h"

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
       
       if (seleccion > 0)
       {
        char bufferConfirmacion[3];
        int confirmacion;   
            do 
            {
                clearScreen();
                
                printf("Eliminar tarjeta %d\n"
                    "[1] Confirmar operacion\n"
                    "[2] Cancelar operacion\n"
                    "Seleccionar operacion: ", seleccion);

                fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                confirmacion = leerInteger(bufferConfirmacion);
                
                switch (confirmacion)
                {
                case 1:
                    //Eliminar tarjeta
                    clearScreen();
                    printf("Tarjeta %d eliminada\n", seleccion);
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
                    printf("Opcion no valida. Intentelo de nuevo\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    break;
                    
                }

            } while (confirmacion != 1 && confirmacion != 2);
       } else if (seleccion != 0){
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
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
       
        if (seleccion == 1)
        {
            char bufferConfirmacion[3];
            int confirmacion;   
            do 
            {   
                clearScreen();
                
                printf("[1] Confirmar operacion\n"
                    "[2] Cancelar operacion\n"
                    "Seleccionar operacion: ");

                fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                confirmacion = leerInteger(bufferConfirmacion);
                
                switch (confirmacion)
                {
                case 1:
                    //Crear tarjeta
                    
                    clearScreen();
                    printf("Tarjeta creada. Datos: ....\n");
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
                    printf("Opcion no valida. Intentelo de nuevo\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }

            } while (confirmacion != 1 && confirmacion != 2);
        } else if(seleccion != 0){
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
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
       
       if (seleccion != 0)
       {
            char bufferConfirmacion[3];
            int confirmacion;   
                do 
                {
                    clearScreen();
                    printf("Eliminar cuenta %d\n"
                        "[1] Confirmar operacion\n"
                        "[2] Cancelar operacion\n"
                        "Seleccionar operacion: ", seleccion);

                    fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                    confirmacion = leerInteger(bufferConfirmacion);
                    
                    switch (confirmacion)
                    {
                    case 1:
                        //Eliminar cuenta
                        clearScreen();
                        printf("Cuenta %d eliminada\n", seleccion);
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
                        printf("Opcion no valida. Intentelo de nuevo\n");
                        printf("Persiona enter para continuar...");
                        limpiarBuffer();
                        break;
                    }

                } while (confirmacion != 1 && confirmacion != 2);
        
        
        
       } else if(seleccion != 0){
        clearScreen();
        printf("Opcion no valida. Intentelo de nuevo\n");
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
       
        if (seleccion == 1)
        {
            char bufferConfirmacion[3];
            int confirmacion;   
            do 
            {
                clearScreen();
                printf("[1] Confirmar operacion\n"
                    "[2] Cancelar operacion\n"
                    "Seleccionar operacion: ");

                fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                confirmacion = leerInteger(bufferConfirmacion);
                
                switch (confirmacion)
                {
                case 1:
                    //Crear cuenta
                    clearScreen();
                    printf("Cuenta creada. Datos: ....\n");
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
                    printf("Opcion no valida. Intentelo de nuevo\n");
                    printf("Persiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }

            } while (confirmacion != 1 && confirmacion != 2);
        } else if(seleccion != 0){
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
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