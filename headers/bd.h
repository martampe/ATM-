#ifndef BD_H
#define BD_H

#include "usuario.h"
#include "cuenta.h"
#include "cuentasDisponibles.h"

void abrirBD();
Usuario* cargarUsuario(const char *dni, int password);
void guardarUsuario(Usuario *usuario);
void actualizarUsuario(Usuario *usuario);
void guardarAccesoUsuario(char *dni, char *numCuenta);
void cargarAccesoUsuario(Usuario *usuario);
Cuenta* cargarCuenta(const char *numCuenta);
void guardarCuenta(Cuenta *cuenta);
int realizarTransferencia(char *cuentaOrig, char *cuentaDest, double cantidad);

#endif