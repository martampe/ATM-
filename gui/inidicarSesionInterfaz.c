#include "iniciarSesionInterfaz.h"
#include "leerConsola.h"
#include "inicioInterfaz.h"
#include <stdio.h>
#include "sistem.h"
#include <string.h>
#include "bd.h"
#include <stdlib.h>
#include "usuarioHandler.h"
#include "cuentasDisponibles.h"


void mostrarCuentas(Usuario *usuario){

    printf("Seleccione una cuenta:\n");

    for (int i = 0; i < usuario->numCuentasDisp; i++)
    {
        printf("[%d] %s\n", i, usuario->cuentasDisp[i].numCuenta);
    }

    printf("Seleccione una cuenta: ");
    char bufferOpcion[10];
    fgets(bufferOpcion, sizeof(bufferOpcion), stdin);  
    int opcion = leerInteger(bufferOpcion);

    usuario->cuentaActual = usuario->cuentasDisp[opcion];
    printf("Cuenta actual: %s\n", usuario->cuentaActual.numCuenta);
    mostrarInicioInterfaz();

}

int iniciarSesion(){
    clearScreen();
    char bufferDni[30];
    char bufferContrasena[20];

    //mostrar-leer dni, eliminar \n de dni
    printf("Dni: ");
    fgets(bufferDni, sizeof(bufferDni), stdin);
    eliminarSaltoLinea(bufferDni);

    //mostrar-leer contraseña, convertir a int
    printf("Contraseña: ");
    fgets(bufferContrasena, sizeof(bufferContrasena), stdin);
    int contrasena = leerInteger(bufferContrasena);

    //buscar usuario
    Usuario *usuario = cargarUsuario(bufferDni, contrasena);
    
    if (!usuario) //si no valido, mostrar y liberar memoria
    {
        clearScreen();
        printf("Usuario o contraseña incorrecta. Intentelo de nuevo.\n");
        printf("Presione enter para continuar...");
        limpiarBuffer();
        return 1;

    }


    //set usuario actual y mostrar cuentas
    setUsuarioActual(usuario);

    mostrarCuentas(usuario);
    
}

void mostrarIniciarSesionInterfaz(void){

    
    char bufferSeleccion[3];
    int seleccion;
    int rc = -1;

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
            rc = 0;
            break;
        case 1:
            rc = iniciarSesion();
            break;
        default:
            clearScreen();
            printf("Opción no válida. Inténtelo de nuevo.\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            rc = 1;
            break;
        }

    } while (rc != 0);
    
    

    

}