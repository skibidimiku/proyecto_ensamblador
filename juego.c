#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "juego.h"


void imprimirVentana(int *mapaSeleccionado, int filaJug, int colJug){
    char salida[TAM_SALIDA];
    int ventana[20][20];

    int filaIni = filaJug - 10;
    int colIni = colJug - 10;

    if(filaIni < 0) filaIni = 0;
    if(colIni < 0) colIni = 0;
    if(filaIni > FILAS + VENTANA) filaIni = FILAS - VENTANA;
    if(colIni > COLUMNAS + VENTANA) colIni = COLUMNAS - VENTANA;

    for(int i = 0; i < VENTANA; i++){
        for(int j = 0; j < VENTANA; j++){
            ventana[i][j] = mapaSeleccionado[(filaIni + i) * COLUMNAS + (colIni + j)];
        }
    }
    generar_pixel_art(&ventana[0][0], salida, VENTANA, VENTANA);

    imprimirColor(salida);
}

void imprimirColor(const char *salida){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; salida[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)salida[i];

        if(c == 219){
            SetConsoleTextAttribute(consola, 10);
        }else if(c == '.'){
            SetConsoleTextAttribute(consola, 8);
        }else if(c == '$'){
            SetConsoleTextAttribute(consola, 14);
        }else if(c == 'P'){
            SetConsoleTextAttribute(consola, 12);
        }else if(c == 177){
            SetConsoleTextAttribute(consola, 3);
        }else if(c == 'S'){
            SetConsoleTextAttribute(consola, 4);
        }else if(c == 'K'){
            SetConsoleTextAttribute(consola, 6);
        }else{
            SetConsoleTextAttribute(consola, 7);
        }

        putchar(c);
    }

    SetConsoleTextAttribute(consola, 7);
}

int moverJug(int *mapa, int columnas, int *filaJug, int *colJug, char direccion, int *mondJug, int *pasos){
    int fila2 = *filaJug;
    int columna2 = *colJug;
    int resultado = 0;

    switch(direccion){
        case 'w': fila2--; break;
        case 's': fila2++; break;
        case 'a': columna2--; break;
        case 'd': columna2++; break;
        case 'b': preparar_buscar_objeto(mapa); break;
        case 'c': preparar_contar_cantidad_celda(mapa); break;
        default: return 0;
    }

    if(direccion == 'w' || direccion == 's' || direccion == 'a' || direccion == 'd' ) resultado = intercambiar_celdas(mapa, columnas, *filaJug, *colJug, fila2, columna2);

    if(resultado != 0){
        *filaJug = fila2;
        *colJug  = columna2;
        (*pasos)++;
    }

    if(resultado == 2){
        (*mondJug)++;
    }


    if(resultado == 6){
        printf("¡Has encontrado la llave! La puerta se ha abierto.\n");
        abrirPuerta(mapa, FILAS, COLUMNAS);
    }
    
    return resultado;
}

void colocar_monedas(
    int *mapa,
    int filas,
    int columnas,
    int cantidad
){
    static int inicializado = 0;

    if(!inicializado)
    {
        srand((unsigned)time(NULL));
        inicializado = 1;
    }

    int total = filas * columnas;

    while(cantidad > 0)
    {
        int pos = rand() % total;

        if(mapa[pos] == 0){
            mapa[pos] = 2;
            cantidad--;
        }
    }
}

void buscarJug(int *mapa, int filas, int columnas, int *fila, int *columna){
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (mapa[i * columnas + j] == 3){
                *fila = i;
                *columna = j;
                return;
            }
        }
    }
}

void abrirPuerta(int *mapa, int filas, int columnas){
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (mapa[i * columnas + j] == 4){
                mapa[i * columnas + j] = 7;
                return;
            }
        }
    }
}

void preparar_contar_cantidad_celda(int *mapaSeleccionado){
    int cantidad, op;
    printf("Cual es el numero de la celda que quieres contar? (0: vacia, 1: pared, 2: moneda, 3: jugador, 4: puerta cerrada, 6: llave, 7: puerta abierta)\n");
    scanf("%d", &op);
    
    if(op < 0 || op > 7){
        printf("Opcion invalida.\n");
        return;
    }

    cantidad = contar_cantidad_celda(mapaSeleccionado, FILAS, COLUMNAS, op);
    printf("Cantidad de celdas con valor %d: %d\n", op, cantidad);
    system("pause");
}

void preparar_buscar_objeto(int *mapaSeleccionado){
    int columna, fila, op, res;
    printf("Cual es el numero de la celda que quieres buscar? (0: vacia, 1: pared, 2: moneda, 3: jugador, 4: puerta cerrada, 6: llave, 7: puerta abierta)\n");
    scanf("%d", &op);

    if(op < 0 || op > 7){
        printf("Opcion invalida.\n");
        return;
    }

    printf("Cual es el numero de la fila en la que buscar (0-59):");
    scanf("%d", &fila);

    if(fila <= 0 || fila >= 59){
        printf("Fuera de rango.\n");
        return;
    }

    printf("Cual es el numero de la columna en la que buscar(0-59):");
    scanf("%d", &columna);

    if(columna <= 0 || columna >= 59){
        printf("Fuera de rango.\n");
        return;
    }

    res = buscar_objeto(mapaSeleccionado, COLUMNAS, fila, columna, op);

    if(res == 1){
        switch (op){
        case 0: printf("Si, ahi hay un espacio vacio\n");  break;
        case 1: printf("Si, ahi hay una pared\n");  break;
        case 2: printf("Si, ahi hay una moneda\n");  break;
        case 3: printf("Si, ahi esta el jugador\n");  break;
        case 4: printf("Si, ahi hay una puerta\n");  break;
        case 5: printf("Si, ahi esta la salida pared\n");  break;
        case 6: printf("Si, ahi hay una llave\n");  break;
        case 7: printf("Si, ahi hay una puerta abirta\n");  break;
        default: break;
        }
    }else{
        printf("No se encontro el objeto que buscabas\n");
    }

    system("pause");
}

void pantallaInicio(){
    system("cls");
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consola, 11);
    printf("====================================\n");
    printf("          Bienvenid@s\n");
    printf("====================================\n");

    SetConsoleTextAttribute(consola, 14);
    printf("  ____  _ _   __  __                     \n");
    printf(" | __ )(_) |_ |  \\/  | __ _ _______      \n");
    printf(" |  _ \\| | __|| |\\/| |/ _` |_  / _ \\ \n");
    printf(" | |_) | | |_ | |  | | (_| |/ /  __/     \n");
    printf(" |____/|_|\\__||_|  |_|\\__,_/___\\___| \n\n");


    SetConsoleTextAttribute(consola, 10); 
    printf("Un Laberinto Bien ensamblado\n\n");

    SetConsoleTextAttribute(consola, 7); 
    system("pause");
}

void pantallaFinal(int puntaje, int monedas, int pasos, int monedaJuego, int pasosJuegp) {
    system("cls");
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consola, 12);
    printf("====================================\n");
    printf("          JUEGO COMPLETADO!        \n");
    printf("====================================\n\n");

    SetConsoleTextAttribute(consola, 13);
    printf("  ____  _ _   __  __                     \n");
    printf(" | __ )(_) |_ |  \\/  | __ _ _______      \n");
    printf(" |  _ \\| | __|| |\\/| |/ _` |_  / _ \\ \n");
    printf(" | |_) | | |_ | |  | | (_| |/ /  __/     \n");
    printf(" |____/|_|\\__||_|  |_|\\__,_/___\\___| \n\n");

    SetConsoleTextAttribute(consola, 7);
    printf("Resumen final:\n");
    printf("Monedas recolectadas: %d/%d\n", monedas, monedaJuego);
    printf("Pasos realizados: %d/%d\n", pasos, pasosJuegp);
    printf("Puntaje final: %d\n\n", puntaje);

    printf("Gracias por jugar BitMaze.\n");
    printf("====================================\n");
    system("pause");
}