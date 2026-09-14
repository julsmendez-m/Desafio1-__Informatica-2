#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Marca las fichas que forman grupos horizontales de 3 o más.
int BuscarHorizontal(const unsigned char* tablero,int filas,int columnas,unsigned char* marcadas);

// Marca las fichas que forman grupos verticales de 3 o más.
int BuscarVertical(const unsigned char* tablero,int filas,int columnas,unsigned char* marcadas);

// Busca combinaciones horizontales y verticales.
// Devuelve la cantidad de posiciones marcadas.
int BuscarCombinaciones(const unsigned char* tablero,int filas,int columnas,unsigned char* marcadas);

#endif
