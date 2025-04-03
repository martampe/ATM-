#ifndef TRANSACCION_H
#define TRANSACCION_H

typedef struct 
{
    //id,numCuenta_orig,numTarjeta_orig,numCuenta_dest,cant,fecha,dir_ATM,estado,tipo
    int id;
    char numCuentaOrigen[25];
    char numeroTarjetaOrigen[17];
    char numCuentaDestino[25];
    int cantidad;
    char fecha[20];
    char dirATM[50];
    int estado;
    int tipo;

}Transaccion;

#endif
