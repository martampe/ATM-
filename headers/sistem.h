#ifndef SISTEMA_H
#define SISTEMA_H

#ifdef __linux__
    #define SO "Linux"
    #define CLEAR_COMMAND "clear"
#elif _WIN32
    #define SO "Windows"
    #define CLEAR_COMMAND "cls"
#endif

void clearScreen();

#endif