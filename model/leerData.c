#include "leerData.h"
#include <stdlib.h>
#include <string.h>
#include "leerConsola.h"

int contarLineas(FILE *file){
    int lineas = 0;
    char linea[250];
    while ((fgets(linea, sizeof(linea), file)) != NULL)
    {
        lineas ++;
    }

    return lineas;
    
}

Usuario* leerUsuarios(){
    //10 usuarios
    //IMPORTANTE LIBERAR MEMORIA
    FILE *usuariosFile = fopen("resources/data/Usuarios.csv", "r");
    if (usuariosFile == NULL)
    {
        printf("Error: al cargar el archivo");
        return NULL;
    }
    
    int lineas = contarLineas(usuariosFile);
    fseek(usuariosFile, 0L, SEEK_SET);
    Usuario *usuarios = (Usuario*) calloc(lineas, sizeof(Usuario));
    int idx = 0;
    char linea[200];
    while (fgets(linea, sizeof(linea), usuariosFile) != NULL)
    {

        Usuario *usuarioActual = &usuarios[idx];
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
        
        

        strcpy(usuarioActual->dni, dni);
        strcpy(usuarioActual->nombre, nombre);
        strcpy(usuarioActual->apellidos, apellido);
        strcpy(usuarioActual->fechaNac, fecha_nac);
        strcpy(usuarioActual->email, email);
        strcpy(usuarioActual->telefono, tlfn);
        strcpy(usuarioActual->password, password);
        strcpy(usuarioActual->pregunta_seguridad, pregunta_seguridad);
        strcpy(usuarioActual->respuesta_seguridad, respuesta_seguridad);
        strcpy(usuarioActual->dir, dir);

        idx++;
    } 

    fclose(usuariosFile);

    return usuarios;
    
}

Transaccion* leerTransacciones(){
    FILE *transaccionesFile = fopen("resources/data/Transacciones.csv", "r");
    if (transaccionesFile == NULL)
    {
        printf("Error: al cargar el archivo");
        return NULL;
    }
    
    int lineas = contarLineas(transaccionesFile);
    fseek(transaccionesFile, 0L, SEEK_SET);
    Transaccion *transacciones = (Transaccion*) calloc(lineas, sizeof(Transaccion));
    int idx = 0;

    char linea[200];

    while ((fgets(linea, sizeof(linea), transaccionesFile) != NULL))
    {
        //id,numCuenta_orig,numTarjeta_orig,numCuenta_dest,cant,fecha,dir_ATM,estado,tipo
        
        Transaccion *transaccionActual = &transacciones[idx];

        char *id = strtok(linea, ";");
        char *numCuentaOrigen = strtok(NULL, ";");
        char *numeroTarjetaOrigen = strtok(NULL, ";");
        char *numCuentaDestino = strtok(NULL, ";");
        char *cantidad = strtok(NULL, ";");
        char *fecha = strtok(NULL, ";");
        char *dirATM = strtok(NULL, ";");
        char *estado = strtok(NULL, ";");
        char *tipo = strtok(NULL, "\n");

        transaccionActual->id = atoi(id);
        strcpy(transaccionActual->numCuentaOrigen, numCuentaOrigen);
        transaccionActual->numeroTarjetaOrigen = atoi(numeroTarjetaOrigen);
        strcpy(transaccionActual->numCuentaDestino, numCuentaDestino);
        transaccionActual->cantidad = atoi(cantidad);
        strcpy(transaccionActual->fecha, fecha);
        strcpy(transaccionActual->dirATM, dirATM);
        transaccionActual->estado = atoi(estado);
        transaccionActual->tipo = atoi(tipo);

        idx++;

    }

    fclose(transaccionesFile);
    return transacciones;
    

}

void leerAcceso(){

    FILE *accesoFile = fopen("resources/data/AccesoCuenta.csv", "r");
    if (accesoFile == NULL)
    {
        printf("Error: al cargar el archivo");
        return;
    }
    
    int idx = 0;

    char linea[100];

    while ((fgets(linea, sizeof(linea), accesoFile)) != NULL);
    {
        //dni,numCuenta

        char *dni = strtok(linea, ",");
        char *numCuenta = strtok(NULL, "\n");

    }
    
    fclose(accesoFile);

}