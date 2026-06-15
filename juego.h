#ifndef JUEGO_H
#define JUEGO_H

#define FILAS 60
#define COLUMNAS 60
#define VENTANA 20
#define Pasos1 780
#define Pasos2 200 //161
#define Pasos3 300 //251
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

void abrirPuerta(int *mapa, int filas, int columnas);

void imprimirVentana(int *mapaSeleccionado, int filaJug, int colJug);
void imprimirColor(const char *salida);
int moverJug(int *mapa, int columnas, int *filaJug, int *colJug, char direccion, int *mondJug, int *pasos);

short generar_cantidad_monedas();

void colocar_monedas(
    int *mapa,
    int filas,
    int columnas,
    int cantidad
);

void buscarJug(int *mapa, int filas, int columnas, int *fila, int *col);
void preparar_contar_cantidad_celda(int *mapaSeleccionado);
int contar_cantidad_celda(int *mapa, int filas, int columnas, int valor);
void preparar_buscar_objeto(int *mapa);
int buscar_objeto(int *mapa, int columnas, int fila, int columna, int valor);
int contar_celdas_vacias(int *mapa, int filas, int columnas);
int calcular_puntaje(int nivel, int pasos, int monedas);
void pantallaInicio();
void pantallaFinal(int puntaje, int monedas, int pasos, int monedaJuego, int pasosJuego);


#endif