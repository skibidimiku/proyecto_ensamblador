#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "juego.h"
#include "mapas.h"

int main(){
    int opcion;
    int *mapaSeleccionado;
    int filaJug, colJug, mondJug = 0, pasos = 0, movLeg;
    int monedasGeneradas = 0;
    int monedasEnMapa = 0;
    float puntaje = 0;

    char salida[TAM_SALIDA];
    char direccion;

    system("chcp 437 > nul");

    opcion = mostrarMenu();

    do{
        if(pasos > 0 && opcion < 3){
            opcion ++;
        }

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

        if(opcion == 2 || opcion == 3){
            printf("Monedas generadas: %d\n", monedasGeneradas);
            printf("Monedas encontradas en el mapa: %d\n\n", monedasEnMapa);
        }

        buscarJug(mapaSeleccionado, FILAS, COLUMNAS, &filaJug, &colJug);
        imprimirVentana(mapaSeleccionado, filaJug, colJug);
    
        printf("\nUsa WASD para moverte y Q para salir:");
        scanf(" %c", &direccion);
        direccion = tolower(direccion);

        movLeg = moverJug(mapaSeleccionado, COLUMNAS, &filaJug, &colJug, direccion, &mondJug, &pasos);
    
        imprimirVentana(mapaSeleccionado, filaJug, colJug);

        while(direccion != 'q' && movLeg != 5){
            system("cls");

            printf("====================================\n");
            printf("            NIVEL %d\n", opcion);
            printf("====================================\n\n");

            if(movLeg == 6){  
                printf("¡Has encontrado una llave!, Ahora busca la puerta para abrirla.\n\n"); 
            }

            if(opcion == 2 || opcion == 3){
                printf("Monedas generadas: %d\n", monedasGeneradas);
                printf("Monedas encontradas en el mapa: %d\n", monedasEnMapa);
                printf("Monedas recogidas: %d\n\n", mondJug);
            }

            imprimirVentana(mapaSeleccionado, filaJug, colJug);

            printf("\nUsa WASD para moverte y Q para salir:");
            scanf(" %c", &direccion);
            direccion = tolower(direccion);

            movLeg = moverJug(mapaSeleccionado, COLUMNAS, &filaJug, &colJug, direccion, &mondJug, &pasos);

        }
        
        if(movLeg == 5){
            printf("¡Has completado el nivel!\n");
            if(opcion == 3) printf("Felicidades! Completaste el juego.\n");
            system("pause");
        }

    }while(direccion != 'q' && opcion < 3);

    printf("\n");

    system("pause");

    return 0;
}