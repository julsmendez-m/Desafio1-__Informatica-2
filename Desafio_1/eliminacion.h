#ifndef ELIMINACION_H
#define ELIMINACION_H

bool EliminarFicha(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados);

void VaciarPosicion(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados);

int ContarFichasEliminadas(const unsigned char* marcador, int totalPosiciones);

int EliminarFichasMarcadas(unsigned char* tablero, int filas, int columnas,int bytesReservados, const unsigned char* marcador);

int EliminarCombinaciones(unsigned char* tablero, int filas, int columnas,int bytesReservados, const unsigned char* marcador);

#endif