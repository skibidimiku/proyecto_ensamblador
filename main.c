#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "juego.h"
#include "mapas.h"

int main(){
    int opcion = 1;
    int *mapaSeleccionado;
    int filaJug, colJug, mondJug = 0, llave, pasos = 0, pasosTot = 0, mondTot = 0, mondJuego = 0, movLeg, vacias;
    int monedasGeneradas = 0;
    int monedasEnMapa = 0;
    int puntaje = 0, pasosJuego = 0;

    char direccion;

    system("chcp 437 > nul");

    pantallaInicio();

    do{
        if(pasos > 0 && opcion < 3){
            opcion ++;
        }

        pasosTot += pasos;
        mondTot += mondJug;
        pasos = 0;
        mondJug = 0;
        llave = 0;

        switch(opcion){
            case 1: mapaSeleccionado = &nivel1[0][0]; pasosJuego += Pasos1;  break;

            case 2: mapaSeleccionado = &nivel2[0][0]; pasosJuego += Pasos2; break;

            case 3: mapaSeleccionado = &nivel3[0][0]; pasosJuego += Pasos3; break;

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

            monedasEnMapa = contar_cantidad_celda(
                mapaSeleccionado,
                FILAS,
                COLUMNAS, 
                2
            );
        }

        vacias = contar_celdas_vacias(mapaSeleccionado, FILAS, COLUMNAS);

        system("cls");

        printf("====================================\n");
        printf("            NIVEL %d\n", opcion);
        printf("====================================\n\n");

        printf("Celdas vacias en este nivel: %d\n", vacias);

        if(opcion == 2 || opcion == 3){
            printf("Monedas generadas: %d\n", monedasGeneradas);
            printf("Monedas encontradas en el mapa: %d\n\n", monedasEnMapa);
            mondJuego += monedasGeneradas;
        }

        buscarJug(mapaSeleccionado, FILAS, COLUMNAS, &filaJug, &colJug);
        imprimirVentana(mapaSeleccionado, filaJug, colJug);
    
        printf("\nUsa WASD para moverte, C para contar los valores que quieras, B para buscar y Q para salir:");
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
                printf("Has encontrado una llave!, Ahora busca la puerta para abrirla.\n"); 
                llave = 1;
            }

            if(opcion == 2 || opcion == 3){
                printf("Monedas recogidas: %d/%d\n", mondJug, monedasGeneradas);
            }

            printf("Pasos: %d\n", pasos);
            if(llave == 1)printf("LLave: Si\n\n");
            else printf("LLave: No\n\n");

            imprimirVentana(mapaSeleccionado, filaJug, colJug);

            printf("\nUsa WASD para moverte, C para contar los valores que quieras, B para buscar y Q para salir:");
            scanf(" %c", &direccion);
            direccion = tolower(direccion);

            movLeg = moverJug(mapaSeleccionado, COLUMNAS, &filaJug, &colJug, direccion, &mondJug, &pasos);

        }

        

        if(movLeg == 5){
            printf("Has completado el nivel!\n");
            puntaje += calcular_puntaje( opcion, pasos, mondJug);
            printf("Resumen de nivel:\n");
            if(opcion != 1) printf("Monedas recolectadas: %d/%d\n", mondJug, monedasGeneradas);
            printf("Pasos realizados: %d\n", pasos);
            printf("Puntaje final: %d\n\n", puntaje);
            system("pause");
        }

    }while(direccion != 'q' && opcion < 3);

    if (opcion == 3 && movLeg == 5){
        pasosTot += pasos;
        mondTot += mondJug;
        pantallaFinal(puntaje, mondTot, pasosTot, mondJuego, pasosJuego);
    }    

    printf("\n");

    system("pause");

    return 0;
}