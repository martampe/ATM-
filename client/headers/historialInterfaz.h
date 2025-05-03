#ifndef HISTORIAL_INTERFAZ_H
#define HISTORIAL_INTERFAZ_H

#include "transaccion.h"

typedef enum {
    TRANSFERENCIA = 1,
    PAGO_CON_TARJETA = 2,
    RETIRO_EN_EFECTIVO = 3,
    INGRESO_EN_EFECTIVO = 4

} TIPO_TRANSACCIONES;

void imprimirTransaccionCuenta(Transaccion transacccion, int num);
void mostrarHistorialInterfaz(void);
void mostrarTransaccionesTarjeta();
void mostrarTransaccionesCuenta();
void imprimirTransaccionTarjeta(Transaccion transaccion, int i);

#endif