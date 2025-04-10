#include "historialInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include <string.h>
#include "sistem.h"
#include "usuarioHandler.h"
#include "bd.h"
void imprimirTransaccionCuenta(Transaccion transaccion, int num){
    if (transaccion.tipo == PAGO_CON_TARJETA) return;
    
    char buffer[200];
    if (transaccion.tipo == TRANSFERENCIA) {
        int signo = strcmp(transaccion.numCuentaOrigen, getUsuarioActual()->cuentaActual.numCuenta) != 0 ? 1 : -1;
        int cantidad = signo * transaccion.cantidad;
        sprintf(buffer, "[%d] %-25s %-10s %8d  %-24s %-24s",
                num,
                "Transferencia bancaria",
                transaccion.fecha,
                cantidad,
                transaccion.numCuentaOrigen,
                transaccion.numCuentaDestino);
    } else if (transaccion.tipo == INGRESO_EN_EFECTIVO) {
        sprintf(buffer, "[%d] %-25s %-10s %8d",
                num,
                "Ingreso en efectivo",
                transaccion.fecha,
                transaccion.cantidad);
    } else {
        sprintf(buffer, "[%d] %-25s %-10s %8d",
                num,
                "Retiro en efectivo",
                transaccion.fecha,
                transaccion.cantidad * -1);
    }
    printf("%s\n", buffer);
}

void mostrarTransaccionesCuenta(){
    clearScreen();
    printf("<<Transacciones de cuenta>> \n");
    printf("*-------------*\n");
    printf("| Saldo: %2.f |\n", getUsuarioActual()->cuentaActual.saldo);
    printf("*-------------*\n");


    printf("%-5s %-25s %-10s %8s  %-24s %-24s\n",
           "Num", "Tipo de transaccion", "Fecha", "Cantidad", "Cuenta origen", "Cuenta destino");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < getUsuarioActual()->numeroTransacciones; i++) {
        imprimirTransaccionCuenta(getUsuarioActual()->transaciones[i], i);
    }
    printf("Presiona cualquier letra para salir...");
    limpiarBuffer();
}

void imprimirTransaccionTarjeta(Transaccion transaccion, int i){
    if (transaccion.tipo == PAGO_CON_TARJETA) {
        char buffer[200];
        sprintf(buffer, "[%d] %-12s %8d      %-20s", 
                i, 
                transaccion.fecha, 
                -transaccion.cantidad, 
                transaccion.numeroTarjetaOrigen);
        printf("%s\n", buffer);
    }
}

void mostrarTransaccionesTarjeta(){
    clearScreen();
    printf("<<Operaciones de tarjeta>> \n");
    printf("*-------------*\n");
    printf("| Saldo: %2.f |\n", getUsuarioActual()->cuentaActual.saldo);
    printf("*-------------*\n");
    printf("%-5s %-12s %8s      %-20s\n",
           "Num", "Fecha", "Cantidad", "Tarjeta");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < getUsuarioActual()->numeroTransacciones; i++) {
        imprimirTransaccionTarjeta(getUsuarioActual()->transaciones[i], i);
    }
    
    printf("Presiona cualquier letra para salir...");
    limpiarBuffer();
}

void mostrarHistorialInterfaz(void) {
    char buffer[3];
    int seleccion;
    int operacionCorrecta = -1;
    do {
        clearScreen();
        printf("Historial de Transacciones\n");
        printf("[0] Volver al menu principal\n");
        printf("[1] Mostrar transacciones bancarias\n");
        printf("[2] Mostrar operaciones de tarjeta\n");
        printf("Introduzca operacion: ");

        fgets(buffer, sizeof(buffer), stdin);
        seleccion = leerInteger(buffer);

        switch (seleccion) {
            case 0:
                printf("Seleccionado volver al menu principal\n");
                operacionCorrecta  = 0;
                break;

            case 1: 
                printf("Seleccionado mostrar mis transacciones\n");
                operacionCorrecta = cargarTransaccionesCuenta(getUsuarioActual()->cuentaActual.numCuenta);
                if (operacionCorrecta != 0)
                {
                    clearScreen();
                    printf("No hay transacciones diponibles para mostrar\n");
                    printf("Presiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }   
                mostrarTransaccionesCuenta();
                break;
            
            case 2:
                printf("Seleccionado mostrar operaciones de tarjeta\n");
                operacionCorrecta = cargarTransaccionesCuenta(getUsuarioActual()->cuentaActual.numCuenta);
                if (operacionCorrecta != 0)
                {
                    clearScreen();
                    printf("No hay transacciones diponibles para mostrar\n");
                    printf("Presiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }
                
                mostrarTransaccionesTarjeta();
            break;

            default:
                clearScreen();
                printf("Opcion no valida. Intentelo de nuevo\n");
                printf("Presiona enter para continuar...");
                limpiarBuffer(); 
        }

    } while (operacionCorrecta != 0);  
    
}
