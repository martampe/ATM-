#include "loginInterfaz.h"
#include "leerData.h"
#include "bd.h"
#include "config.h"
int main(int argc, char **argv){
    cargarPathFicheros();
    abrirBD();
    leerUsuarios();
    leerAcceso();
    leerCuentas();
    mostrarLoginInterfaz();
}