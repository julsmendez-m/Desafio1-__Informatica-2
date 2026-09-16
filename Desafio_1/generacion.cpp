#include "generacion.h"
#include "bits.h"
#include "posicion.h"
#include <cstdlib>

unsigned char GenerarFichaAleatoria()
{
    int sobrante = (RAND_MAX % TIPOS_DE_FICHA + 1) % TIPOS_DE_FICHA;
    int limite = RAND_MAX - sobrante;
    int numero = rand();

    while (numero > limite)
    {
        numero = rand();
    }

    return (unsigned char)(numero % TIPOS_DE_FICHA);
}

// escribe si la casilla esta vacia (110),devuelve true si inserto una ficha nueva.
bool InsertarNuevasFichas(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados)
{
    if (obtenerFicha(tablero, posicion, totalPosiciones, bytesReservados) != F_VACIO)
        return false;

    modificarFicha(tablero, posicion, GenerarFichaAleatoria(), totalPosiciones, bytesReservados);
    return true;
}

int RellenarEspaciosVacios(unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    int totalPosiciones = filas * columnas;
    int rellenadas = 0;

    for (int posicion = 0; posicion < totalPosiciones; posicion++)
    {
        if (InsertarNuevasFichas(tablero, posicion, totalPosiciones, bytesReservados))
        {
            rellenadas++;
        }
    }

    return rellenadas;
}

// despues de AplicarGravedad.se deja todos los vacios juntos arriba, cada columna se recorre desde la fila 0 y se detiene en la primera ficha que encuentra
int GenerarNuevasFichas(unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    int totalPosiciones = filas * columnas;
    int generadas = 0;

    for (int columna = 0; columna < columnas; columna++)
    {
        int fila = 0;

        while (fila < filas &&
               InsertarNuevasFichas(tablero, filaColumnaPosicion(fila, columna, columnas),
                                    totalPosiciones, bytesReservados))
        {
            generadas++;
            fila++;
        }
    }

    return generadas;
}