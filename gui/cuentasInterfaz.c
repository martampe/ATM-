#include "cuentasInterfaz.h"
#include <stdio.h>
#include "leerConsola.h"
#include "sistem.h"
#include "usuarioHandler.h"
#include "bd.h"
#include "cuenta.h"
#include <stdlib.h>

void mostrarDetallesCuentaInterfaz(char *cuenta) {
    char buffer[3];
    int seleccion;
    Cuenta *cuentaSelecionada = NULL;
    clearScreen();
    printf("Detalles de Cuenta <<%s>>\n", cuenta);
    cuentaSelecionada = cargarCuenta((const char*) cuenta);
    
    // Definir anchos para cada columna
    int anchoNumCuenta = 30;
    int anchoSaldo = 15;
    int anchoTarjetas = 20;
    
    // Imprimir cabeceras alineadas con los datos
    printf("%-*s", anchoNumCuenta, "Numero de cuenta");
    printf("%*s", 6, "saldo"); // Movido a la derecha
    printf("%*s\n", anchoTarjetas - 2, "tarjetas");
    
    // Imprimir barra horizontal separadora
    for (int i = 0; i < anchoNumCuenta + anchoSaldo + anchoTarjetas; i++) {
        printf("-");
    }
    printf("\n");
    
    // Definir posición fija para todas las tarjetas
    int posicionTarjeta = anchoNumCuenta + 10; // Alineado con la columna "tarjetas"
    
    // Imprimir primera línea con número de cuenta y saldo
    printf("[1] %-*s", anchoNumCuenta - 4, cuentaSelecionada->numCuenta);
    printf("%*.2f", 8, cuentaSelecionada->saldo);
    
    // Imprimir primera tarjeta si existe
    if (cuentaSelecionada->numTarjetasDisp > 0) {
        // Calculamos el espacio que ya hemos usado
        int espacioUsado = (anchoNumCuenta - 4) + 8; // Longitud de lo ya impreso
        
        // Imprimimos espacios hasta llegar a la posición de tarjetas
        int espaciosNecesarios = posicionTarjeta - espacioUsado;
        printf("%*s%s\n", espaciosNecesarios, "", cuentaSelecionada->tarjetasDisp[0].numTarjeta);
    } else {
        printf("\n");
    }
    
    // Imprimir tarjetas adicionales alineadas con la primera
    for (int i = 1; i < cuentaSelecionada->numTarjetasDisp; i++) {
        printf("%*s%s\n", posicionTarjeta + 4, "", cuentaSelecionada->tarjetasDisp[i].numTarjeta);
    }
    
    printf("\nPresione enter para salir....");
    limpiarBuffer();
    free(cuentaSelecionada);
}

void mostrarCuentasInterfaz(void){
    char buffer[3];
    int seleccion;
    do{
        clearScreen();
        printf("<<Mostrar cuentas>>\n");
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
            mostrarDetallesCuentaInterfaz(getUsuarioActual()->cuentasDisp[seleccion - 1].numCuenta); //pasar id de la cuenta
        } else {
            clearScreen();
            printf("Opcion no valida. Intentelo de nuevo\n");
            printf("Persiona enter para continuar...");
            limpiarBuffer();
        }
        

    } while (seleccion != 0);
}