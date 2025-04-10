#include "inicioInterfaz.h"
#include "leerConsola.h"
#include "registrarInterfaz.h"
#include <stdio.h>
#include "bd.h"
#include "sistem.h"
#include <string.h>
#include "usuario.h"
#include "usuarioHandler.h"
#include <stdlib.h>

int iniciarRegistrar(){
    clearScreen();

    char bufferDni[10];
    char bufferNombre [20];
    char bufferApellidos [40];
    char bufferFechaNac[20];
    char bufferEmail[50];
    char bufferTelefono[15];
    char bufferPassword[20];
    char bufferPregunta_seguridad[100];
    char bufferRespuesta_seguridad[100];
    char bufferDir [50];
    printf("<<Registrar nuevo usuario>>\n"
           "Ingrese los datos solicitados:\n");
    
    do
    {
        printf("Dni: ");
    } while ((leerEntradaSegura(bufferDni, sizeof(bufferDni))) != 0);

    do
    {
        printf("Nombre: ");
    } while ((leerEntradaSegura(bufferNombre, sizeof(bufferNombre))) != 0);

    do
    {
        printf("Apellido: ");
    } while ((leerEntradaSegura(bufferApellidos, sizeof(bufferApellidos))) != 0);

    do
    {
        printf("Fecha de nacimiento (yyyy-mm-dd): ");
    } while ((leerEntradaSegura(bufferFechaNac, sizeof(bufferFechaNac))) != 0);

    do
    {
        printf("Email: ");
    } while ((leerEntradaSegura(bufferEmail, sizeof(bufferEmail))) != 0);

    do
    {
        printf("Telefono (sin guiones): ");
    } while ((leerEntradaSegura(bufferTelefono, sizeof(bufferTelefono))) != 0);

    do
    {
        printf("Contraseña: ");
    } while ((leerEntradaSegura(bufferPassword, sizeof(bufferPassword))) != 0);

    do
    {
        printf("Pregunta de seguridad: ");
    } while ((leerEntradaSegura(bufferPregunta_seguridad, sizeof(bufferPregunta_seguridad))) != 0);

    do
    {
        printf("Respuesta de seguridad: ");
    } while ((leerEntradaSegura(bufferRespuesta_seguridad, sizeof(bufferRespuesta_seguridad))) != 0);

    do
    {
        printf("Direccion: ");
    } while ((leerEntradaSegura(bufferDir, sizeof(bufferDir))) != 0);

    


    Usuario *usuario = calloc(1, sizeof(Usuario));
    strcpy(usuario->apellidos, bufferApellidos);
    strcpy(usuario->dir, bufferDir);
    strcpy(usuario->dni, bufferDni);
    strcpy(usuario->email, bufferEmail);
    strcpy(usuario->fechaNac, bufferFechaNac);
    strcpy(usuario->nombre, bufferNombre);
    usuario->password = leerInteger(bufferPassword);
    strcpy(usuario->pregunta_seguridad, bufferPregunta_seguridad);
    strcpy(usuario->respuesta_seguridad, bufferRespuesta_seguridad);
    strcpy(usuario->telefono, bufferTelefono);

    if((registrarUsuario(*usuario)) != 0){
        free(usuario);
        return -1;
    }

    usuario->valido = YES;
    setUsuarioActual(usuario);

    mostrarInicioInterfaz();
}

void mostrarRegistrarInterfaz(void){

    
    char bufferSeleccion[3];
    int seleccion;
    int operacionCorrecta = -1;
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
            operacionCorrecta = 0;
            break;
        case 1:
            operacionCorrecta = iniciarRegistrar();
            if (operacionCorrecta != 0)
            {
                printf("Ha habido un error a la hora de crear el usuario\n");
            }
            

            break;
        default:
            operacionCorrecta = -1;
            clearScreen();
            printf("Opción no válida. Inténtelo de nuevo.\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
            break;
        }

    } while (operacionCorrecta != 0);
    
    

    

}