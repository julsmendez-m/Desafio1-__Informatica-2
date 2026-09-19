#ifndef GENERACION_H
#define GENERACION_H

unsigned char GenerarFichaAleatoria();

bool InsertarNuevasFichas(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados);

int RellenarEspaciosVacios(unsigned char* tablero, int filas, int columnas, int bytesReservados);

int GenerarNuevasFichas(unsigned char* tablero, int filas, int columnas, int bytesReservados);

#endif