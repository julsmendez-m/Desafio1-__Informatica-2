#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

// Indices del arreglo de estadisticas (cada casilla guarda un contador).
const int EST_MOVIMIENTOS       = 0;  // eliminaciones hechas por el jugador
const int EST_FICHAS_ELIMINADAS = 1;  // fichas eliminadas en total
const int EST_COMBINACIONES     = 2;  // combinaciones detectadas en total
const int EST_CASCADAS          = 3;  // cascadas en toda la partida
const int EST_CASCADAS_JUGADA   = 4;  // cascadas de la jugada actual
const int EST_PUNTUACION        = 5;  // puntaje acumulado
const int TOTAL_ESTADISTICAS    = 6;  // tamano del arreglo

// Puntos del criterio de puntuacion.
const int PUNTOS_POR_FICHA   = 10;
const int PUNTOS_POR_CASCADA = 50;

void inicializarEstadisticas(int* estadisticas);

// Cuenta una eliminacion del jugador y reinicia las cascadas de la jugada.
void registrarMovimiento(int* estadisticas);

// Suma las combinaciones detectadas.
void registrarCombinacion(int* estadisticas, int cantidad);

// Suma las fichas eliminadas.
void registrarFichaEliminada(int* estadisticas, int cantidad);

// Cuenta una cascada en el total y en la jugada actual.
void registrarCascada(int* estadisticas);

// Suma al puntaje segun las fichas eliminadas y si fue una cascada.
void actualizarPuntuacion(int* estadisticas, int fichasEliminadas, bool esCascada);

// Registra todo lo que ocurrio en una ronda de eliminacion.
void actualizarEstadisticas(int* estadisticas, int fichasEliminadas,int combinaciones, bool esCascada);

// Muestra las dimensiones del tablero y todos los contadores.
void mostrarEstadisticas(const int* estadisticas, int filas, int columnas);

#endif