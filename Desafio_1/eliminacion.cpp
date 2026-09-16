#include "eliminacion.h"
#include "bits.h"
#include "marcador.h"

bool EliminarFicha(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados)
{
    unsigned char ficha = obtenerFicha(tablero, posicion, totalPosiciones, bytesReservados);

    // obtenerFicha devuelve F_ESPECIAL si la posicion esta fuera de rango,
    // asi que este if cubre ambos casos: posicion invalida o casilla sin ficha.
    if (ficha >= TIPOS_DE_FICHA)
        return false;

    VaciarPosicion(tablero, posicion, totalPosiciones, bytesReservados);
    return true;
}

void VaciarPosicion(unsigned char* tablero, int posicion, int totalPosiciones, int bytesReservados)
{
    modificarFicha(tablero, posicion, F_VACIO, totalPosiciones, bytesReservados);
}

// se reutiliza la funcion del modulo marcador.
int ContarFichasEliminadas(const unsigned char* marcador, int totalPosiciones)
{
    return contarFichasMarcadas(marcador, totalPosiciones);
}

int EliminarFichasMarcadas(unsigned char* tablero, int filas, int columnas,int bytesReservados, const unsigned char* marcador)
{
    int totalPosiciones = filas * columnas;
    int eliminadas = 0;

    for (int i = 0; i < totalPosiciones; i++)
    {
        if (estaMarcada(marcador, i))
        {
            VaciarPosicion(tablero, i, totalPosiciones, bytesReservados);
            eliminadas++;
        }
    }

    return eliminadas;
}

// Elimina las combinaciones que BuscarCombinaciones dejo marcadas.
int EliminarCombinaciones(unsigned char* tablero, int filas, int columnas,int bytesReservados, const unsigned char* marcador)
{
    return EliminarFichasMarcadas(tablero, filas, columnas, bytesReservados, marcador);
}