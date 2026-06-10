#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "juego.h"
#include "mapas.h"

int main()
{
    int opcion;
    int *mapaSeleccionado;
    int filaJug, colJug, movLeg;
    int monedasGeneradas = 0;
    int monedasEnMapa = 0;

    char salida[TAM_SALIDA];
    char direccion;

    system("chcp 437 > nul");

    opcion = mostrarMenu();

    switch(opcion){
        case 1: mapaSeleccionado = &nivel1[0][0]; break;

        case 2: mapaSeleccionado = &nivel2[0][0]; break;

        case 3: mapaSeleccionado = &nivel3[0][0];break;

        default:
            printf("Nivel invalido.\n");
            system("pause");
            return 1;
    }

    if(opcion == 2 || opcion == 3){
        monedasGeneradas = generar_cantidad_monedas();

        colocar_monedas(
            mapaSeleccionado,
            FILAS,
            COLUMNAS,
            monedasGeneradas
        );

        monedasEnMapa = contar_monedas(
            mapaSeleccionado,
            FILAS,
            COLUMNAS
        );

    }

    printf("Paso 6\n");

    generar_pixel_art(
        mapaSeleccionado,
        salida,
        FILAS,
        COLUMNAS
    );

    system("cls");

    printf("====================================\n");
    printf("            NIVEL %d\n", opcion);
    printf("====================================\n\n");

    if(opcion == 2 || opcion == 3)
    {
        printf("Monedas generadas: %d\n", monedasGeneradas);
        printf("Monedas encontradas en el mapa: %d\n\n", monedasEnMapa);
    }

    buscarJug(mapaSeleccionado, FILAS, COLUMNAS, &filaJug, &colJug);
    imprimirVentana(mapaSeleccionado, filaJug, colJug);
    
    printf("\nUsa WASD para moverte y Q para salir:");
    scanf(" %c", &direccion);
    direccion = tolower(direccion);

    movLeg = moverJug(mapaSeleccionado, COLUMNAS, &filaJug, &colJug, direccion);
    
    imprimirVentana(mapaSeleccionado, filaJug, colJug);

    while(direccion != 'q'){
        system("cls");

        printf("====================================\n");
        printf("            NIVEL %d\n", opcion);
        printf("====================================\n\n");

        if(opcion == 2 || opcion == 3)
        {
            printf("Monedas generadas: %d\n", monedasGeneradas);
            printf("Monedas encontradas en el mapa: %d\n\n", monedasEnMapa);
        }

        imprimirVentana(mapaSeleccionado, filaJug, colJug);

        printf("\nUsa WASD para moverte y Q para salir:");
        scanf(" %c", &direccion);
        direccion = tolower(direccion);

        movLeg = moverJug(mapaSeleccionado, COLUMNAS, &filaJug, &colJug, direccion);

    }
    printf("\n");

    system("pause");

    return 0;
}