#include "bits.h"

int calcularBytes(int totalPosiciones)
{
    int totalBits = totalPosiciones * BITS_POR_FICHA;
    return (totalBits + 7) >> 3;
}

int calcularRelleno(int totalPosiciones)
{
    int totalBits = totalPosiciones * BITS_POR_FICHA;
    return (calcularBytes(totalPosiciones) << 3) - totalBits;
}


int calcularBits(int posicion, int totalPosiciones)
{
    return calcularRelleno(totalPosiciones) + posicion * BITS_POR_FICHA;
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

    int bitsEnPrimero = 8 - desplazado;      // 2 o 1
    int bitsEnSegundo = 3 - bitsEnPrimero;   // 1 o 2

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

    // Primer byte: recibe los bits MAS significativos de la ficha
    unsigned char mascara1 = (unsigned char)((1 << bitsEnPrimero) - 1);
    tablero[indiceByte] &= (unsigned char)(~mascara1);
    tablero[indiceByte] |= (unsigned char)((valor >> bitsEnSegundo) & mascara1);

    // Segundo byte: recibe los bits MENOS significativos
    unsigned char mascara2 = (unsigned char)(((1 << bitsEnSegundo) - 1) << (8 - bitsEnSegundo));
    tablero[indiceByte + 1] &= (unsigned char)(~mascara2);
    tablero[indiceByte + 1] |= (unsigned char)((valor << (8 - bitsEnSegundo)) & mascara2);
}


unsigned char obtenerFicha(const unsigned char* tablero,int posicion,int totalPosiciones)
{
    if (posicion < 0 || posicion >= totalPosiciones)
        return F_ESPECIAL;

    return extraerFicha(tablero, calcularBits(posicion, totalPosiciones));
}


void modificarFicha(unsigned char* tablero,int posicion,unsigned char valor,int totalPosiciones)
{
    if (posicion < 0 || posicion >= totalPosiciones)
        return;

    guardarFicha(tablero, calcularBits(posicion, totalPosiciones), valor);
}
