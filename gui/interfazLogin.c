#include <string.h>
#include <stdio.h>

void mostrarInterfaz(void){
    int seleccion;

    do{
      printf("¡Bienvenido a la App!\nIngrese su usuario y contraseña");
      printf("[1] Iniciar sesión\n[2] Registrarse\n[3] Salir");
      scanf("%d", &seleccion);      // Leer la opción

      switch (seleccion)
      {
      case 1:
        break;
        case 2:

        case 3:
        printf("Saliendo del programa...\n");
                break;
      default:
        printf("Opción no válida. Inténtelo de nuevo.\n");
      }

    } while (seleccion =! 3);
        
}

