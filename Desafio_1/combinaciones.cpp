#include "combinaciones.h"
#include "bits.h"
#include "posicion.h"
#include "marcador.h"

int BuscarHorizontal(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador)
{
    int totalPosiciones = filas * columnas;
    int combinaciones = 0;

    for (int fila = 0; fila < filas; fila++)
    {
        int contador = 1;

        for (int columna = 1; columna < columnas; columna++)
        {
            int posicionActual =
                filaColumnaPosicion(fila, columna, columnas);

            int posicionAnterior =
                filaColumnaPosicion(fila, columna - 1, columnas);

            unsigned char fichaActual =
                obtenerFicha(tablero, posicionActual, totalPosiciones, bytesReservados);

            unsigned char fichaAnterior =
                obtenerFicha(tablero, posicionAnterior, totalPosiciones, bytesReservados);

            if (fichaActual < TIPOS_DE_FICHA &&
                fichaActual == fichaAnterior)
            {
                contador++;
            }
            else
            {

                if (contador >= 3)
                {
                    for (int k = 0; k < contador; k++)
                    {
                        marcarFicha(marcador,filaColumnaPosicion(fila, columna - 1 - k, columnas));
                    }

                    combinaciones++;
                }

                contador = 1;
            }
        }


        if (contador >= 3)
        {
            for (int k = 0; k < contador; k++)
            {
                marcarFicha(marcador,filaColumnaPosicion(fila, columnas - 1 - k, columnas));
            }

            combinaciones++;
        }
    }

    return combinaciones;
}

int BuscarVertical(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador)
{
    int totalPosiciones = filas * columnas;
    int combinaciones = 0;

    for (int columna = 0; columna < columnas; columna++)
    {
        int contador = 1;

        for (int fila = 1; fila < filas; fila++)
        {
            int posicionActual =
                filaColumnaPosicion(fila, columna, columnas);

            int posicionAnterior =
                filaColumnaPosicion(fila - 1, columna, columnas);

            unsigned char fichaActual =
                obtenerFicha(tablero, posicionActual, totalPosiciones, bytesReservados);

            unsigned char fichaAnterior =
                obtenerFicha(tablero, posicionAnterior, totalPosiciones, bytesReservados);

            if (fichaActual < TIPOS_DE_FICHA &&
                fichaActual == fichaAnterior)
            {
                contador++;
            }
            else
            {
                if (contador >= 3)
                {
                    for (int k = 0; k < contador; k++)
                    {
                        marcarFicha(marcador,filaColumnaPosicion(fila - 1 - k, columna, columnas));
                    }

                    combinaciones++;
                }

                contador = 1;
            }
        }

        if (contador >= 3)
        {
            for (int k = 0; k < contador; k++)
            {
                marcarFicha(marcador,filaColumnaPosicion(filas - 1 - k, columna, columnas));
            }

            combinaciones++;
        }
    }

    return combinaciones;
}

int BuscarCombinaciones(const unsigned char* tablero, int filas, int columnas,int bytesReservados, unsigned char* marcador)
{
    int totalPosiciones = filas * columnas;

    inicializarMarcador(marcador, totalPosiciones);

    int combinaciones = 0;

    combinaciones += BuscarHorizontal(tablero, filas, columnas, bytesReservados, marcador);
    combinaciones += BuscarVertical(tablero, filas, columnas, bytesReservados, marcador);

    return combinaciones;
}