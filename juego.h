#ifndef JUEGO_H
#define JUEGO_H

#define FILAS 60
#define COLUMNAS 60
#define VENTANA 20
#define TAM_SALIDA (FILAS * (COLUMNAS + 1) + 1)


void generar_pixel_art(
    int *matriz,
    char *salida,
    int filas,
    int columnas
);

int intercambiar_celdas(
            int *matriz,
            int columnas,
            int fila1,
            int columna1,
            int fila2,
            int columna2
);

void imprimirVentana(int *mapaSeleccionado, int filaJug, int colJug);
void imprimirColor(const char *salida);
int mostrarMenu();
int moverJug(int *mapa, int columnas, int *filaJug, int *colJug, char direccion);

short generar_cantidad_monedas();

int contar_monedas(
    int *mapa,
    int filas,
    int columnas
);

void colocar_monedas(
    int *mapa,
    int filas,
    int columnas,
    int cantidad
);

void buscarJug(int *mapa, int filas, int columnas, int *fila, int *col);

#endif