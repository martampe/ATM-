#ifndef CUENTA_H
#define CUENTA_H

typedef struct 
{
    char numCuenta[25];
    int saldo;
    int tipo;
    char fechaCreacion[11];
    int estado;
    char dniTitular[10];

}Cuenta;

#endif