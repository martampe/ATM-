#include "loginInterfaz.h"
#include "leerData.h"
#include "bd.h"

int main(int argc, char **argv){
    abrirBD();
    leerCuentas();
    mostrarLoginInterfaz();
}