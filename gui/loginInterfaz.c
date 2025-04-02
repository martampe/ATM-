#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "leerConsola.h"
#include "inicioInterfaz.h"
#include "loginInterfaz.h"
#include "iniciarSesionInterfaz.h"
#include "registrarInterfaz.h"
#include "sistem.h"

void mostrarLoginInterfaz(void){

    char buffer[3];
    int seleccion;
    do{
        //clearScreen();

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
            mostrarIniciarSesionInterfaz();
            break;
        case 2:
            printf("Seleccionado registrarse\n");
            mostrarRegistrarInterfaz();
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            clearScreen();
            printf("Opción no válida. Inténtelo de nuevo.\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }

    } while (seleccion != 3 || seleccion == -1);
    
    exit(0);
}

