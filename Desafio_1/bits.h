#ifndef BITS_H
#define BITS_H

/* MODULO: bits
   Traduce entre la posicion logica de una ficha y su ubicacion
   fisica dentro de la secuencia continua de bits, y lee/escribe
   esos 3 bits.*/

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

// Cantidad minima de bytes para almacenar totalPosiciones fichas
int calcularBytes(int totalPosiciones);

// Bits sobrantes del bloque reservado. Quedan agrupados a la izquierda de toda la trama.
int calcularRelleno(int totalPosiciones, int bytesReservados);

// Indice global del primer bit de una ficha, contando desde el bit mas significativo del byte 0.
int calcularBits(int posicion, int totalPosiciones, int bytesReservados);

// Lee los 3 bits que empiezan en bitInicial (uso interno del modulo).
unsigned char extraerFicha(const unsigned char* tablero, int bitInicial);

// Escribe los 3 bits de valor a partir de bitInicial sin tocar las fichas vecinas (uso interno del modulo).
void guardarFicha(unsigned char* tablero, int bitInicial, unsigned char valor);

// Devuelve la ficha de una posicion logica. Si la posicion no existe devuelve F_ESPECIAL.
unsigned char obtenerFicha(const unsigned char* tablero, int posicion,int totalPosiciones, int bytesReservados);

// Cambia la ficha de una posicion logica. Si la posicion no existe no hace nada.
void modificarFicha(unsigned char* tablero, int posicion, unsigned char valor,int totalPosiciones, int bytesReservados);

// Pone en 0 los bits de relleno de la izquierda.
void limpiarRelleno(unsigned char* tablero, int totalPosiciones, int bytesReservados);

#endif