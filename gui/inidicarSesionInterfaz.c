#include "iniciarSesionInterfaz.h"
#include "leerConsola.h"
#include "inicioInterfaz.h"
#include <stdio.h>
#include "sistem.h"

void iniciarSesion(){
    clearScreen();
    char bufferUsuario[30];
    char bufferContrasena[20];

    printf("Usuario: ");
    fgets(bufferUsuario, sizeof(bufferUsuario), stdin);

    printf("Contraseña: ");
    fgets(bufferContrasena, sizeof(bufferContrasena), stdin);

    mostrarInicioInterfaz();
}

void mostrarIniciarSesionInterfaz(void){

    
    char bufferSeleccion[3];
    int seleccion;
    do
    {
        clearScreen();

        printf("Inicio se sesion\n"
            "[0] Volver al portal\n"
            "[1] Iniciar sesion\n"
            "Seleccione operacion: ");

        fgets(bufferSeleccion, sizeof(bufferSeleccion), stdin);
        seleccion = leerInteger(bufferSeleccion);

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            iniciarSesion();
            break;
        default:
            clearScreen();
            printf("Opción no válida. Inténtelo de nuevo.\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            break;
        }

    } while (seleccion != 0 && seleccion != 1);
    
    

    

}