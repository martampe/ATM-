#ifndef BD_H
#define BD_H

#include "transaccion.h"
#include "usuario.h"
#include "cuenta.h"
#include "cuentasDisponibles.h"
#include "tarjeta.h"
#include "transaccion.h"
void abrirBD();
Usuario* cargarUsuario(const char *dni, int password);
void guardarUsuario(Usuario *usuario);
void actualizarUsuario(Usuario *usuario);
void guardarAccesoUsuario(char *dni, char *numCuenta);
void cargarAccesoUsuario(Usuario *usuario);
Cuenta* cargarCuenta(const char *numCuenta);
void guardarCuenta(Cuenta *cuenta);
int contarTransaccionesCuenta(char* numCuenta);
void mostrarTransaccionesCuenta(char* numCuenta);
int realizarTransferencia(char *cuentaOrig, char *cuentaDest, double cantidad);
<<<<<<< HEAD


=======
void actualizarCuenta(Cuenta *cuenta);
void guardarTarjeta(Tarjeta *tarjeta);
Tarjeta *cargarTarjeta(const char *numTarjeta);
void guardarTransaccion(Transaccion *transaccion);
>>>>>>> 77618ac5457ce4c5b6080d01618e50497e7f158d
#endif