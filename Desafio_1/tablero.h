#ifndef TABLERO_H
#define TABLERO_H

// Reserva la memoria necesaria para el tablero y lo inicializa vacío.
// Devuelve en bytesReservados el tamaño del bloque.
void crearTablero(unsigned char*& tablero, int filas, int columnas, int& bytesReservados);

// Coloca todas las posiciones del tablero en estado vacío (110).
void LimpiarTablero(unsigned char* tablero, int filas, int columnas, int bytesReservados);

// Libera la memoria dinámica del tablero.
void liberarTablero(unsigned char*& tablero, int& bytesReservados);

// Indica si la ocupación de la memoria cayó por debajo del 65 %.
bool debeReducirMemoria(int totalPosiciones, int bytesReservados);

// Mueve las fichas a la nueva forma del tablero. Lo usan las 4 operaciones de abajo.
bool ReorganizarTablero(unsigned char*& tablero, int& filas, int& columnas, int& bytesReservados,int indiceFila, int cambioFila, int indiceColumna, int cambioColumna);

// Agrega una fila vacía en indice (0..filas). Las casillas nuevas quedan en 110.
bool InsertarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice);

// Elimina la fila indice (0..filas-1).
bool EliminarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice);

// Agrega una columna vacía en indice (0..columnas). Las casillas nuevas quedan en 110.
bool InsertarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice);

// Elimina la columna indice (0..columnas-1).
bool EliminarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice);

#endif