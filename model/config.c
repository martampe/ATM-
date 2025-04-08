#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static FILE *config = NULL;
static char *pathConfig = "resources/config/config.txt";
static char pathAccesoCuenta[100];
static char pathCuenta[100];
static char pathTarjeta[100];
static char pathTransaccion[100];
static char pathUsuario[100];
static char pathBD[100];


char *getConfig(char *atributo) {
    static char valorGuardado[100]; // Buffer estático que persiste entre llamadas
    rewind(config); // Reinicia la posición del archivo al principio
    
    char linea[100];
    while ((fgets(linea, sizeof(linea), config)) != NULL) {
        char *atributoEcontrado = strtok(linea, "=");
        char *valor = strtok(NULL, "\n");
        if (strcmp(atributoEcontrado, atributo) == 0) {
            strcpy(valorGuardado, valor); // Copia a buffer seguro
            printf("Atributo encontrado, valor: %s\n", valorGuardado);
            return valorGuardado;
        }
    }
    printf("Error: Atributo de configuracion %s, no encontrado\n", atributo);
    return NULL;
}


void cargarPathFicheros(){

    FILE *fileConfig = fopen(pathConfig, "r");
    if (fileConfig == NULL)
    {
        printf("Error: No se ha podido cargar el fichero de configuracion, ruta: %s", pathConfig);
        return;
    }
    
    config = fileConfig;

    strcpy(pathAccesoCuenta, getConfig("pathAccesoCuenta"));
    strcpy(pathCuenta, getConfig("pathCuenta"));
    strcpy(pathTarjeta, getConfig("pathTarjeta"));
    strcpy(pathTransaccion, getConfig("pathTransaccion"));
    strcpy(pathUsuario, getConfig("pathUsuario"));
    strcpy(pathBD, getConfig("pathBD"));

    printf("Transacciones config: %s", pathTransaccion);


    fclose(fileConfig);


}

char *getPathAccesoCuenta(){
    return pathAccesoCuenta;
}
char *getPathCuenta(){
    return pathCuenta;
}
char *getPathTarjeta(){
    return pathTarjeta;
}
char *getPathTransaccion(){
    return pathTransaccion;
}
char *getPathUsuario(){
    return pathUsuario;
}
char *getPathBD(){
    return pathBD;
}
