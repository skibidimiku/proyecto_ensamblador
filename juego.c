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

void imprimirColor(const char *salida)
{
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

int moverJug(int *mapa, int columnas, int *filaJug, int *colJug, char direccion){
    int fila2 = *filaJug;
    int columna2 = *colJug;

    switch(direccion){
        case 'w': fila2--; break;
        case 's': fila2++; break;
        case 'a': columna2--; break;
        case 'd': columna2++; break;
        default: return 0;
    }

    int resultado =intercambiar_celdas(mapa, columnas, *filaJug, *colJug, fila2, columna2);

    if(resultado != 0){
        *filaJug = fila2;
        *colJug  = columna2;
    }

    if(resultado == 6){
        printf("¡Has encontrado la llave! La puerta se ha abierto.\n");
        abrirPuerta(mapa, FILAS, COLUMNAS);
    }
    
    return resultado;
}

int mostrarMenu(){
    int opcion;

    printf("====================================\n");
    printf("           LABERINTOS\n");
    printf("====================================\n");
    printf("1. Nivel 1\n");
    printf("2. Nivel 2\n");
    printf("3. Nivel 3\n");
    printf("\nSelecciona un nivel: ");

    scanf("%d", &opcion);

    return opcion;
}


void colocar_monedas(
    int *mapa,
    int filas,
    int columnas,
    int cantidad
)
{
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

        if(mapa[pos] == 0)
        {
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
                mapa[i * columnas + j] = 0;
                return;
            }
        }
    }
}