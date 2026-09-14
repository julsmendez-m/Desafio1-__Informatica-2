#ifndef TABLERO_H
#define TABLERO_H

// Reserva la memoria necesaria para el tablero y lo inicializa vacío.
void crearTablero(unsigned char*& tablero, int filas, int columnas);

// Coloca todas las posiciones del tablero en estado vacío (110).
void LimpiarTablero(unsigned char* tablero, int filas, int columnas);

// Libera la memoria dinámica del tablero.
void liberarTablero(unsigned char*& tablero);


#endif
