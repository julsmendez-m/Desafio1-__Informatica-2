#include "estadisticas.h"
#include <iostream>

void inicializarEstadisticas(int* estadisticas)
{
    for (int i = 0; i < TOTAL_ESTADISTICAS; i++)
    {
        estadisticas[i] = 0;
    }
}

void registrarMovimiento(int* estadisticas)
{
    estadisticas[EST_MOVIMIENTOS]++;
    estadisticas[EST_CASCADAS_JUGADA] = 0;
}

void registrarCombinacion(int* estadisticas, int cantidad)
{
    estadisticas[EST_COMBINACIONES] += cantidad;
}

void registrarFichaEliminada(int* estadisticas, int cantidad)
{
    estadisticas[EST_FICHAS_ELIMINADAS] += cantidad;
}

void registrarCascada(int* estadisticas)
{
    estadisticas[EST_CASCADAS]++;
    estadisticas[EST_CASCADAS_JUGADA]++;
}

void actualizarPuntuacion(int* estadisticas, int fichasEliminadas, bool esCascada)
{
    estadisticas[EST_PUNTUACION] += fichasEliminadas * PUNTOS_POR_FICHA;

    if (esCascada)
    {
        estadisticas[EST_PUNTUACION] += PUNTOS_POR_CASCADA;
    }
}

void actualizarEstadisticas(int* estadisticas, int fichasEliminadas,int combinaciones, bool esCascada)
{
    registrarFichaEliminada(estadisticas, fichasEliminadas);
    registrarCombinacion(estadisticas, combinaciones);

    if (esCascada)
    {
        registrarCascada(estadisticas);
    }

    actualizarPuntuacion(estadisticas, fichasEliminadas, esCascada);
}

void mostrarEstadisticas(const int* estadisticas, int filas, int columnas)
{
    std::cout << "\n===== ESTADISTICAS =====\n";
    std::cout << "Tablero: " << filas << " x " << columnas << '\n';
    std::cout << "Eliminaciones del jugador: " << estadisticas[EST_MOVIMIENTOS] << '\n';
    std::cout << "Fichas eliminadas: " << estadisticas[EST_FICHAS_ELIMINADAS] << '\n';
    std::cout << "Combinaciones: " << estadisticas[EST_COMBINACIONES] << '\n';
    std::cout << "Cascadas en esta jugada: " << estadisticas[EST_CASCADAS_JUGADA] << '\n';
    std::cout << "Cascadas en la partida: " << estadisticas[EST_CASCADAS] << '\n';
    std::cout << "Puntuacion: " << estadisticas[EST_PUNTUACION] << '\n';
}