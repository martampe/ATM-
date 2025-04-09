#ifndef BD_H
#define BD_H

#include "transaccion.h"
#include "usuario.h"
#include "cuenta.h"
#include "cuentasDisponibles.h"
#include "tarjeta.h"
#include "transaccion.h"
#include <sqlite3.h>
void abrirBD();
char** cargarUsuario(const char *dni, int password, int *numCuentas);
void guardarUsuario(Usuario *usuario);
void actualizarUsuario(Usuario *usuario);
void guardarAccesoUsuario(char *dni, char *numCuenta);
void cargarAccesoUsuario(Usuario *usuario);
Cuenta* cargarCuenta(const char *numCuenta);
void guardarCuenta(Cuenta *cuenta);
int contarTransaccionesCuenta(char* numCuenta);
int mostrarTransaccionesCuenta(char* numCuenta);
int realizarTransferencia(char *cuentaOrig, char *cuentaDest, double cantidad);
int actualizarCuenta(Cuenta *cuenta);
int guardarTarjeta(Tarjeta *tarjeta);
Tarjeta *cargarTarjeta(const char *numTarjeta);
int guardarTransaccion(Transaccion *transaccion);
int registrarUsuario(Usuario usuario);
double consultarSaldo(char *numCuenta, sqlite3_stmt *stmt);
int retirarDinero(const char* numCuenta, double cantidad);
int ingresarDinero(const char* numCuenta, double cantidad);
#endif