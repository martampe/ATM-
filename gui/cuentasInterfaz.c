#include "cuentasInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include "sistem.h"
#include "usuarioHandler.h"
#include "bd.h"
#include "cuenta.h"

void mostrarDetallesCuentaInterfaz(char *cuenta){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Detalles de Cuenta <<%s>>\n", cuenta);
        Cuenta *cuentaSelecionada = cargarCuenta((const char*) cuenta);
        printf("Num tarjetas: %d", cuentaSelecionada->numTarjetasDisp);
        for (int i = 0; i < cuentaSelecionada->numTarjetasDisp; i++)
        {
            printf("Num %s\n", cuentaSelecionada->tarjetasDisp[i].numTarjeta);
        }
        
        printf("Numero de cuenta      saldo     tarjetas\n");
        printf("%s    %.2f    %s", cuentaSelecionada->numCuenta, cuentaSelecionada->saldo, cuentaSelecionada->numTarjetasDisp != 0 ? cuentaSelecionada->tarjetasDisp[0].numTarjeta : "");
        for (int i = 1; i < cuentaSelecionada->numTarjetasDisp; i++)
        {
            printf("                                     %s", cuentaSelecionada->tarjetasDisp[i].numTarjeta);
        }
        
        printf("[0] Volver al a tus cuentas\n"
            "Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        switch (seleccion)
        {
        case 0:
            printf("Presionado volver a tus cuentas\n");
            break;

        default:
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }

    } while (seleccion != 0);
}

void mostrarCuentasInterfaz(void){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("Cuentas\n");
        for (int i = 0; i < getUsuarioActual()->numCuentasDisp; i++)
        {
            printf("[%d] %s\n", i + 1, getUsuarioActual()->cuentasDisp[i].numCuenta);
        }
        
        printf("[0] Volver al menu principal\n"
            "Introduzca la cuenta ('0' para cancelar): ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);
        
        if (seleccion == 0)
        {
            printf("Seleccionado volver al menu principal\n");
            return;
        } else if(seleccion > 0 && seleccion <= getUsuarioActual()->numCuentasDisp){
            printf("Seleccionado ver cuenta %d\n", seleccion);
            mostrarDetallesCuentaInterfaz(getUsuarioActual()->cuentasDisp[seleccion].numCuenta); //pasar id de la cuenta
        } else {
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }
        

    } while (seleccion != 0);
}