#include "marcador.h"

int calcularBytesMarcador(int totalPosiciones)
{
    return (totalPosiciones + 7) >> 3;
}

void inicializarMarcador(unsigned char* marcador, int totalPosiciones)
{
    int bytes = calcularBytesMarcador(totalPosiciones);

    for (int i = 0; i < bytes; i++)
    {
        marcador[i] = 0;
    }
}

void reiniciarMarcador(unsigned char*& marcador, int totalPosiciones)
{
    delete[] marcador;
    marcador = new unsigned char[calcularBytesMarcador(totalPosiciones)];

    inicializarMarcador(marcador, totalPosiciones);
}

void marcarFicha(unsigned char* marcador, int posicion)
{
    if (posicion < 0)
        return;

    int indiceByte = posicion >> 3;
    unsigned char mascara = (unsigned char)(0x80 >> (posicion & 7));

    marcador[indiceByte] |= mascara;
}

void desmarcarFicha(unsigned char* marcador, int posicion)
{
    if (posicion < 0)
        return;

    int indiceByte = posicion >> 3;
    unsigned char mascara = (unsigned char)(0x80 >> (posicion & 7));

    marcador[indiceByte] &= (unsigned char)(~mascara);
}

bool estaMarcada(const unsigned char* marcador, int posicion)
{
    if (posicion < 0)
        return false;

    int indiceByte = posicion >> 3;
    unsigned char mascara = (unsigned char)(0x80 >> (posicion & 7));

    return (marcador[indiceByte] & mascara) != 0;
}

int contarFichasMarcadas(const unsigned char* marcador, int totalPosiciones)
{
    int cantidad = 0;

    for (int i = 0; i < totalPosiciones; i++)
    {
        if (estaMarcada(marcador, i))
        {
            cantidad++;
        }
    }

    return cantidad;
}


int obtenerFichasMarcadas(const unsigned char* marcador,int totalPosiciones,int* posiciones)
{
    int cantidad = 0;

    for (int i = 0; i < totalPosiciones; i++)
    {
        if (estaMarcada(marcador, i))
        {
            posiciones[cantidad] = i;
            cantidad++;
        }
    }

    return cantidad;
}