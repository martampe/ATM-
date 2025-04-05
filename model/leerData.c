#include "leerData.h"
#include <stdlib.h>
#include <string.h>
#include "tarjeta.h"
#include "leerConsola.h"
#include "cuenta.h"
#include "bd.h"

int contarLineas(FILE *file){
    int lineas = 0;
    char linea[250];
    while ((fgets(linea, sizeof(linea), file)) != NULL)
    {
        lineas ++;
    }

    return lineas;
    
}

void leerUsuarios(){
    //10 usuarios
    //IMPORTANTE LIBERAR MEMORIA
    FILE *usuariosFile = fopen("resources/data/Usuarios.csv", "r");
    if (usuariosFile == NULL)
    {
        printf("Error: al cargar el archivo de Usuarios\n");
        return;
    }
    
   
    char linea[200];
    while (fgets(linea, sizeof(linea), usuariosFile) != NULL)
    {

        Usuario usuarioActual;
        //dni, nombre, apellido, fecha_nac, email, tlfno, password, pregunta_seguridad, respuesta_seguridad, dir
        char *dni = strtok(linea, ",");
        char *nombre = strtok(NULL, ",");
        char *apellido = strtok(NULL, ",");
        char *fecha_nac = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *tlfn = strtok(NULL, ",");
        char *password = strtok(NULL, ",");
        char *pregunta_seguridad = strtok(NULL, ",");
        char *respuesta_seguridad = strtok(NULL, ",");
        char *dir = strtok(NULL, "\n");  // Captura todo hasta el final de la línea

        // Eliminar comillas si existen
        if (dir && dir[0] == '"') {
            // Eliminar comilla inicial
            dir++;
        }

        if (strchr(dir, '"') != NULL)
        {
            dir[strcspn(dir, "\"")] = '\0';
        }
        
        
        usuarioActual.valido = YES;
        strcpy(usuarioActual.dni, dni);
        strcpy(usuarioActual.nombre, nombre);
        strcpy(usuarioActual.apellidos, apellido);
        strcpy(usuarioActual.fechaNac, fecha_nac);
        strcpy(usuarioActual.email, email);
        strcpy(usuarioActual.telefono, tlfn);
        strcpy(usuarioActual.password, password);
        strcpy(usuarioActual.pregunta_seguridad, pregunta_seguridad);
        strcpy(usuarioActual.respuesta_seguridad, respuesta_seguridad);
        strcpy(usuarioActual.dir, dir);

        //printf("Dni: %s, Nombre: %s, Apellidos: %s, fechaNac: %s, Email: %s, Telefono: %s, Password: %s, Pregunta: %s, Respuesta: %s, Dir: %s\n",
        //usuarioActual.dni, usuarioActual.nombre, usuarioActual.apellidos, usuarioActual.fechaNac, usuarioActual.email, usuarioActual.telefono, usuarioActual.password, usuarioActual.pregunta_seguridad, usuarioActual.respuesta_seguridad, usuarioActual.dir);
        guardarUsuario(&usuarioActual, 0);
    } 

    fclose(usuariosFile);

    
}

void leerTransacciones(){
    FILE *transaccionesFile = fopen("resources/data/Transacciones.csv", "r");
    if (transaccionesFile == NULL)
    {
        printf("Error: al cargar el archivo de transacciones\n");
        return;
    }
    
    

    char linea[200];

    while ((fgets(linea, sizeof(linea), transaccionesFile) != NULL))
    {
        
        Transaccion transaccionActual;

        char *id = strtok(linea, ";");
        char *numCuentaOrigen = strtok(NULL, ";");
        char *numeroTarjetaOrigen = strtok(NULL, ";");
        char *numCuentaDestino = strtok(NULL, ";");
        char *cantidad = strtok(NULL, ";");
        char *fecha = strtok(NULL, ";");
        char *dirATM = strtok(NULL, ";");
        char *estado = strtok(NULL, ";");
        char *tipo = strtok(NULL, "\n");

        transaccionActual.id = atoi(id);
        strcpy(transaccionActual.numCuentaOrigen, numCuentaOrigen);
        strcpy(transaccionActual.numeroTarjetaOrigen, numeroTarjetaOrigen);
        strcpy(transaccionActual.numCuentaDestino, numCuentaDestino);
        transaccionActual.cantidad = atoi(cantidad);
        strcpy(transaccionActual.fecha, fecha);
        strcpy(transaccionActual.dirATM, dirATM);
        transaccionActual.estado = atoi(estado);
        transaccionActual.tipo = atoi(tipo);

        //printf("Id: %d, Origen: %s, Tarjeta: %s, Destino: %s, Cantidad: %d, Fecha: %s, Dir: %s, Estado: %d, Tipo: %d\n",
        //transaccionActual.id, transaccionActual.numCuentaOrigen, transaccionActual.numeroTarjetaOrigen, transaccionActual.numCuentaDestino,transaccionActual.cantidad, transaccionActual.fecha, transaccionActual.dirATM, transaccionActual.estado, transaccionActual.tipo);
        

    }

    fclose(transaccionesFile);
    

}

void leerAcceso(){

    FILE *accesoFile = fopen("resources/data/AccesoCuenta.csv", "r");
    if (accesoFile == NULL)
    {
        printf("Error: al cargar el archivo de Acceso-Cuenta\n");
        return;
    }
    
    char linea[100];
    fseek(accesoFile, 0L, SEEK_SET);
    while ((fgets(linea, sizeof(linea), accesoFile)) != NULL)
    {
        //dni,numCuenta

        char *dni = strtok(linea, ",");
        char *numCuenta = strtok(NULL, "\n");

        printf("Dni: %s, numCuenta: %s\n", dni, numCuenta);

    }
    
    fclose(accesoFile);

}

void leerTarjetas(){

    //numTarjeta,fechaExpiracion,ccv,pin,estado,numCuenta,dniPropietario
    FILE *fileTarjeta = fopen("resources/data/Tarjeta.csv", "r");

    if (fileTarjeta == NULL)
    {
        printf("Error: No se ha podido abrir el fichero de tarjetas\n");
        return;
    }

    char linea[200];

    while ((fgets(linea, sizeof(linea), fileTarjeta)) != NULL)
    {

        Tarjeta tarjetaActual;

        char *numTarjeta = strtok(linea, ",");
        char *fechaExpiracion = strtok(NULL, ",");
        char *ccv = strtok(NULL, ",");
        char *pin = strtok(NULL, ",");
        char *estado = strtok(NULL, ",");
        char *numCuenta = strtok(NULL, ",");
        char *dniPropietario = strtok(NULL, "\n");

        strcpy(tarjetaActual.numTarjeta, numTarjeta);
        strcpy(tarjetaActual.fechaExpiracion, fechaExpiracion);
        tarjetaActual.ccv = atoi(ccv);
        tarjetaActual.pin = atoi(pin);
        tarjetaActual.estado = atoi(estado);
        strcpy(tarjetaActual.numCuenta, numCuenta);
        strcpy(tarjetaActual.dniPropietario, dniPropietario);

        //printf("Tarjeta: %s, Expiracion: %s, CCV: %d, Pin: %d, Estado: %d, Cuenta: %s, dniProp: %s\n",
        //tarjetaActual.numTarjeta, tarjetaActual.fechaExpiracion, tarjetaActual.ccv, tarjetaActual.pin, tarjetaActual.estado, tarjetaActual.numCuenta, tarjetaActual.dniPropietario);


    }
    
    

}

void leerCuentas(){

    FILE *fileCuentas = fopen("resources/data/Cuenta.csv", "r");

    if (fileCuentas == NULL)
    {
        printf("Error: No se pudo abrir el archivo de cuentas\n");
    }

    char linea[200];

    while ((fgets(linea, sizeof(linea), fileCuentas)) != NULL)
    {
        //numCuenta,saldo,tipo,fechaCreacion,estado,dniTitular

        Cuenta cuentaActual;

        char *numCuenta = strtok(linea, ",");
        char *saldo = strtok(NULL, ",");
        char *tipo = strtok(NULL, ",");
        char *fechaCreacion = strtok(NULL, ",");
        char *estado = strtok(NULL, ",");
        char *dniTitular = strtok(NULL, "\n");

        strcpy(cuentaActual.numCuenta, numCuenta);
        cuentaActual.saldo = atoi(saldo);
        cuentaActual.tipo = atoi(tipo);
        strcpy(cuentaActual.fechaCreacion, fechaCreacion);
        cuentaActual.estado = atoi(estado);
        strcpy(cuentaActual.dniTitular, dniTitular);

        //printf("numCuenta: %s, Saldo: %d, Tipo: %d, FechaCreacion: %s, Estado: %d, DniTitular: %s\n",
        //cuentaActual.numCuenta, cuentaActual.saldo, cuentaActual.tipo, cuentaActual.fechaCreacion, cuentaActual.estado, cuentaActual.dniTitular);
    }
    
    
}