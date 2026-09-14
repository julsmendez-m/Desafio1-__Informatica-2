#ifndef POSICION_H
#define POSICION_H

/* El tablero es rectangular para el usuario, pero en memoria es
   una sola tira lineal de bits.
   posicion lineal: 0 .. (filas*columnas - 1), recorrida por
   filas. Es decir, la fila 0 completa, luego la fila 1, etc. */

// De (fila, columna) a posicion lineal
int filaColumnaPosicion(int fila, int columna, int columnas);

// De posicion lineal a (fila, columna)
void posicionFilaColumna(int posicion, int columnas, int& fila, int& columna);

// Solo la fila de una posicion lineal
int posicionFila(int posicion, int columnas);

#endif