#ifndef ELIMINACION_H
#define ELIMINACION_H

// Elimina la ficha que eligio el jugador. Devuelve false si no habia ficha.
bool EliminarFicha(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados);

// Escribe el codigo de vacio (110) en la posicion.
void VaciarPosicion(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados);

// Cuenta las posiciones marcadas.
int ContarFichasEliminadas(const unsigned char* marcador, int totalPosiciones);

// Vacia todas las posiciones marcadas. Devuelve cuantas vacio.
int EliminarFichasMarcadas(unsigned char* tablero, int filas, int columnas,int bytesReservados, const unsigned char* marcador);

// Elimina las combinaciones que BuscarCombinaciones dejo marcadas.
int EliminarCombinaciones(unsigned char* tablero, int filas, int columnas,int bytesReservados, const unsigned char* marcador);

#endif