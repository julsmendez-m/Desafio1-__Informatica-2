#ifndef TABLERO_H
#define TABLERO_H

void crearTablero(unsigned char*& tablero, int filas, int columnas, int& bytesReservados);

void LimpiarTablero(unsigned char* tablero, int filas, int columnas, int bytesReservados);

void liberarTablero(unsigned char*& tablero, int& bytesReservados);

bool debeReducirMemoria(int totalPosiciones, int bytesReservados);

bool ReorganizarTablero(unsigned char*& tablero, int& filas, int& columnas, int& bytesReservados,int indiceFila, int cambioFila, int indiceColumna, int cambioColumna);

bool InsertarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice);

bool EliminarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice);

bool InsertarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice);

bool EliminarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice);

void mostrarTablero(const unsigned char* tablero, int filas, int columnas, int bytesReservados);

#endif