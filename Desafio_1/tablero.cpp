#include "tablero.h"
#include "bits.h"

// Porcentaje minimo de ocupacion antes de reducir la memoria.
const int PORCENTAJE_MINIMO = 65;


// Reserva exactamente los bytes necesarios y los deja vacios.
void crearTablero(unsigned char*& tablero, int filas, int columnas, int& bytesReservados)
{
    bytesReservados = calcularBytes(filas * columnas);

    tablero = new unsigned char[bytesReservados];

    LimpiarTablero(tablero, filas, columnas, bytesReservados);
}

// Pone todos los bytes en 0 y luego escribe el codigo de vacio en cada posicion.
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

// Libera el bloque y deja el puntero y el tamano en 0.
void liberarTablero(unsigned char*& tablero, int& bytesReservados)
{
    delete[] tablero;
    tablero = nullptr;
    bytesReservados = 0;
}

// Se compara que ocupacion < 65 %.
bool debeReducirMemoria(int totalPosiciones, int bytesReservados)
{
    int bitsUsados = totalPosiciones * BITS_POR_FICHA;
    int bitsReservados = bytesReservados << 3;

    return bitsUsados * 100 < bitsReservados * PORCENTAJE_MINIMO;
}

// Dada una fila (o columna) del tablero nuevo, devuelve cual era en el tablero viejo
// Devuelve -1 si es la fila/columna recien insertada.
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

// las fichas estan pegadas al bit menos significativo, entonces el bloque minimo
// son los ultimos 'bytesNuevos' bytes del bloque actual
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

// Nucleo de las 4 operaciones. Recorre las posiciones del tablero, busca
// de que posicion vieja viene cada una y copia sus 3 bits.
//
// Si el tablero crece y ya no cabe, se reserva un bloque nuevo del tamano justo.
// Si cabe, se trabaja sobre el mismo bloque:
//  - Al insertar, cada ficha se mueve hacia la izquierda o se queda
//  - Al eliminar, cada ficha se mueve hacia la derecha o se queda
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

    // Al eliminar quedan restos de fichas viejas a la izquierda y se borran.
    limpiarRelleno(tablero, totalNuevo, bytesReservados);

    if (!crece && debeReducirMemoria(totalNuevo, bytesReservados))
    {
        reducirMemoria(tablero, bytesReservados, bytesNecesarios);
    }

    return true;
}

// Inserta una fila vacia en 'indice'. Si indice == filas, queda al final.
bool InsertarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice > filas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, indice, 1, 0, 0);
}

// Elimina la fila 'indice'.
bool EliminarFila(unsigned char*& tablero, int& filas, int columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice >= filas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, indice, -1, 0, 0);
}

// Inserta una columna vacia en 'indice'. Si indice == columnas, queda al final.
bool InsertarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice > columnas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, 0, 0, indice, 1);
}

// Elimina la columna 'indice'.
bool EliminarColumna(unsigned char*& tablero, int filas, int& columnas, int& bytesReservados, int indice)
{
    if (indice < 0 || indice >= columnas)
        return false;

    return ReorganizarTablero(tablero, filas, columnas, bytesReservados, 0, 0, indice, -1);
}