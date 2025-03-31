#include "inicioInterfaz.h"
#include "leerConsola.h"
#include "registrarInterfaz.h"
#include <stdio.h>
#include "sistem.h"

void iniciarRegistrar(){
    clearScreen();

    char bufferUsuario[30];
    char bufferContrasena[20];

    printf("Usuario: ");
    fgets(bufferUsuario, sizeof(bufferUsuario), stdin);

    printf("Contraseña: ");
    fgets(bufferContrasena, sizeof(bufferContrasena), stdin);

    mostrarInicioInterfaz();
}

void mostrarRegistrarInterfaz(void){

    
    char bufferSeleccion[3];
    int seleccion;
    do
    {
        clearScreen();

        printf("Registro de usuario\n"
            "[0] Volver al portal\n"
            "[1] Registrar\n"
            "Seleccione operacion: ");

        fgets(bufferSeleccion, sizeof(bufferSeleccion), stdin);
        seleccion = leerInteger(bufferSeleccion);

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            iniciarRegistrar();
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