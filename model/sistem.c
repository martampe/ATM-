#include "sistem.h"
#include <stdlib.h>
#include "usuarioHandler.h"
void clearScreen(){
    system(CLEAR_COMMAND);
}

void liberarMemoria(){
    free(getUsuarioActual()->cuentasDisp->tarjetasDisp);
    free(getUsuarioActual()->cuentasDisp);
    free(getUsuarioActual()->transaciones);
    

}