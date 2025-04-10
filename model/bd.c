#include <stdio.h>
#include "bd.h"
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include <tarjeta.h>
#include "usuarioHandler.h"
#include <time.h>
#include "leerConsola.h"

static sqlite3* dbHandler = NULL;

// Abrir BD
void abrirBD(){
    char *pathBD = getPathBD();
    sqlite3 *db;
    int comprobante = sqlite3_open(pathBD, &db); //ASEGURAR LA RUTA

    if (comprobante != SQLITE_OK){ //Comprobar sqlite OK
        printf("No se ha podido abrir a BD.");  // estaria bien que saliese en formato error
    return;
    }

    dbHandler = db;

}

int borrarBD(){
    sqlite3_stmt *stmt;

    char *sql = "DELETE FROM Transaccion;";
    if (sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL)) return -1;
    if((sqlite3_step(stmt)) != SQLITE_DONE) return -1;
    sqlite3_reset(stmt);

    sql = "DELETE FROM Tarjeta;";
    if (sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL)) return -1;
    if((sqlite3_step(stmt)) != SQLITE_DONE) return -1;
    sqlite3_reset(stmt);

    sql = "DELETE FROM AccesoUsCuenta;";
    if (sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL)) return -1;
    if((sqlite3_step(stmt)) != SQLITE_DONE) return -1;
    sqlite3_reset(stmt);

    sql = "DELETE FROM Cuenta;";
    if (sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL)) return -1;
    if((sqlite3_step(stmt)) != SQLITE_DONE) return -1;
    sqlite3_reset(stmt);

    sql = "DELETE FROM Usuario;";
    if (sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL)) return -1;
    if((sqlite3_step(stmt)) != SQLITE_DONE) return -1;
    sqlite3_reset(stmt);
    
    
    

}

/*
void cargarAccesoUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "SELECT numCuenta FROM ACCESOUSCUENTA WHERE dni = ?;";

    // Realizar la consulta
    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);

    if (rt != SQLITE_OK){
        sqlite3_finalize(stmt);
        return;
    }
    
    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);
    
    usuario->cuentasDisp = calloc(1, sizeof(CuentasDisponibles));

    //Hay al menos 1 cuenta
    CuentasDisponibles *disponibles = usuario->cuentasDisp;
    disponibles->numCuentas = 0; //inicializamos en 0
    disponibles->cuentas = NULL; //reservamos para una

    while ((rt = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        //incrementar num Cuentas
        disponibles->numCuentas++;
        Cuenta **temp = realloc(disponibles->cuentas, disponibles->numCuentas * sizeof(Cuenta)); //Redimensionar
        disponibles->cuentas = temp; //reasignar nueva ubicacion memoria
        char *numCuenta = ((char*) sqlite3_column_text(stmt, 0)); //obetener
        disponibles->cuentas[disponibles->numCuentas -1] = calloc(1, sizeof(Cuenta)); //reservar cuenta
        strcpy(disponibles->cuentas[disponibles->numCuentas - 1]->numCuenta, numCuenta); //copiar numCuenta

    }
    
    sqlite3_finalize(stmt);
}
    
*/

int contarTarjetas(const char *numCuenta) {
    sqlite3_stmt *countStmt;
    int count = 0;
    
    char *sql = "SELECT COUNT(*) FROM Tarjeta WHERE numCuenta = ?;";
    if (sqlite3_prepare_v2(dbHandler, sql, -1, &countStmt, NULL) != SQLITE_OK) {
        return -1;
    }
    
    sqlite3_bind_text(countStmt, 1, numCuenta, -1, SQLITE_STATIC);
    
    if (sqlite3_step(countStmt) == SQLITE_ROW) {
        count = sqlite3_column_int(countStmt, 0);
    }
    
    sqlite3_finalize(countStmt);
    return count;
}

int asignarTarjetas(Cuenta *cuenta) {
    sqlite3_stmt *stmt;
    char *sql = "SELECT numTarjeta FROM Tarjeta WHERE numCuenta = ?;";
    
    // Primero contar las tarjetas
    int numTarj = contarTarjetas(cuenta->numCuenta);
    if (numTarj <= 0) return numTarj;
  
    // Asignar memoria para las tarjetas
    cuenta->numTarjetasDisp = numTarj;
    cuenta->tarjetasDisp = calloc(numTarj, sizeof(Tarjeta));
    
    // Preparar consulta para obtener datos
    if (sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la consulta");
        return -1;
    }
    
    sqlite3_bind_text(stmt, 1, cuenta->numCuenta, -1, SQLITE_STATIC);
    
    int idx = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && idx < numTarj) {
        Tarjeta tarjeta;
        const char *numTarj = sqlite3_column_text(stmt, 0);
        strcpy(tarjeta.numTarjeta, (const char *)numTarj);
        cuenta->tarjetasDisp[idx] = tarjeta;
        idx++;
    }
    
    sqlite3_finalize(stmt);
    return idx;  // Devuelve número real de tarjetas cargadas
}


int contarCuentas(const char *dni, int password) {
    sqlite3_stmt *countStmt;
    int count = 0;
    
    char *sql = "SELECT COUNT(*) FROM Usuario u, AccesoUsCuenta a WHERE u.dni = ? AND u.password = ? AND u.dni = a.dni;";
    if (sqlite3_prepare_v2(dbHandler, sql, -1, &countStmt, NULL) != SQLITE_OK) {
        printf("Error: al preparar el statement para contar cuentas\n");
        return -1;
    }
    
    sqlite3_bind_text(countStmt, 1, dni, -1, SQLITE_STATIC);
    sqlite3_bind_int(countStmt, 2, password);
    
    if (sqlite3_step(countStmt) == SQLITE_ROW) {
        count = sqlite3_column_int(countStmt, 0);
    }
    
    sqlite3_finalize(countStmt);
    return count;
}

Usuario *cargarUsuario(const char *dni, int password) {
    // Primero contar cuántas cuentas tiene el usuario
    int numCuentas = contarCuentas(dni, password);
    if (numCuentas <= 0) {
        printf("No se ha encontrado ninguna cuenta disponible o error en la consulta\n");
        return NULL;
    }
    
    // Crear el usuario y asignar memoria para las cuentas
    Usuario *usuario = calloc(1, sizeof(Usuario));
    if (!usuario) {
        printf("Error: No se pudo asignar memoria para el usuario\n");
        return NULL;
    }
    
    usuario->cuentasDisp = calloc(numCuentas, sizeof(Cuenta));
    if (!usuario->cuentasDisp) {
        printf("Error: No se pudo asignar memoria para las cuentas\n");
        free(usuario);
        return NULL;
    }
    
    usuario->numCuentasDisp = numCuentas;
    
    // Crear el statement para obtener los números de cuenta
    sqlite3_stmt *stmt;
    char *sql = "SELECT a.numCuenta FROM Usuario u, AccesoUsCuenta a WHERE u.dni = ? AND u.password = ? AND u.dni = a.dni;";
    
    if (sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error: al preparar el statement\n");
        free(usuario->cuentasDisp);
        free(usuario);
        return NULL;
    }
    
    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, password);
    
    int idx = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && idx < numCuentas) {
        Cuenta cuenta;
        const unsigned char *numCuenta = sqlite3_column_text(stmt, 0);
        
        // Verificar que el número de cuenta no es NULL
        if (numCuenta) {
            // Asegurar que no hay desbordamiento de buffer
            strncpy(cuenta.numCuenta, (const char*)numCuenta, sizeof(cuenta.numCuenta) - 1);
            cuenta.numCuenta[sizeof(cuenta.numCuenta) - 1] = '\0';  // Garantizar terminación
            
            // Asignar tarjetas a esta cuenta
            int rc = asignarTarjetas(&cuenta);
            if (rc == -1) {
                printf("Error al cargar las tarjetas en la cuenta\n");
                // Continuar con otras cuentas a pesar del error
            }
            double saldo = consultarSaldo(cuenta.numCuenta);
            if (saldo != -1){
                cuenta.saldo = saldo;
            }
            usuario->cuentasDisp[idx] = cuenta;
            idx++;
            
        }

        
        
        
    }
    
    // Actualizar el número real de cuentas cargadas
    if (idx < numCuentas) {
        printf("Advertencia: Se cargaron menos cuentas (%d) de las esperadas (%d)\n", idx, numCuentas);
        usuario->numCuentasDisp = idx;
    }
    
    sqlite3_finalize(stmt);
    
    // Si no se cargó ninguna cuenta, liberar memoria y devolver NULL
    if (idx == 0) {
        printf("Error: No se pudo cargar ninguna cuenta\n");
        free(usuario->cuentasDisp);
        free(usuario);
        return NULL;
    }
    
    return usuario;
}


// Hay que separar update y guardar por que los binds son diferentes
void actualizarUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "UPDATE USUARIO SET nombre = ?, apellidos = ?, fechaNac = ?, email = ?, telefono = ?, pregunta_seguridad = ?, respuesta_seguridad = ?, dir = ? WHERE dni = ? AND password = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql,-1, &stmt, NULL);
    if (rt != SQLITE_OK){
        sqlite3_finalize(stmt);
        return;
    }
    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, usuario->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->apellidos, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->fechaNac, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, usuario->telefono, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, usuario->pregunta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, usuario->respuesta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, usuario->dir, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, usuario->dni, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 10, usuario->password);




    // Ejecutarlo para actualizar los datos
    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {     // comprobar que se ha hecho correctamente
        printf("Error actualizar usuario: %s\n", sqlite3_errmsg(dbHandler));
        
    }else{
        printf("Usuario actualizar correctamente.\n");
    } 

    // Liberar memoria del statement
    sqlite3_finalize(stmt);
    return;
    
}

void guardarUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO USUARIO VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL); //No devuelve filas, devuelve un estado, OK || ERROR
    if(rt != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return;
    }
    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->apellidos, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->fechaNac, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, usuario->email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, usuario->telefono, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, usuario->password);
    sqlite3_bind_text(stmt, 8, usuario->pregunta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, usuario->respuesta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, usuario->dir, -1, SQLITE_STATIC);
   


    // Ejecutarlo para actualizar los datos
    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {     // comprobar que se ha hecho correctamente
        printf("Error insertado usuarios: %s\n", sqlite3_errmsg(dbHandler));
    }else{
        printf("Usuarios insertado correctamente. Filas: %d\n", sqlite3_changes(dbHandler));
    } 

    // Liberar memoria del statement
    sqlite3_finalize(stmt);

}



// TABLA ACCESO_US
void guardarAccesoUsuario(char *dni, char *numCuenta){
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO AccesoUsCuenta VALUES (?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);
    if(rt != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, numCuenta, -1, SQLITE_STATIC);

    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {     // comprobar que se ha hecho correctamente
        printf("Error actualizando usuario: %s\n", sqlite3_errmsg(dbHandler));
    }else {
        printf("Acceso guardado correctamente.\n");
    }

    // Liberar memoria del statement
    sqlite3_finalize(stmt);
}

/*
void cargarAccesoUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "SELECT numCuenta FROM ACCESOUSCUENTA WHERE dni = ?;";

    // Realizar la consulta
    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);

    if (rt != SQLITE_OK) return;
   
    
    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);
    
    usuario->cuentasDisp = calloc(1, sizeof(CuentasDisponibles));

    //Hay al menos 1 cuenta
    CuentasDisponibles *disponibles = usuario->cuentasDisp;
    disponibles->numCuentas = 0; //inicializamos en 0
    disponibles->cuentas = NULL; //reservamos para una

    while ((rt = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        //incrementar num Cuentas
        disponibles->numCuentas++;
        Cuenta **temp = realloc(disponibles->cuentas, disponibles->numCuentas * sizeof(Cuenta)); //Redimensionar
        disponibles->cuentas = temp; //reasignar nueva ubicacion memoria
        char *numCuenta = ((char*) sqlite3_column_text(stmt, 0)); //obetener
        disponibles->cuentas[disponibles->numCuentas -1] = calloc(1, sizeof(Cuenta)); //reservar cuenta
        strcpy(disponibles->cuentas[disponibles->numCuentas - 1]->numCuenta, numCuenta); //copiar numCuenta

    }
    
    sqlite3_finalize(stmt);
}

*/


// TABLA CUENTAS
// Cargar cuenta desde la BD
Cuenta* cargarCuenta(const char *numCuenta) {

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM CUENTA WHERE numCuenta = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        sqlite3_finalize(stmt);
        printf(" Error en consulta SQL: %s\n", sqlite3_errmsg(dbHandler));
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, numCuenta, -1, SQLITE_STATIC);

    Cuenta *cuenta = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cuenta = (Cuenta*)malloc(sizeof(Cuenta));
        if (cuenta == NULL) {
            printf(" Error al asignar memoria para la cuenta.\n");
            sqlite3_finalize(stmt);
            return NULL;
        }

        // Extraer datos de la consulta, IMPORTANTE, COMPROBAR TIPOS DE DATOS
        strcpy(cuenta->numCuenta, (const char*)sqlite3_column_text(stmt, 0));
        cuenta->saldo = sqlite3_column_double(stmt, 1);
        cuenta->tipo = sqlite3_column_int(stmt, 2);
        strcpy(cuenta->fechaCreacion, (const char*)sqlite3_column_text(stmt, 3));
        cuenta->estado = sqlite3_column_int(stmt, 4);
        strcpy(cuenta->dniTitular, (const char*)sqlite3_column_text(stmt, 5));
        int rt = asignarTarjetas(cuenta);
        
    }

    sqlite3_finalize(stmt);
    return cuenta;
}


void guardarCuenta(Cuenta *cuenta){
    if (cuenta == NULL) return;

    char numCuenta[25];
    double saldo;
    int tipo;
    char fechaCreacion[11];
    int estado;
    char dniTitular[10];

    sqlite3_stmt *stmt;
    const char *sql = 
        "INSERT INTO CUENTA VALUES (?, ?, ?, ?, ?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        sqlite3_finalize(stmt);
        printf("Error preparando la consulta: %s\n", sqlite3_errmsg(dbHandler));
        return;
    }

    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, cuenta->numCuenta, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, cuenta->saldo);
    sqlite3_bind_int(stmt, 3, cuenta->tipo);
    sqlite3_bind_text(stmt, 4, cuenta->fechaCreacion, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, cuenta->estado);
    sqlite3_bind_text(stmt, 6, cuenta->dniTitular, -1, SQLITE_STATIC);

    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {
        printf("Error al insertar cuenta: %s\n", sqlite3_errmsg(dbHandler));
    } else {
        printf("Cuenta insertada correctamente.\n");
    }

    sqlite3_finalize(stmt);
}

// Guardar cambios en la cuenta
/*
int actualizarCuenta(Cuenta *cuenta) {
    if (cuenta == NULL) return;

    sqlite3_stmt *stmt;
    const char *sql = 
        "UPDATE CUENTA SET saldo = ?, tipo = ?, fechaCreacion = ?, estado = ?, dniTitular = ? WHERE numCuenta = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        printf("Error preparando la consulta: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return 1;
    }

    // Asignar valores a los parámetros `?`
    sqlite3_bind_double(stmt, 1, cuenta->saldo);
    sqlite3_bind_int(stmt, 2, cuenta->tipo);
    sqlite3_bind_text(stmt, 3, cuenta->fechaCreacion, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, cuenta->estado);
    sqlite3_bind_text(stmt, 5, cuenta->dniTitular, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, cuenta->numCuenta, -1, SQLITE_STATIC);

    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {
        printf("Error actualizando cuenta: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return 1;
    } else {
        printf("Cuenta actualizada correctamente.\n");
    }

    sqlite3_finalize(stmt);
}
*/

// TABLA TRASNFERENCIA
int contarTransaccionesCuenta(char* numCuenta){
    sqlite3_stmt *stmt;
    int contador = 0;

    char *sql = "SELECT * FROM Transaccion WHERE numCuentaOrig = ? OR numCuentaDest = ?";
   
    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    
    if (rt != SQLITE_OK) {
        printf(" Error en consulta SQL: %s\n", sqlite3_errmsg(dbHandler));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, numCuenta, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, numCuenta, -1, SQLITE_STATIC);

    while ((rt = sqlite3_step(stmt)) == SQLITE_ROW){
        contador++;
    }

    sqlite3_finalize(stmt);
    
    return contador;
}

int cargarTransaccionesCuenta(char* numCuenta){
    // FALTA LIBERAR MEMORIA AAAAAAAA
    sqlite3_stmt *stmt;

    int contador = contarTransaccionesCuenta(numCuenta);
    if (contador == 0)
    {
        printf("Error: no hay transacciones para visualizar\n");
        return -1;
    }
    
    Transaccion *transacciones = malloc(sizeof(Transaccion) * contador);

    if (!transacciones)
    {
        printf("Error: al reservar memoria\n");
        return -1;
    }

    getUsuarioActual()->numeroTransacciones = contador;
    

    char *sql = "SELECT * FROM Transaccion WHERE numCuentaOrig = ? OR numCuentaDest = ? ORDER BY fecha DESC";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    
    if (rt != SQLITE_OK) {
        printf(" Error en consulta SQL: %s\n", sqlite3_errmsg(dbHandler));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, numCuenta, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, numCuenta, -1, SQLITE_STATIC);

    int ultimoElemento = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        
        // Extraer datos con verificación
        Transaccion t;
        t.id = sqlite3_column_int(stmt, 0);
        
        const char* temp_text;
        
        // Manejo seguro de las cadenas
        temp_text = (const char*)sqlite3_column_text(stmt, 1);
        strncpy(t.numCuentaOrigen, (temp_text != NULL) ? temp_text : "", sizeof(t.numCuentaOrigen) - 1);
        t.numCuentaOrigen[sizeof(t.numCuentaOrigen) - 1] = '\0';
        
        temp_text = (const char*)sqlite3_column_text(stmt, 2);
        strncpy(t.numeroTarjetaOrigen, (temp_text != NULL) ? temp_text : "", sizeof(t.numeroTarjetaOrigen) - 1);
        t.numeroTarjetaOrigen[sizeof(t.numeroTarjetaOrigen) - 1] = '\0';
        
        temp_text = (const char*)sqlite3_column_text(stmt, 3);
        strncpy(t.numCuentaDestino, (temp_text != NULL) ? temp_text : "", sizeof(t.numCuentaDestino) - 1);
        t.numCuentaDestino[sizeof(t.numCuentaDestino) - 1] = '\0';
        
        t.cantidad = sqlite3_column_double(stmt, 4);
        
        temp_text = (const char*)sqlite3_column_text(stmt, 5);
        strncpy(t.fecha, (temp_text != NULL) ? temp_text : "", sizeof(t.fecha) - 1);
        t.fecha[sizeof(t.fecha) - 1] = '\0';
        
        temp_text = (const char*)sqlite3_column_text(stmt, 6);
        strncpy(t.dirATM, (temp_text != NULL) ? temp_text : "", sizeof(t.dirATM) - 1);
        t.dirATM[sizeof(t.dirATM) - 1] = '\0';
        
        t.estado = sqlite3_column_int(stmt, 7);
        t.tipo = sqlite3_column_int(stmt, 8);
        
        transacciones[ultimoElemento] = t;
        ultimoElemento++;
            
        
            
    }

    getUsuarioActual()->transaciones = transacciones;


    sqlite3_finalize(stmt);
    return 0;
}

double consultarSaldo(const char *numCuenta){
    sqlite3_stmt *stmt;

    char *sql = "SELECT saldo from Cuenta where numCuenta = ?;";

    sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, numCuenta, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double saldo = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);

        return saldo;
    } else {
        sqlite3_finalize(stmt);
        return -1; // O cualquier otro valor que indique error
    }
    
}
/*

	"numCuentaOrig"	TEXT,
	"numTarjetaOrig"	TEXT,
	"numCuentaDest"	TEXT,
	"cant"	REAL,
	"fecha"	TEXT,
	"dirATM"	TEXT,
	"estado"	INTEGER,
	"tipo"	INTEGER,

*/    

int registrarIngreso(const char *numCuentaDest, double cant){
    sqlite3_stmt *stmt;

    char *sql = "INSERT INTO Transaccion (numCuentaDest, cant, fecha, estado, tipo) VALUES (?, ?, ?, ?, ?);";

    if(sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL) != SQLITE_OK){
        printf("Error al crear al preparar la consulta\n");
        return -1;
    }
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    char fecha[11]; // Espacio para "yyyy-mm-dd" + caracter nulo
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tm_info);

    sqlite3_bind_text(stmt, 1, numCuentaDest, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, cant);
    sqlite3_bind_text(stmt, 3, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, 1);
    sqlite3_bind_int(stmt, 5, 4);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Error al ingresar el retiro\n");
        return -1;
    }


    sqlite3_finalize(stmt);
    return 0;
    
}

int registrarRetiro(const char *numCuentaOrig, double cant){
    sqlite3_stmt *stmt;

    char *sql = "INSERT INTO Transaccion (numCuentaOrig, cant, fecha, estado, tipo) VALUES (?, ?, ?, ?, ?);";

    if(sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL) != SQLITE_OK){
        printf("Error al crear al preparar la consulta: %s\n", sqlite3_errmsg(dbHandler));
        return -1;
    }
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    char fecha[11]; // Espacio para "yyyy-mm-dd" + caracter nulo
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tm_info);

    sqlite3_bind_text(stmt, 1, numCuentaOrig, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, cant);
    sqlite3_bind_text(stmt, 3, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, 1);
    sqlite3_bind_int(stmt, 5, 3);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Error al registrar el retiro\n");
        return -1;
    }


    sqlite3_finalize(stmt);
    return 0;
    
}

int registrarTransaccion(const char *cuentaOrigen, const char *cuentaDestino, double cantidad){
    sqlite3_stmt *stmt;

    char *sql = "INSERT INTO Transaccion (numCuentaOrig, numCuentaDest, cant, fecha, estado, tipo) VALUES (?, ?, ?, ?, ?, ?);";

    if(sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL) != SQLITE_OK){
        printf("Error al crear al preparar la consulta\n");
        return -1;
    }
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    char fecha[11]; // Espacio para "yyyy-mm-dd" + caracter nulo
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tm_info);

    sqlite3_bind_text(stmt, 1, cuentaOrigen, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, cuentaDestino, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, cantidad);
    sqlite3_bind_text(stmt, 4, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, 1);
    sqlite3_bind_int(stmt, 6, 1);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Error al registrar la transaccion\n");
        return -1;
    }

    printf("Transaccion registrada correctamente\n");

    sqlite3_finalize(stmt);
    return 0;
    

}

int realizarTransferencia(const char *cuentaOrig, const char *cuentaDest, double cantidad){

    sqlite3_stmt *stmt;

    //Actualizar cuenta origen

    double saldoOrig = consultarSaldo(cuentaOrig);
    printf("Saldo original: %.2f, Cantidad: %.2f\n", saldoOrig, cantidad);
    if (saldoOrig < cantidad)
    {
        printf("Error: No se dispone de %.2f euros para tranferir\n", cantidad);
        sqlite3_finalize(stmt);
        return -1;
    }
    
    char *sql = "UPDATE Cuenta set saldo = saldo - ? where numCuenta = ?;";
    sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL);
    sqlite3_bind_double(stmt, 1, cantidad);
    sqlite3_bind_text(stmt, 2, cuentaOrig, -1, SQLITE_STATIC);

    
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Error: No se pudo actualizar la tabla durante la transaccion\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    printf("Cuenta origen actualizada correctamente\n");
    

    //Actualizar cuenta destino

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    sql = "UPDATE Cuenta SET saldo = saldo + ? WHERE numCuenta = ?;";
    int rt = sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL);
    if (rt != SQLITE_OK)
    {
        printf("Error: Al preparar la consulta\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, cantidad);
    sqlite3_bind_text(stmt, 2, cuentaDest, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        printf("Error: No se pudo actualizar la tabla durante la transaccion\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    printf("Cuenta destino actualizada correctamente\n");

    sqlite3_finalize(stmt);

    if ((registrarTransaccion(cuentaOrig, cuentaDest, cantidad)) != 0) return -1;
    
    return 0;
}

int guardarTarjeta(Tarjeta *tarjeta){

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO TARJETA VALUES (?, ?, ?, ?, ?, ?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        printf("Error preparando guardarTarjeta: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, tarjeta->numTarjeta, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tarjeta->fechaExpiracion, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, tarjeta->ccv);
    sqlite3_bind_int(stmt, 4, tarjeta->pin);
    sqlite3_bind_int(stmt, 5, tarjeta->estado);
    sqlite3_bind_text(stmt, 6, tarjeta->numCuenta, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, tarjeta->dniPropietario, -1, SQLITE_STATIC);

    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {
        printf("Error insertando tarjeta: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return 1;
    } else {
        printf("Tarjeta insertada correctamente.\n");
    }

    sqlite3_finalize(stmt);
    return 0;
}



Tarjeta* cargarTarjeta(const char *numTarjeta){
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM TARJETA WHERE numTarjeta = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        printf("Error preparando cargarTarjeta: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, numTarjeta, -1, SQLITE_STATIC);

    Tarjeta *tarjeta = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        tarjeta = (Tarjeta*)malloc(sizeof(Tarjeta));
        strcpy(tarjeta->numTarjeta, (const char*)sqlite3_column_text(stmt, 0));
        strcpy(tarjeta->fechaExpiracion, (const char*)sqlite3_column_text(stmt, 1));
        tarjeta->ccv = sqlite3_column_int(stmt, 2);
        tarjeta->pin = sqlite3_column_int(stmt, 3);
        tarjeta->estado = sqlite3_column_int(stmt, 4);
        strcpy(tarjeta->numCuenta, (const char*)sqlite3_column_text(stmt, 5));
        strcpy(tarjeta->dniPropietario, (const char*)sqlite3_column_text(stmt, 6));
    }

    sqlite3_finalize(stmt);
    return tarjeta;
}


int guardarTransaccion(Transaccion *transaccion){
    if (transaccion == NULL){

        return 1;
    }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO TRANSACCION (numCuentaOrig, numTarjetaOrig, numCuentaDest, cant, fecha, dirATM, estado, tipo)VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        printf("Error preparando guardarTransaccion: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return 1;
    }

     // Comprobar numCuentaOrigen
     if (strcmp(transaccion->numCuentaOrigen, "VACIO") == 0) {
        sqlite3_bind_null(stmt, 1);
    } else {
        sqlite3_bind_text(stmt, 1, transaccion->numCuentaOrigen, -1, SQLITE_STATIC);
    }
    
    // Comprobar numeroTarjetaOrigen
    if (strcmp(transaccion->numeroTarjetaOrigen, "VACIO") == 0) {
        sqlite3_bind_null(stmt, 2);
    } else {
        sqlite3_bind_text(stmt, 2, transaccion->numeroTarjetaOrigen, -1, SQLITE_STATIC);
    }
    
    // Comprobar numCuentaDestino
    if (strcmp(transaccion->numCuentaDestino, "VACIO") == 0) {
        sqlite3_bind_null(stmt, 3);
    } else {
        sqlite3_bind_text(stmt, 3, transaccion->numCuentaDestino, -1, SQLITE_STATIC);
    }
    
    // Para cantidad no necesitamos comprobar "VACIO" ya que es un número
    sqlite3_bind_double(stmt, 4, transaccion->cantidad);
    
    // Comprobar fecha
    if (strcmp(transaccion->fecha, "VACIO") == 0) {
        sqlite3_bind_null(stmt, 5);
    } else {
        sqlite3_bind_text(stmt, 5, transaccion->fecha, -1, SQLITE_STATIC);
    }
    
    // Comprobar dirATM
    if (strcmp(transaccion->dirATM, "VACIO") == 0) {
        sqlite3_bind_null(stmt, 6);
    } else {
        sqlite3_bind_text(stmt, 6, transaccion->dirATM, -1, SQLITE_STATIC);
    }
    
    // Para estado y tipo no necesitamos comprobar "VACIO" ya que son números
    sqlite3_bind_double(stmt, 7, transaccion->estado);
    sqlite3_bind_int(stmt, 8, transaccion->tipo);
    
    // Ejecutar la consulta y finalizar el statement (parte que falta en tu código original)
    rt = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rt != SQLITE_DONE) {
        printf("Error ejecutando guardarTransaccion: %s\n", sqlite3_errmsg(dbHandler));
        return 1;
    }
    
    return 0;
}

// Función para ingresar dinero
int ingresarDinero(const char* numCuenta, double cantidad) {
    sqlite3_stmt *stmt;

    if (dbHandler == NULL) {
        printf("Error: No hay conexión a la base de datos.\n");
        return -1;
    }

    if (cantidad <= 0) {
        printf("Cantidad inválida.\n");
        return -1;
    }

    char *sql = "UPDATE Cuenta SET saldo = saldo + ? WHERE numCuenta = ?;";
    if(sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL) != SQLITE_OK){
        printf("Error: Al preparar el statement.\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, cantidad);
    sqlite3_bind_text(stmt, 2, numCuenta, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error al ingresar dinero: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);

    registrarIngreso(numCuenta, cantidad);

    return 0;
}

// Función para retirar dinero
int retirarDinero(const char* numCuenta, double cantidad) {
    sqlite3_stmt *stmt;

    if (dbHandler == NULL) {
        printf("Error: No hay conexión a la base de datos.\n");
        return -1;
    }

    if (cantidad < 0) {
        printf("Cantidad inválida.\n");
        return -1;
    }

    double saldoActual = consultarSaldo((char*)numCuenta);

    if (saldoActual < cantidad) {
        printf("Saldo insuficiente. Tienes: %.2f\n", saldoActual);
        return -1;
    }

    char *sql = "UPDATE Cuenta SET saldo = saldo - ? WHERE numCuenta = ?;";
    sqlite3_prepare(dbHandler, sql, -1, &stmt, NULL);

    sqlite3_bind_double(stmt, 1, cantidad);
    sqlite3_bind_text(stmt, 2, numCuenta, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error al retirar dinero: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    registrarRetiro(numCuenta, cantidad);
    return 0;
}

int registrarUsuario(Usuario usuario) {

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Usuario (dni, nombre, apellidos, fechaNac, email, tlf, password, preguntaRec, respuestaRec, dir) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    int rc;

    if ((sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL)) != SQLITE_OK);
    {
        printf("Error: al hacer el prepared statement\n");
        return -1;
    }
    

    // Asignar los valores a la sentencia preparada
    sqlite3_bind_text(stmt, 1, usuario.dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario.apellidos, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario.fechaNac, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, usuario.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, usuario.telefono, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, usuario.password);
    sqlite3_bind_text(stmt, 8, usuario.pregunta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, usuario.respuesta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, usuario.dir, -1, SQLITE_STATIC);

    // Ejecutar 
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la sentencia SQL: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return -1; 
    }

    sqlite3_finalize(stmt);

    printf("Usuario registrado exitosamente.\n");
    return 0; 

    }
