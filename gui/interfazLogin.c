#include <string.h>
#include <stdio.h>
#include "leerConsola.h"
#include "interfazLogin.h"

void mostrarInterfazLogin(void){

    char buffer[10];
    int caracterCorrecto = -1;
    int seleccion;
    do{
        printf("¡Bienvenido a la App!\n");
        printf("[1] Iniciar sesión\n"
            "[2] Registrarse\n"
            "[3] Salir\n"
            "Introduzca seleccion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer, &caracterCorrecto);
        switch (seleccion)
        {
        case 1:

            printf("Seleccionado inicar sesion\n");
            break;
        case 2:
            printf("Seleccionado registrarse\n");
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida. Inténtelo de nuevo.\n");
        }

    } while (seleccion != 3 || caracterCorrecto != 0);
        
}

