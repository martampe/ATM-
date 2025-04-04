#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static FILE *config = NULL;
static char *pathConfig = "resources/config/config.txt";
static char pathAccesoCuenta[30];
static char pathCuenta[30];
static char pathTarjeta[30];
static char pathTransaccion[30];
static char pathUsuario[30];
static char pathBD[30];


char *getConfig(char *atributo){

    char linea[100];

    while ((fgets(linea, sizeof(linea), config)) != NULL)
    {
        char *atributoEcontrado = strtok(linea, "=");
        char *valor = strtok(NULL, "\n");

        if (strcmp(atributoEcontrado, atributo) == 0)
        {
            printf("Atributo encontrado, valor: %s\n", valor);
            return valor;
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
