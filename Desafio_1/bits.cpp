#include "bits.h"

int calcularBytes(int totalPosiciones)
{
    int totalBits = totalPosiciones * BITS_POR_FICHA;
    return (totalBits + 7) >> 3;
}

int calcularRelleno(int totalPosiciones, int bytesReservados)
{
    int totalBits = totalPosiciones * BITS_POR_FICHA;
    return (bytesReservados << 3) - totalBits;
}

int calcularBits(int posicion, int totalPosiciones, int bytesReservados)
{
    return calcularRelleno(totalPosiciones, bytesReservados) + posicion * BITS_POR_FICHA;
}


unsigned char extraerFicha(const unsigned char* tablero, int bitInicial)
{
    int indiceByte = bitInicial >> 3;
    int desplazado = bitInicial & 7;

    if (desplazado <= 5)
    {
        int corrimiento = 5 - desplazado;
        return (tablero[indiceByte] >> corrimiento) & MASCARA_FICHA;
    }

    int bitsEnPrimero = 8 - desplazado;
    int bitsEnSegundo = 3 - bitsEnPrimero;

    unsigned char parteAlta = tablero[indiceByte] & (unsigned char)((1 << bitsEnPrimero) - 1);
    unsigned char parteBaja = tablero[indiceByte + 1] >> (8 - bitsEnSegundo);

    return (unsigned char)(((parteAlta << bitsEnSegundo) | parteBaja) & MASCARA_FICHA);
}

void guardarFicha(unsigned char* tablero, int bitInicial, unsigned char valor)
{
    valor &= MASCARA_FICHA;

    int indiceByte = bitInicial >> 3;
    int desplazado = bitInicial & 7;

    if (desplazado <= 5)
    {
        int corrimiento = 5 - desplazado;
        unsigned char mascara = (unsigned char)(MASCARA_FICHA << corrimiento);

        tablero[indiceByte] &= (unsigned char)(~mascara);
        tablero[indiceByte] |= (unsigned char)(valor << corrimiento);
        return;
    }

    int bitsEnPrimero = 8 - desplazado;
    int bitsEnSegundo = 3 - bitsEnPrimero;


    unsigned char mascara1 = (unsigned char)((1 << bitsEnPrimero) - 1);
    tablero[indiceByte] &= (unsigned char)(~mascara1);
    tablero[indiceByte] |= (unsigned char)((valor >> bitsEnSegundo) & mascara1);

    unsigned char mascara2 = (unsigned char)(((1 << bitsEnSegundo) - 1) << (8 - bitsEnSegundo));
    tablero[indiceByte + 1] &= (unsigned char)(~mascara2);
    tablero[indiceByte + 1] |= (unsigned char)((valor << (8 - bitsEnSegundo)) & mascara2);
}


unsigned char obtenerFicha(const unsigned char* tablero, int posicion,int totalPosiciones, int bytesReservados)
{
    if (posicion < 0 || posicion >= totalPosiciones)
        return F_ESPECIAL;

    return extraerFicha(tablero, calcularBits(posicion, totalPosiciones, bytesReservados));
}


void modificarFicha(unsigned char* tablero, int posicion, unsigned char valor,int totalPosiciones, int bytesReservados)
{
    if (posicion < 0 || posicion >= totalPosiciones)
        return;

    guardarFicha(tablero, calcularBits(posicion, totalPosiciones, bytesReservados), valor);
}

void limpiarRelleno(unsigned char* tablero, int totalPosiciones, int bytesReservados)
{
    int relleno = calcularRelleno(totalPosiciones, bytesReservados);
    int bytesCompletos = relleno >> 3;
    int bitsSueltos = relleno & 7;

    for (int i = 0; i < bytesCompletos; i++)
    {
        tablero[i] = 0;
    }

    if (bitsSueltos > 0)
    {
        unsigned char mascara = (unsigned char)((1 << (8 - bitsSueltos)) - 1);
        tablero[bytesCompletos] &= mascara;
    }
}