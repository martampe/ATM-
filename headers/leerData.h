#ifndef LEER_DATA_H
#define LEER_DATA_H


#include "usuario.h"
#include <stdio.h>
#include "transaccion.h"

int contarLineas(FILE *file);
void leerUsuarios();

void leerTransacciones();
void leerAcceso();
void leerTarjetas();
void leerCuentas();

#endif