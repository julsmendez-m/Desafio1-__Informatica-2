#include "posicion.h"

int filaColumnaPosicion(int fila, int columna, int columnas)
{
    return fila * columnas + columna;
}

void posicionFilaColumna(int posicion, int columnas, int& fila, int& columna)
{
    if (columnas <= 0)
    {
        fila = 0;
        columna = 0;
        return;
    }

    fila = posicion / columnas;
    columna = posicion % columnas;
}

int posicionFila(int posicion, int columnas)
{
    if (columnas <= 0)
        return 0;

    return posicion / columnas;
}