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