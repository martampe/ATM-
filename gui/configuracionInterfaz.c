#include "configuracionInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"

void eliminarTarjeta(){

    char buffer[3];
    int seleccion;
    do{
        printf("Eliminar tarjeta\n");
        //printear las tarjetas
        printf("[0] Volver a la configuracion\n"
            "Introduzaca la tarjeta a eliminar ('0' para volver a la configuracion): ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
       
       if (seleccion != 0)
       {
            char bufferConfirmacion[3];
            int confirmacion;   
                do 
                {
                    
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
                        printf("Tarjeta %d eliminada\n", seleccion);
                        break;
                    
                    case 2:
                        printf("Operacion cancelada\n");
                        break;
                    default:
                        printf("Opcion no valida. Intentelo de nuevo\n");
                        break;
                    }

                } while (confirmacion != 1 && confirmacion != 2);
        
        
        
       }
       

    } while (seleccion != 0);
}

void crearTarjeta(){
    char buffer[3];
    int seleccion;
    do{
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
                
                printf("[1] Confirmar operacion\n"
                    "[2] Cancelar operacion\n"
                    "Seleccionar operacion: ");

                fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                confirmacion = leerInteger(bufferConfirmacion);
                
                switch (confirmacion)
                {
                case 1:
                    //Crear tarjeta
                    printf("Tarjeta creada. Datos: ....\n");
                    break;
                
                case 2:
                    printf("Operacion cancelada\n");
                    break;
                default:
                    printf("Opcion no valida. Intentelo de nuevo\n");
                    break;
                }

            } while (confirmacion != 1 && confirmacion != 2);
        }
        
        
       

    } while (seleccion != 0);
}

void eliminarCuenta(){
    char buffer[3];
    int seleccion;
    do{
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
                        printf("Cuenta %d eliminada\n", seleccion);
                        break;
                    
                    case 2:
                        printf("Operacion cancelada\n");
                        break;
                    default:
                        printf("Opcion no valida. Intentelo de nuevo\n");
                        break;
                    }

                } while (confirmacion != 1 && confirmacion != 2);
        
        
        
       }
       

    } while (seleccion != 0);
}

void crearCuenta(){
    char buffer[3];
    int seleccion;
    do{
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
                
                printf("[1] Confirmar operacion\n"
                    "[2] Cancelar operacion\n"
                    "Seleccionar operacion: ");

                fgets(bufferConfirmacion, sizeof(bufferConfirmacion), stdin);
                confirmacion = leerInteger(bufferConfirmacion);
                
                switch (confirmacion)
                {
                case 1:
                    //Crear cuenta
                    printf("Cuenta creada. Datos: ....\n");
                    break;
                
                case 2:
                    printf("Operacion cancelada\n");
                    break;
                default:
                    printf("Opcion no valida. Intentelo de nuevo\n");
                    break;
                }

            } while (confirmacion != 1 && confirmacion != 2);
        }
        
        
       

    } while (seleccion != 0);
}


void mostrarConfiguracionInterfaz(){

    char buffer[3];
    int seleccion;
    do{
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
        default:
            printf("Operacion no valida. Volver a intentar\n");
            break;
        }

    } while (seleccion != 5);
}