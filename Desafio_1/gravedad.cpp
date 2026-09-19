#include "gravedad.h"
#include "bits.h"
#include "posicion.h"

void DesplazarFicha(unsigned char* tablero, int origen, int destino,int totalPosiciones, int bytesReservados)
{
    if (origen == destino)
        return;

    unsigned char ficha = obtenerFicha(tablero, origen, totalPosiciones, bytesReservados);

    modificarFicha(tablero, destino, ficha, totalPosiciones, bytesReservados);
    modificarFicha(tablero, origen, F_VACIO, totalPosiciones, bytesReservados);
}

void BajarFicha(unsigned char* tablero, int filaOrigen, int filaDestino,int columna, int filas, int columnas, int bytesReservados)
{
    if (filaDestino <= filaOrigen || filaDestino >= filas || filaOrigen < 0)
        return;

    int totalPosiciones = filas * columnas;
    int origen  = filaColumnaPosicion(filaOrigen, columna, columnas);
    int destino = filaColumnaPosicion(filaDestino, columna, columnas);

    DesplazarFicha(tablero, origen, destino, totalPosiciones, bytesReservados);
}

int CompactarColumna(unsigned char* tablero, int columna, int filas, int columnas, int bytesReservados)
{
    int totalPosiciones = filas * columnas;
    int filaDestino = filas - 1;

    for (int fila = filas - 1; fila >= 0; fila--)
    {
        int posicion = filaColumnaPosicion(fila, columna, columnas);
        unsigned char ficha = obtenerFicha(tablero, posicion, totalPosiciones, bytesReservados);

        if (ficha != F_VACIO)
        {
            BajarFicha(tablero, fila, filaDestino, columna, filas, columnas, bytesReservados);
            filaDestino--;
        }
    }

    return filaDestino + 1;
}

int AplicarGravedad(unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    int vacios = 0;

    for (int columna = 0; columna < columnas; columna++)
    {
        vacios += CompactarColumna(tablero, columna, filas, columnas, bytesReservados);
    }

    return vacios;
}