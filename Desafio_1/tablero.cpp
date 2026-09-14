#include "tablero.h"
#include "bits.h"

void crearTablero(unsigned char*& tablero, int filas, int columnas)
{
    int bytes = calcularBytes(filas * columnas);

    tablero = new unsigned char[bytes];

    LimpiarTablero(tablero, filas, columnas);
}

void LimpiarTablero(unsigned char* tablero, int filas, int columnas)
{
    int totalPosiciones = filas * columnas;
    int bytes = calcularBytes(totalPosiciones);

    for (int i = 0; i < bytes; i++)
    {
        tablero[i] = 0;
    }

    for (int i = 0; i < totalPosiciones; i++)
    {
        modificarFicha(tablero, i, F_VACIO, totalPosiciones);
    }
}

void liberarTablero(unsigned char*& tablero)
{
    delete[] tablero;
    tablero = nullptr;
}
