#include <stdio.h>
#include <windows.h>
#include "juego.h"

void imprimirColor(const char *salida)
{
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; salida[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)salida[i];

        if(c == 219)
            SetConsoleTextAttribute(consola, 10);

        else if(c == '.')
            SetConsoleTextAttribute(consola, 8);

        else
            SetConsoleTextAttribute(consola, 7);

        putchar(c);
    }

    SetConsoleTextAttribute(consola, 7);
}

int mostrarMenu()
{
    int opcion;

    printf("====================================\n");
    printf("          LABERINTOS\n");
    printf("====================================\n");
    printf("1. Nivel 1\n");
    printf("2. Nivel 2\n");
    printf("3. Nivel 3\n");
    printf("\nSelecciona un nivel: ");

    scanf("%d", &opcion);

    return opcion;
}