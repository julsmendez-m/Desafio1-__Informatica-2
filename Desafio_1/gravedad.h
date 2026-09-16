#ifndef GRAVEDAD_H
#define GRAVEDAD_H

// Copia los 3 bits de la ficha en 'origen' hacia 'destino' y luego escribe el codigo de vacio (110) en 'origen'
void DesplazarFicha(unsigned char* tablero, int origen, int destino,int totalPosiciones, int bytesReservados);

// Baja una ficha dentro de la misma columna, desde filaOrigen hasta filaDestino.
void BajarFicha(unsigned char* tablero, int filaOrigen, int filaDestino,int columna, int filas, int columnas, int bytesReservados);

// Recorre la columna abajo hacia arriba. 'filaDestino' indica la casilla mas baja que todavia esta libre.
//Cada ficha que se encuentra se baja a esa casilla y filaDestino sube una fila.
//Al terminar, todas las casillas desde 0 hasta filaDestino son vacias.
int CompactarColumna(unsigned char* tablero, int columna, int filas, int columnas, int bytesReservados);

// Compacta cada columna del tablero y acumula los vacios que quedaron,para que el modulo de nuevas fichas sepa cuantas debe generar.
int AplicarGravedad(unsigned char* tablero, int filas, int columnas, int bytesReservados);

#endif