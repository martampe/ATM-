#include <stdio.h>
#include "bd.h"
#include "sqlite3.h"
#include "usuario.h"
#include <string.h>
#include <stdlib.h>

static sqlite3* dbHandler = NULL;

// Abrir BD
void abrirBD(){
    sqlite3 *db;
    int comprobante = sqlite3_open("bd.db", &db);

    if (comprobante != SQLITE_OK){ //Comprobar sqlite OK
        printf("No se ha podido abrir a BD.");  // estaria bien que saliese en formato error
        return;
    }

    dbHandler = db;

}

Usuario* cargarUsuario(const char *dni, const char *password){
   // FALTA LIBERAR MEMORIA AAAAAAAAAAAAAAAAAAAAAAAHHHHHHHH
    
    // Crear el statement + La consulta
    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM USUARIO WHERE dni = ? AND password = ?";

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
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);


    Usuario *usuario = NULL;

    // Buscar el usuario ejecutando la consulta (Dios mio donde nos hemos metido)
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        usuario = malloc(sizeof(Usuario));

        // ¿Que hacer si el malloc no va? X_X
        //Si no va, malloc devuelve null, salir con return;
        if(usuario == NULL) return NULL;


    // Tomar los datos del usuario encontrado
    strcpy(usuario->dni, (const char*) sqlite3_column_text(stmt, 0));
    strcpy(usuario->nombre, (const char*) sqlite3_column_text(stmt, 1));
    strcpy(usuario->apellidos,(const char*) sqlite3_column_text(stmt, 2));
    strcpy(usuario->fechaNac, (const char*) sqlite3_column_text(stmt, 3));
    strcpy(usuario->email, (const char*) sqlite3_column_text(stmt, 4));
    strcpy(usuario->telefono, (const char*) sqlite3_column_text(stmt, 5));
    strcpy(usuario->password, (const char*) sqlite3_column_text(stmt, 6));
    strcpy(usuario->pregunta_seguridad, (const char*) sqlite3_column_text(stmt, 7));
    strcpy(usuario->respuesta_seguridad, (const char*) sqlite3_column_text(stmt, 8));
    strcpy(usuario->dir, (const char*) sqlite3_column_text(stmt, 9));

    }

    // Terminar statement
    sqlite3_finalize(stmt);

    return usuario;
}

void actualizarUsuario(Usuario *usuario){
    sqlite3_stmt *stmt;
    char *sql = "UPDATE USUARIO SET nombre = ?, apellidos = ?, fechaNac = ?, email = ?, telefono = ?, pregunta_seguridad = ?, respuesta_seguridad = ?, dir = ? WHERE dni = ? AND password = ?";

    int rt = sqlite3_prepare_v2(dbHandler, sql, -1, &stmt, NULL); //No devuelve filas, devuelve un estado, OK || ERROR
    if(rt != SQLITE_OK) return;

    // Asignar valores a los parámetros `?`
    sqlite3_bind_text(stmt, 1, usuario->dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario->password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->fechaNac, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, usuario->telefono, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, usuario->pregunta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, usuario->respuesta_seguridad, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, usuario->dir, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, usuario->dni, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, usuario->password, -1, SQLITE_STATIC);

    
    // Ejecutarlo para actualizar los datos
    rt = sqlite3_step(stmt);
    if (rt != SQLITE_DONE) {     // comprobar que se ha hecho correctamente
        printf("Error actualizando usuario: %s\n", sqlite3_errmsg(dbHandler));
    } 

    printf("Usuario actualizado correctamente.\n");

    // Liberar memoria del statement
    sqlite3_finalize(stmt);

}