#include "leerData.h"
#include "bd.h"
#include "config.h"
#include <string.h>
int main(int argc, char **argv){
    cargarPathFicheros();
    abrirBD();

    if (argc > 1 && (strcmp(argv[1], "reset") == 0))
    {
        borrarBD();
        leerUsuarios();
        leerAcceso();
        leerCuentas();
        leerTarjetas();
        leerTransacciones();
        
    }
    
    
}