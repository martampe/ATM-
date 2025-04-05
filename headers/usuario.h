#ifndef USUARIO_H
#define USUARIO_H

#include "cuenta.h"
#include "cuentasDisponibles.h"
typedef enum{
    YES,
    NO
} VALIDO;

typedef struct 
{
    //dni, nombre, apellido, fecha_nac, email, tlfno, password, pregunta_seguridad, respuesta_seguridad, dir
    VALIDO valido;
    char dni[10];
    char nombre [20];
    char apellidos [40];
    char fechaNac[20];
    char email[50];
    char telefono[15];
    int password;
    char pregunta_seguridad[100];
    char respuesta_seguridad[100];
    char dir [50];
    CuentasDisponibles *cuentasDisp;
    Cuenta *cuentaActual;

    
}Usuario;

#endif