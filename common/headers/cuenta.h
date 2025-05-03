#ifndef CUENTA_H
#define CUENTA_H

#include "tarjeta.h"

typedef struct 
{
    char numCuenta[25];
    double saldo;
    int tipo;
    char fechaCreacion[11];
    int estado;
    char dniTitular[10];
    Tarjeta *tarjetasDisp;
    int numTarjetasDisp;

}Cuenta;

#endif