#ifndef MARCADOR_H
#define MARCADOR_H

// Cantidad minima de bytes para marcar totalPosiciones casillas.
int calcularBytesMarcador(int totalPosiciones);

// Pone todas las marcas en 0
void inicializarMarcador(unsigned char* marcador, int totalPosiciones);

// Enciende el bit de esa posicion
void marcarFicha(unsigned char* marcador, int posicion);

// Apaga el bit de esa posicion.
void desmarcarFicha(unsigned char* marcador, int posicion);

// Devuelve true si esa posicion esta marcada.
bool estaMarcada(const unsigned char* marcador, int posicion);

// Cuenta cuantas posiciones estan marcadas.
int contarFichasMarcadas(const unsigned char* marcador, int totalPosiciones);

// Llena 'posiciones' con los indices de las casillas marcadas, en orden,y devuelve cuantas escribio
int obtenerFichasMarcadas(const unsigned char* marcador,int totalPosiciones,int* posiciones);

#endif