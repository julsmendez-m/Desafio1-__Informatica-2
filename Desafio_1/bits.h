#ifndef BITS_H
#define BITS_H

/* MODULO: bits
   Traduce entre la posicion logica de una ficha y su ubicacion
   fisica dentro de la secuencia continua de bits, y lee/escribe
   esos 3 bits.*/

//Codificacion de las fichas
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

// Bits sobrante. Quedan agrupados a la izquierda del byte
int calcularRelleno(int totalPosiciones);

// Indice global del primer bit de una ficha, contando desde el bit mas significativo del byte 0.
int calcularBits(int posicion, int totalPosiciones);

// Conversiones entre (fila, columna) y posicion lineal.
int filaColumnaPosicion(int fila, int columna, int columnas);
int posicionFila(int posicion, int columnas);
int posicionColumna(int posicion, int columnas);


// ---------- Bajo nivel: uso interno del modulo ----------

unsigned char extraerFicha(const unsigned char* tablero, int bitInicial);
void guardarFicha(unsigned char* tablero, int bitInicial, unsigned char valor);


// ---------- Alto nivel: lo que usan los demas modulos ----------

unsigned char obtenerFicha(const unsigned char* tablero,int posicion,int totalPosiciones);

void modificarFicha(unsigned char* tablero,int posicion,unsigned char valor,int totalPosiciones);

#endif
