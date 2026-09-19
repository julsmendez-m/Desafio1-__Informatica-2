#ifndef BITS_H
#define BITS_H

const int BITS_POR_FICHA = 3;
const unsigned char MASCARA_FICHA = 0x07;   // 0000 0111

const unsigned char F_CUADRADO   = 0;   // 000
const unsigned char F_HEXAGONO   = 1;   // 001
const unsigned char F_RECTANGULO = 2;   // 010
const unsigned char F_TRIANGULO  = 3;   // 011
const unsigned char F_ROMBO      = 4;   // 100
const unsigned char F_PENTAGONO  = 5;   // 101
const unsigned char F_VACIO      = 6;   // 110
const unsigned char F_ESPECIAL   = 7;   // 111

const unsigned char TIPOS_DE_FICHA = 6;

int calcularBytes(int totalPosiciones);

int calcularRelleno(int totalPosiciones, int bytesReservados);

int calcularBits(int posicion, int totalPosiciones, int bytesReservados);

unsigned char extraerFicha(const unsigned char* tablero, int bitInicial);

void guardarFicha(unsigned char* tablero, int bitInicial, unsigned char valor);

unsigned char obtenerFicha(const unsigned char* tablero, int posicion,int totalPosiciones, int bytesReservados);

void modificarFicha(unsigned char* tablero, int posicion, unsigned char valor,int totalPosiciones, int bytesReservados);

void limpiarRelleno(unsigned char* tablero, int totalPosiciones, int bytesReservados);

#endif