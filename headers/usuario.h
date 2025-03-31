typedef struct 
{
    //dni, nombre, apellido, fecha_nac, email, tlfno, password, pregunta_seguridad, respuesta_seguridad, dir
    char dni[10];
    char nombre [20];
    char apellidos [40];
    char fechaNac[20];
    char email[50];
    char telefono[15];
    char password[20];
    char pregunta_seguridad[100];
    char respuesta_seguridad[100];
    char dir [50];
    
}Usuario;
