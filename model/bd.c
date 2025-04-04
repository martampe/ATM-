#include <stdio.h>
#include "bd.h"
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include "config.h"

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

Usuario* cargarUsuario(const char *dni, int password){
   // FALTA LIBERAR MEMORIA AAAAAAAAAAAAAAAAAAAAAAAHHHHHHHH
    
    // Crear el statement + La consulta
    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM USUARIO WHERE dni = ? AND password = ?;";

    /* sqlite3 *db 
    const char *sql
    int nByte -->   Indica la longitud máxima en bytes a leer del string SQL. Si pones -1,
                    SQLite leerá hasta encontrar el primer carácter nulo (\0), es decir, procesará todo el string.
     
    sqlite3_stmt **ppStmt
    const char **pzTail --> puntero que, si no es NULL, apuntará a la parte de la consulta SQL que no fue procesada. 
   */
   
    int rc = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);

    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, password);


    Usuario *usuario = calloc(1, sizeof(Usuario));
    if (usuario == NULL) exit(1);
    
   

   // Buscar el usuario ejecutando la consulta (Dios mio donde nos hemos metido)
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        usuario->valido = NO;
        return usuario;

    }   

    // Tomar los datos del usuario encontrado
    usuario->valido = YES;
    strcpy(usuario->dni, (const char*) sqlite3_column_text(stmt, 0));
    strcpy(usuario->nombre, (const char*) sqlite3_column_text(stmt, 1));
    strcpy(usuario->apellidos,(const char*) sqlite3_column_text(stmt, 2));
    strcpy(usuario->fechaNac, (const char*) sqlite3_column_text(stmt, 3));
    strcpy(usuario->email, (const char*) sqlite3_column_text(stmt, 4));
    strcpy(usuario->telefono, (const char*) sqlite3_column_text(stmt, 5));
    usuario->password = sqlite3_column_int(stmt, 6);
    strcpy(usuario->pregunta_seguridad, (const char*) sqlite3_column_text(stmt, 7));
    strcpy(usuario->respuesta_seguridad, (const char*) sqlite3_column_text(stmt, 8));
    strcpy(usuario->dir, (const char*) sqlite3_column_text(stmt, 9));

    cargarAccesoUsuario(usuario);
    // Terminar statement
    sqlite3_finalize(stmt);

    return usuario;
}


// Hay que separar update y guardar por que los binds son diferentes
void actualizarUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "UPDATE USUARIO SET nombre = ?, apellidos = ?, fechaNac = ?, email = ?, telefono = ?, pregunta_seguridad = ?, respuesta_seguridad = ?, dir = ? WHERE dni = ? AND password = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql,-1, &stmt, NULL);
    if (rt != SQLITE_OK) return;

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
    
}

void guardarUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO USUARIO VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL); //No devuelve filas, devuelve un estado, OK || ERROR
    if(rt != SQLITE_OK) return;

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

// FUNCIONES CUENTA
// FUNCIONES TARJETA

// FUNCIONES ACCESO_US
void guardarAccesoUsuario(char *dni, char *numCuenta){
    sqlite3_stmt *stmt;
    char *sql = "INSERT INTO ACCESOUSCUENTA VALUES (?, ?);";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL);
    if(rt != SQLITE_OK) return;

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





// Cargar cuenta desde la BD
Cuenta* cargarCuenta(const char *numCuenta) {

    printf("Funcion cargar cuenta %s\n", numCuenta);
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM CUENTA WHERE numCuenta = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
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
void actualizarCuenta(Cuenta *cuenta) {
    if (cuenta == NULL) return;

    sqlite3_stmt *stmt;
    const char *sql = 
        "UPDATE CUENTA SET saldo = ?, tipo = ?, fechaCreacion = ?, estado = ?, dniTitular = ? WHERE numCuenta = ?;";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, 0);
    if (rt != SQLITE_OK) {
        printf("Error preparando la consulta: %s\n", sqlite3_errmsg(dbHandler));
        return;
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
    } else {
        printf("Cuenta actualizada correctamente.\n");
    }

    sqlite3_finalize(stmt);
}