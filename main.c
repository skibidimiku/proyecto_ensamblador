#include <stdio.h>
#include <stdlib.h>

#include "juego.h"
#include "mapas.h"

void generar_pixel_art(int *matriz,
                       char *salida,
                       int filas,
                       int columnas);

int main()
{
    int opcion;
    int *mapaSeleccionado;
    char salida[TAM_SALIDA];

    system("chcp 437 > nul");

    opcion = mostrarMenu();

    switch(opcion)
    {
        case 1:
            mapaSeleccionado = &nivel1[0][0];
            break;

        case 2:
            mapaSeleccionado = &nivel2[0][0];
            break;

        case 3:
            mapaSeleccionado = &nivel3[0][0];
            break;

        default:
            printf("Nivel invalido.\n");
            return 1;
    }

    generar_pixel_art(
        mapaSeleccionado,
        salida,
        FILAS,
        COLUMNAS
    );

    system("cls");

    printf("Nivel %d\n\n", opcion);

    imprimirColor(salida);

    printf("\n\n");

    system("pause");

    return 0;
}