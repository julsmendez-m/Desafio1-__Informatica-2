#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

const int EST_MOVIMIENTOS       = 0;  // eliminaciones hechas por el jugador
const int EST_FICHAS_ELIMINADAS = 1;  // fichas eliminadas en total
const int EST_COMBINACIONES     = 2;  // combinaciones detectadas en total
const int EST_CASCADAS          = 3;  // cascadas en toda la partida
const int EST_CASCADAS_JUGADA   = 4;  // cascadas de la jugada actual
const int EST_PUNTUACION        = 5;  // puntaje acumulado
const int TOTAL_ESTADISTICAS    = 6;  // tamano del arreglo

const int PUNTOS_POR_FICHA   = 10;
const int PUNTOS_POR_CASCADA = 50;

void inicializarEstadisticas(int* estadisticas);

void registrarMovimiento(int* estadisticas);

void registrarCombinacion(int* estadisticas, int cantidad);

void registrarFichaEliminada(int* estadisticas, int cantidad);

void registrarCascada(int* estadisticas);

void actualizarPuntuacion(int* estadisticas, int fichasEliminadas, bool esCascada);

void actualizarEstadisticas(int* estadisticas, int fichasEliminadas,int combinaciones, bool esCascada);

void mostrarEstadisticas(const int* estadisticas, int filas, int columnas);

#endif