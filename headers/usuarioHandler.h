#ifndef USUARIO_HANDLER_H
#define USUARIO_HANDLER_H
#include "usuario.h"

Usuario * getUsuarioActual();
void setUsuarioActual(Usuario *usuario);
void liberarUsuario();
#endif