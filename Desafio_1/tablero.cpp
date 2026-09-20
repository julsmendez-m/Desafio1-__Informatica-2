#include "tablero.h"
#include "bits.h"
#include "posicion.h"
#include <iostream>

const int PORCENTAJE_MINIMO = 65;

const char* simboloFicha(unsigned char ficha)
{
    switch (ficha)
    {
    case F_CUADRADO:   return "■";
    case F_HEXAGONO:   return "⬢";
    case F_RECTANGULO: return "▬";
    case F_TRIANGULO:  return "▲";
    case F_ROMBO:      return "◆";
    case F_PENTAGONO:  return "⬟";
    case F_VACIO:      return "○";
    default:           return "★";   // F_ESPECIAL
    }
}

void mostrarBitsFicha(unsigned char ficha)
{
    for (int bit = 2; bit >= 0; bit--)
    {
        if ((ficha >> bit) & 1)
            std::cout << '1';
        else
            std::cout << '0';
    }
}

void crearTablero(unsigned char*& tablero, int filas, int columnas, int& bytesReservados)
{
    bytesReservados = calcularBytes(filas * columnas);

    tablero = new unsigned char[bytesReservados];

    LimpiarTablero(tablero, filas, columnas, bytesReservados);
}

void LimpiarTablero(unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    int totalPosiciones = filas * columnas;

    for (int i = 0; i < bytesReservados; i++)
    {
        tablero[i] = 0;
    }

    for (int i = 0; i < totalPosiciones; i++)
    {
        modificarFicha(tablero, i, F_VACIO, totalPosiciones, bytesReservados);
    }
}

void liberarTablero(unsigned char*& tablero, int& bytesReservados)
{
    delete[] tablero;
    tablero = nullptr;
    bytesReservados = 0;
}

bool debeReducirMemoria(int totalPosiciones, int bytesReservados)
{
    int bitsUsados = totalPosiciones * BITS_POR_FICHA;
    int bitsReservados = bytesReservados << 3;

    return bitsUsados * 100 < bitsReservados * PORCENTAJE_MINIMO;
}

int indiceOrigen(int indiceNuevo, int indiceCambio, int cambio)
{
    if (cambio == 0 || indiceNuevo < indiceCambio)
        return indiceNuevo;

    if (cambio > 0)
    {
        if (indiceNuevo == indiceCambio)
            return -1;

        return indiceNuevo - 1;
    }

    return indiceNuevo + 1;
}


void reducirMemoria(unsigned char*& tablero, int& bytesReservados, int bytesNuevos)
{
    unsigned char* nuevo = new unsigned char[bytesNuevos];
    const unsigned char* origen = tablero + (bytesReservados - bytesNuevos);

    for (int i = 0; i < bytesNuevos; i++)
    {
        *(nuevo + i) = *(origen + i);
    }

    delete[] tablero;
    tablero = nuevo;
    bytesReservados = bytesNuevos;
}

bool ReorganizarTablero(unsigned char*& tablero, int& filas, int& columnas, int& bytesReservados,int indiceFila, int cambioFila, int indiceColumna, int cambioColumna)
{
    int filasNuevas = filas + cambioFila;
    int columnasNuevas = columnas + cambioColumna;

    if (filasNuevas < 1 || columnasNuevas < 1)
        return false;

    int totalViejo = filas * columnas;
    int totalNuevo = filasNuevas * columnasNuevas;
    int bytesNecesarios = calcularBytes(totalNuevo);
    bool crece = totalNuevo > totalViejo;

    unsigned char* destino = tablero;
    int bytesDestino = bytesReservados;

    if (bytesNecesarios > bytesReservados)
    {
        destino = new unsigned char[bytesNecesarios];
        bytesDestino = bytesNecesarios;

        for (int i = 0; i < bytesDestino; i++)
        {
            destino[i] = 0;
        }
    }

    int inicio = crece ? 0 : totalNuevo - 1;
    int paso = crece ? 1 : -1;

    for (int k = 0, posicion = inicio; k < totalNuevo; k++, posicion += paso)
    {
        int filaVieja = indiceOrigen(posicion / columnasNuevas, indiceFila, cambioFila);
        int columnaVieja = indiceOrigen(posicion % columnasNuevas, indiceColumna, cambioColumna);

        unsigned char ficha = F_VACIO;

        if (filaVieja >= 0 && columnaVieja >= 0)
        {
            ficha = obtenerFicha(tablero, filaVieja * columnas + columnaVieja,totalViejo, bytesReservados);
        }

        modificarFicha(destino, posicion, ficha, totalNuevo, bytesDestino);
    }

    if (destino != tablero)
    {
        delete[] tablero;
        tablero = destino;
    }

    bytesReservados = bytesDestino;
    filas = filasNuevas;
    columnas = columnasNuevas;

    limpiarRelleno(tablero, totalNuevo, bytesReservados);

    if (!crece && debeReducirMemoria(totalNuevo, bytesReservados))
    {
        reducirMemoria(tablero, bytesReservados, bytesNecesarios);
    }

    return true;
}

bool InsertarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice > filas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, indice, 1, 0, 0);
}

bool EliminarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice >= filas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, indice, -1, 0, 0);
}

bool InsertarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice > columnas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, 0, 0, indice, 1);
}

bool EliminarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice >= columnas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, 0, 0, indice, -1);
}

void mostrarTablero(const unsigned char* tablero, int filas, int columnas, int bytesReservados)
{
    int totalPosiciones = filas * columnas;

    std::cout << "\nTablero:\n";

    for (int fila = 0; fila < filas; fila++)
    {
        for (int columna = 0; columna < columnas; columna++)
        {
            int posicion = filaColumnaPosicion(fila, columna, columnas);
            unsigned char ficha = obtenerFicha(tablero, posicion, totalPosiciones, bytesReservados);

            mostrarBitsFicha(ficha);
            std::cout << ' ';
        }

        std::cout << '\n';

        for (int columna = 0; columna < columnas; columna++)
        {
            int posicion = filaColumnaPosicion(fila, columna, columnas);
            unsigned char ficha = obtenerFicha(tablero, posicion, totalPosiciones, bytesReservados);

            std::cout << "  " << simboloFicha(ficha) << ' ';
        }

        std::cout << "\n\n";
    }
}
