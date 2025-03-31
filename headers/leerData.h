#include "usuario.h"
#include <stdio.h>
#include "transaccion.h"

int contarLineas(FILE *file);
Usuario* leerUsuarios();

Transaccion* leerTransacciones();
void leerAcceso();