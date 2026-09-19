#ifndef GRAVEDAD_H
#define GRAVEDAD_H

void DesplazarFicha(unsigned char* tablero, int origen, int destino,int totalPosiciones, int bytesReservados);

void BajarFicha(unsigned char* tablero, int filaOrigen, int filaDestino,int columna, int filas, int columnas, int bytesReservados);

int CompactarColumna(unsigned char* tablero, int columna, int filas, int columnas, int bytesReservados);

int AplicarGravedad(unsigned char* tablero, int filas, int columnas, int bytesReservados);

#endif