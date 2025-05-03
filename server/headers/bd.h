#ifndef BD_H
#define BD_H

#include "transaccion.h"
#include "usuario.h"
#include "cuenta.h"
#include "cuentasDisponibles.h"
#include "tarjeta.h"
#include "transaccion.h"
#include "sqlite3.h"

void abrirBD();
Usuario *cargarUsuario(const char *dni, int password);
int contarCuentas(const char *dni, int password);
int asignarTarjetas(Cuenta *cuenta);
int contarTarjetas(const char *numCuenta);
void guardarUsuario(Usuario *usuario);
void actualizarUsuario(Usuario *usuario);
void guardarAccesoUsuario(char *dni, char *numCuenta);
void cargarAccesoUsuario(Usuario *usuario);
Cuenta* cargarCuenta(const char *numCuenta);
void guardarCuenta(Cuenta *cuenta);
int contarTransaccionesCuenta(char* numCuenta);
int cargarTransaccionesCuenta(char* numCuenta);
int realizarTransferencia(const char *cuentaOrig, const char *cuentaDest, double cantidad);
int registrarTransaccion(const char *cuentaOrigen, const char *cuentaDestino, double cantidad);
int actualizarCuenta(Cuenta *cuenta);
int guardarTarjeta(Tarjeta *tarjeta);
Tarjeta *cargarTarjeta(const char *numTarjeta);
int guardarTransaccion(Transaccion *transaccion);
int registrarUsuario(Usuario usuario);
double consultarSaldo(const char *numCuenta);
int retirarDinero(const char* numCuenta, double cantidad);
int ingresarDinero(const char* numCuenta, double cantidad);
char ** obetenerNumTarjetasConCuentas(char **cuentas, int numCuentas);
int registrarIngreso(const char *numCuentaDest, double cant);
int registrarRetiro(const char *numCuentaOrig, double cant);
int borrarBD();
#endif