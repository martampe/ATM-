#include "usuarioHandler.h"
#include "stdlib.h"

static Usuario *usuarioActual = NULL;

Usuario *getUsuarioActual(){
    return usuarioActual;
}
void setUsuarioActual(Usuario *usuario){
    usuarioActual = usuario;
}

void liberarUsuario(){
    free(usuarioActual);
}
