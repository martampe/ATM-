#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "leerConsola.h"
#include "inicioInterfaz.h"
#include "loginInterfaz.h"

void mostrarLoginInterfaz(void){

    char buffer[3];
    int seleccion;
    do{
        printf("¡Bienvenido a la App!\n");
        printf("[1] Iniciar sesión\n"
            "[2] Registrarse\n"
            "[3] Salir\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 1:

            printf("Seleccionado inicar sesion\n");
            mostrarInicioInterfaz();
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

    } while (seleccion != 3 || seleccion == -1);
    
    exit(0);
}

