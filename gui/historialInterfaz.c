#include "historialInterfaz.h"
#include "leerConsola.h"
#include <stdio.h>
#include <string.h>
#include "sistem.h"
#include "usuarioHandler.h"
#include "bd.h"

void imprimirTransaccionCuenta(Transaccion transacccion, int num){
    if (transacccion.tipo == PAGO_CON_TARJETA) return;

    if (transacccion.tipo == TRANSFERENCIA)
    {
        printf("[%d] %s %s %s%d %s %s Tipo: %d\n", num, "Transferencia bancaria", transacccion.fecha,strcmp(transacccion.numCuentaOrigen, getUsuarioActual()->cuentaActual.numCuenta) != 0 ? "" : "-",transacccion.cantidad, transacccion.numCuentaOrigen, transacccion.numCuentaDestino, transacccion.tipo);
    } else if (transacccion.tipo = INGRESO_EN_EFECTIVO){
        printf("[%d] %s %s %d\n", num, "Ingreso en efectivo", transacccion.fecha, transacccion.cantidad);
    } else {
        printf("[%d] %s %s %d\n", num, "Retiro en efectivo", transacccion.fecha, transacccion.cantidad);
    }
    
}


void mostrarTransaccionesCuenta(){
    clearScreen();
    printf("Transacciones de cuenta: \n");
    printf("    Tipo de transaccion      Fecha      Cantidad     Cuenta origen      Cuenta destino\n");
    for (int i = 0; i < getUsuarioActual()->numeroTransacciones; i++)
    {
        imprimirTransaccionCuenta(getUsuarioActual()->transaciones[i], i);
    }
    
}

void imprimirTransaccionTarjeta(Transaccion transaccion, int i){
    if (transaccion.tipo == PAGO_CON_TARJETA)
    {
        printf("[%d] %s -%d %s\n", i, transaccion.fecha, transaccion.cantidad, transaccion.numeroTarjetaOrigen);
    }
    
}

void mostrarTransaccionesTarjeta(){
    clearScreen();
    printf("Operaciones de tarjeta: \n");
    printf("    Fecha      Cantidad     Tarjeta\n");
    for (int i = 0; i < getUsuarioActual()->numeroTransacciones; i++)
    {
        imprimirTransaccionTarjeta(getUsuarioActual()->transaciones[i], i);
    }
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
                    printf("Ha habido un error al cargar las transacciones\n");
                    printf("Presiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }
                
                limpiarBuffer();
                mostrarTransaccionesCuenta();
                break;
            
            case 2:
                printf("Seleccionado mostrar operaciones de tarjeta\n");
                operacionCorrecta = cargarTransaccionesCuenta(getUsuarioActual()->cuentaActual.numCuenta);
                if (operacionCorrecta != 0)
                {
                    printf("Ha habido un error al cargar las transacciones\n");
                    printf("Presiona enter para continuar...");
                    limpiarBuffer();
                    break;
                }
                
                limpiarBuffer();
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
