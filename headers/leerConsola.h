#ifndef LEER_CONSOLA_H
#define LEER_CONSOLA_H
#include <stddef.h>
int leerInteger(char *numero);

void limpiarBuffer();
int eliminarSaltoLinea(char *linea);
int leerEntradaSegura(char *buffer, size_t size);

#endif