#ifndef JUEGO_H
#define JUEGO_H

#define FILAS 60
#define COLUMNAS 60
#define TAM_SALIDA (FILAS * (COLUMNAS + 1) + 1)

void imprimirColor(const char *salida);
int mostrarMenu();

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

#endif