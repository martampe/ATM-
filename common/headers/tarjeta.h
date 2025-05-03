#ifndef TARJETA_H
#define TARJETA_H

typedef struct 
{
    //numTarjeta,fechaExpiracion,ccv,pin,estado,numCuenta,dniPropietario
    char numTarjeta[17];
    char fechaExpiracion[6];
    int ccv;
    int pin;
    int estado;
    char numCuenta[25];
    char dniPropietario[10];


}Tarjeta;

#endif