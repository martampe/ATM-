void abrirBD();
Usuario* cargarUsuario(const char *dni, const char *password);
void guardarUsuario(Usuario *usuario, int decision);
void guardarAccesoUsuario(Usuario *usuario, Cuenta *cuenta);
int cargarAccesoUsuario(Usuario *usuario, Cuenta *cuenta);