#ifndef COMBINACIONES_H
#define COMBINACIONES_H

int BuscarHorizontal(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador);

int BuscarVertical(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador);

int BuscarCombinaciones(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador);

#endif