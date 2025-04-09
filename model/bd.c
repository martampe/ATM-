#include <stdio.h>
#include "bd.h"
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include <tarjeta.h>
#include "usuarioHandler.h"

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

char** cargarUsuario(const char *dni, int password, int *numCuentas){
   // FALTA LIBERAR MEMORIA AAAAAAAAAAAAAAAAAAAAAAAHHHHHHHH
    
    // Crear el statement + La consulta
    sqlite3_stmt *stmt = NULL;
    char **cuentas = NULL;
    *numCuentas = 0;
    int capacidad = 4; // Empezamos con capacidad inicial
    char *sql = "SELECT numCuenta FROM Usuario u, AccesoUsCuenta a WHERE u.dni = ? AND u.password = ? and u.dni = a.dni;";

    cuentas = calloc(capacidad, sizeof(char*));
    if (!cuentas)
    {
        return NULL;
    }
    

    
    if((sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL)) != SQLITE_OK){
        printf("Error: al preparar el statement\n");
        free(cuentas);
        return NULL;
    }

    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, password);

    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        if (*numCuentas >= capacidad)
        {
            capacidad *= 2;
            char **temp = realloc(cuentas, sizeof(char*) * capacidad);

            if (!temp)
            {
                for (int i = 0; i < *numCuentas; i++)
                {
                    free(cuentas[i]);
                }
                free(cuentas);
                sqlite3_finalize(stmt);
                return NULL;
                
            }

            cuentas = temp;
            
        }

        const char *numCuentaActual = (const char*)sqlite3_column_text(stmt, 0);
        int longitud = strlen(numCuentaActual);
        cuentas[*numCuentas] = calloc(longitud + 1, sizeof(char));
        if (cuentas[*numCuentas]) {
            strcpy(cuentas[*numCuentas], numCuentaActual);
            (*numCuentas)++;
        }
    }

    if (*numCuentas == 0)
    {
        free(cuentas);
        cuentas = NULL;
    } else if(*numCuentas < capacidad){
        char **temp = realloc(cuentas, (*numCuentas) * sizeof(char*));
        if (temp)
        {
            cuentas = temp;
        }
        
    }

    sqlite3_finalize(stmt);

    return cuentas;
    
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

    printf("Funcion cargar cuenta %s\n", numCuenta);
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
        printf("Cuenta encontrada\n");
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

    printf("Transacciones contadas correctamente");
    sqlite3_finalize(stmt);
    
    return contador;
}

int mostrarTransaccionesCuenta(char* numCuenta){
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
    

    char *sql = "SELECT * FROM Transaccion WHERE numCuentaOrig = ? OR numCuentaDest = ?";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    
    if (rt != SQLITE_OK) {
        printf(" Error en consulta SQL: %s\n", sqlite3_errmsg(dbHandler));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, numCuenta, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, numCuenta, -1, SQLITE_STATIC);

    int ultimoElemento = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Transaccion encontrada\n");

        // Extraer datos de la consulta, IMPORTANTE, COMPROBAR TIPOS DE DATOS
        Transaccion t;
        t.id = sqlite3_column_int(stmt, 0);
        strcpy(t.numCuentaOrigen, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(t.numeroTarjetaOrigen, (const char*)sqlite3_column_text(stmt, 2));
        strcpy(t.numCuentaDestino, (const char*)sqlite3_column_text(stmt, 3));
        t.cantidad = sqlite3_column_double(stmt, 4);
        strcpy(t.fecha, (const char*)sqlite3_column_text(stmt, 5));
        strcpy(t.dirATM, (const char*)sqlite3_column_text(stmt, 6));
        t.estado = sqlite3_column_int(stmt, 7);
        t.tipo = sqlite3_column_int(stmt, 8);

        transacciones[ultimoElemento] = t;
        ultimoElemento ++;

        printf("ID: %d | Cuenta origen: %s | Tarjeta origen: %s | Cuenta destino: %s | Cantidad: %i | Fecha: %s | Direccion ATM: %s | Estado: %d | Tipo: %d |\n",
            t.id, t.numCuentaOrigen, t.numeroTarjetaOrigen, t.numCuentaDestino, t.cantidad, t.fecha, t.dirATM, t.estado, t.tipo);

    }

    getUsuarioActual()->transaciones = transacciones;


    printf("Transacciones cargadas correctamente.");
    sqlite3_finalize(stmt);
    return 0;
}

double consultarSaldo(char *numCuenta, sqlite3_stmt *stmt){
    char *sql = "SELECT saldo from Cuenta where numCuenta = ?;";

    sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, numCuenta, -1, SQLITE_STATIC);

    if ((sqlite3_step(stmt)) == SQLITE_DONE)
    {
        return -1;
    }

    double saldo = sqlite3_column_double(stmt, 0);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
    return saldo;
    
}

int realizarTransferencia(char *cuentaOrig, char *cuentaDest, double cantidad){

    sqlite3_stmt *stmt;

    

    //Actualizar cuenta origen

    double saldoOrig = consultarSaldo(cuentaOrig, stmt);
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


    /*// Una vez actualizado el saldo de la cuenta, añadimos la fila a la tabla transaccion
    sql = "INSERT INTO Transaccion (numCuentaOrig, numCuentaDest, cantidad, fecha) VALUES (?, ?, ?, datetime('now'));";

    rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);
    if (rt != SQLITE_OK) {
        printf("Error al preparar la inserción de la transacción: %s\n", sqlite3_errmsg(dbHandler));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, cuentaOrig, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, cuentaDest, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, cantidad);
    // Los valores `fecha`, `dirATM`, `estado`, `tipo` están quemados por ahora

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error al insertar transacción\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    printf("Transferencia realizada\n");*/

    sqlite3_finalize(stmt);

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
    const char *sql = "INSERT INTO TRANSACCION VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        printf("Error preparando guardarTransaccion: %s\n", sqlite3_errmsg(dbHandler));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, transaccion-> id);
    sqlite3_bind_text(stmt, 2, transaccion->numCuentaOrigen, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, transaccion->numeroTarjetaOrigen, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, transaccion->numCuentaDestino, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 5, transaccion->cantidad);
    sqlite3_bind_text(stmt, 6, transaccion->fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, transaccion->dirATM, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, transaccion->estado);
    sqlite3_bind_int(stmt, 9, transaccion->tipo);



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

    printf("Dinero ingresado correctamente.\n");
    sqlite3_finalize(stmt);

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

    double saldoActual = consultarSaldo((char*)numCuenta, stmt);

    if (saldoActual < cantidad) {
        printf("Saldo insuficiente. Tienes: %.2f\n", saldoActual);
        sqlite3_finalize(stmt);
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

    printf("Dinero retirado correctamente.\n");
    sqlite3_finalize(stmt);
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
