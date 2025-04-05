#ifndef LEERDATA_H
#define LEERDATA_H

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