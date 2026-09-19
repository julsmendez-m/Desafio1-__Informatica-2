#ifndef MARCADOR_H
#define MARCADOR_H

int calcularBytesMarcador(int totalPosiciones);

void inicializarMarcador(unsigned char* marcador, int totalPosiciones);

void reiniciarMarcador(unsigned char*& marcador, int totalPosiciones);

void marcarFicha(unsigned char* marcador, int posicion);

void desmarcarFicha(unsigned char* marcador, int posicion);

bool estaMarcada(const unsigned char* marcador, int posicion);

int contarFichasMarcadas(const unsigned char* marcador, int totalPosiciones);

int obtenerFichasMarcadas(const unsigned char* marcador,int totalPosiciones,int* posiciones);

#endif