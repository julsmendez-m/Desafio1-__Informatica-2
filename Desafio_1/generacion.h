#ifndef GENERACION_H
#define GENERACION_H

// Devuelve un codigo de ficha al azar entre 0 (000) y 5 (101), con distribucion uniforme.
unsigned char GenerarFichaAleatoria();

// Escribe una ficha aleatoria en la posicion indicada si esta vacia.
bool InsertarNuevasFichas(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados);

// Recorre todo el tablero y rellena cada casilla vacia. Devuelve cuantas relleno.
int RellenarEspaciosVacios(unsigned char* tablero, int filas, int columnas, int bytesReservados);

// Rellena los vacios que la gravedad dejo arriba de cada columna. Devuelve cuantas genero.
int GenerarNuevasFichas(unsigned char* tablero, int filas, int columnas, int bytesReservados);

#endif