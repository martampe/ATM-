#ifndef BD_H
#define BD_H

#include "usuario.h"
#include "cuenta.h"

void abrirBD();
Usuario* cargarUsuario(const char *dni, const char *password);
void guardarUsuario(Usuario *usuario, int decision);
void guardarAccesoUsuario(Usuario *usuario, Cuenta *cuenta);
int cargarAccesoUsuario(Usuario *usuario, Cuenta *cuenta);

#endif