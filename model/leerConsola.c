#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "leerConsola.h"

int eliminarSaltoLinea(char *linea){

    if (strchr(linea, '\n') != NULL)
    {
        linea[strcspn(linea, "\n")] = '\0';
        return 0;
    }
    return 1;
    
}

void limpiarBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

int leerInteger(char *numero){

    if (strchr(numero, '\n') != NULL)
    {
        numero[strcspn(numero, "\n")] = '\0';
    } else {
        printf("Error: buffer desbordado\n");
        limpiarBuffer();
        return -1; 
    }
    

    errno = 0;
    char *idx_fin;

    long resultado = strtol(numero, &idx_fin, 10);

    if (errno == ERANGE && (resultado > LONG_MAX || resultado < LONG_MIN))
    {
        //printf("Error: numero introducido fuera del rango de long\n");
        return -1;
    } else if (numero == idx_fin){
        //printf("Error: ningun caracter introducido valido para castear\n");
        return -1;
    } else if(*idx_fin != '\0'){
        //printf("Error: no se ha podido castear todos los caracteres: %s\n",idx_fin);
        return -1;
    } else if(resultado > INT_MAX || resultado < INT_MIN){
        //printf("Error: numero introducido fuera del rango de integer\n");
        return -1;
    } else {
        return (int) resultado;
    }
    

}