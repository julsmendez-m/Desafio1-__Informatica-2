#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Marca las rachas horizontales de 3 o mas fichas iguales. Devuelve cuantas hay.
int BuscarHorizontal(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador);

// Marca las rachas verticales de 3 o mas fichas iguales. Devuelve cuantas hay.
int BuscarVertical(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador);

// Limpia el marcador y busca en ambas direcciones.
int BuscarCombinaciones(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador);

#endif