#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "marcador.h"
#include "combinaciones.h"
#include "eliminacion.h"
#include "gravedad.h"
#include "generacion.h"
#include "estadisticas.h"
#include "posicion.h"

int leerEntero(const char* mensaje, int minimo, int maximo)
{
    int valor;

    while (true)
    {
        std::cout << mensaje;
        std::cin >> valor;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        if (valor < minimo || valor > maximo)
        {
            std::cout << "Valor fuera de rango [" << minimo << ", " << maximo << "].\n";
            continue;
        }

        return valor;
    }
}

void iniciarJuego(unsigned char*& tablero, int& filas, int& columnas, int& bytesReservados,unsigned char*& marcador, int* estadisticas)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "\n===== SWEET CRUSH =====\n";
    std::cout << "\n===== NUEVO JUEGO =====\n";
    std::cout << "Elige el tamano de tu tablero.\n";

    filas    = leerEntero("Filas : ", 3, 20);
    columnas = leerEntero("Columnas : ", 3, 20);

    crearTablero(tablero, filas, columnas, bytesReservados);
    reiniciarMarcador(marcador, filas * columnas);
    inicializarEstadisticas(estadisticas);

    RellenarEspaciosVacios(tablero, filas, columnas, bytesReservados);
    std::cout << "\nFichas: C=Cuadrado H=Hexagono R=Rectangulo T=Triangulo O=Rombo P=Pentagono .=Vacio\n";

}

void procesarCascadas(unsigned char* tablero, int filas, int columnas, int bytesReservados,unsigned char* marcador, int* estadisticas)
{
    AplicarGravedad(tablero, filas, columnas, bytesReservados);
    GenerarNuevasFichas(tablero, filas, columnas, bytesReservados);

    int combinaciones;
    int numeroCascada = 0;

    while ((combinaciones = BuscarCombinaciones(tablero, filas, columnas, bytesReservados, marcador)) > 0)
    {
        numeroCascada++;

        int eliminadas = EliminarFichasMarcadas(tablero, filas, columnas, bytesReservados, marcador);

        std::cout << "Cascada " << numeroCascada << ": " << combinaciones<< " combinacion(es), " << eliminadas << " ficha(s) eliminada(s).\n";
        actualizarEstadisticas(estadisticas, eliminadas, combinaciones, true);

        AplicarGravedad(tablero, filas, columnas, bytesReservados);
        GenerarNuevasFichas(tablero, filas, columnas, bytesReservados);
    }
}

void mostrarMenu()
{
    std::cout << "\n===== MENU =====\n";
    std::cout << "1) Eliminar ficha\n";
    std::cout << "2) Insertar fila\n";
    std::cout << "3) Eliminar fila\n";
    std::cout << "4) Insertar columna\n";
    std::cout << "5) Eliminar columna\n";
    std::cout << "0) Salir\n";
}

void jugadaEliminarFicha(unsigned char* tablero, int filas, int columnas, int bytesReservados,unsigned char* marcador, int* estadisticas)
{
    std::cout << "Fila (0 a " << filas - 1 << ")\n";
    int fila = leerEntero("Fila: ", 0, filas - 1);

    std::cout << "Columna (0 a " << columnas - 1 << ")\n";
    int columna = leerEntero("Columna: ", 0, columnas - 1);

    int posicion = filaColumnaPosicion(fila, columna, columnas);

    if (!EliminarFicha(tablero, posicion, filas * columnas, bytesReservados))
    {
        std::cout << "Esa posicion ya estaba vacia.\n";
        return;
    }

    std::cout << "Ficha eliminada en fila " << fila << ", columna " << columna << ".\n";

    registrarMovimiento(estadisticas);
    registrarFichaEliminada(estadisticas, 1);
    actualizarPuntuacion(estadisticas, 1, false);

    procesarCascadas(tablero, filas, columnas, bytesReservados, marcador, estadisticas);
}

void jugadaCambiarEstructura(unsigned char*& tablero, int& filas, int& columnas, int& bytesReservados,unsigned char*& marcador, int* estadisticas, int opcion)
{
    bool operacionOk = false;

    if (opcion == 2)
    {
        std::cout << "Indice de la fila a insertar (0 a " << filas << ")\n";
        int indice = leerEntero("Indice: ", 0, filas);
        operacionOk = InsertarFila(tablero, filas, columnas, bytesReservados, indice);
    }
    else if (opcion == 3)
    {
        std::cout << "Indice de la fila a eliminar (0 a " << filas - 1 << ")\n";
        int indice = leerEntero("Indice: ", 0, filas - 1);
        operacionOk = EliminarFila(tablero, filas, columnas, bytesReservados, indice);
    }
    else if (opcion == 4)
    {
        std::cout << "Indice de la columna a insertar (0 a " << columnas << ")\n";
        int indice = leerEntero("Indice: ", 0, columnas);
        operacionOk = InsertarColumna(tablero, filas, columnas, bytesReservados, indice);
    }
    else if (opcion == 5)
    {
        std::cout << "Indice de la columna a eliminar (0 a " << columnas - 1 << ")\n";
        int indice = leerEntero("Indice: ", 0, columnas - 1);
        operacionOk = EliminarColumna(tablero, filas, columnas, bytesReservados, indice);
    }
    if (!operacionOk)
    {
        std::cout << "No se pudo realizar la operacion.\n";
        return;
    }

    std::cout << "Operacion realizada. El tablero ahora es de " << filas << " x " << columnas << ".\n";

    reiniciarMarcador(marcador, filas * columnas);

    estadisticas[EST_CASCADAS_JUGADA] = 0;

    procesarCascadas(tablero, filas, columnas, bytesReservados, marcador, estadisticas);
}


int main()
{
    unsigned char* tablero = nullptr;
    unsigned char* marcador = nullptr;
    int filas = 0;
    int columnas = 0;
    int bytesReservados = 0;
    int estadisticas[TOTAL_ESTADISTICAS];

    iniciarJuego(tablero, filas, columnas, bytesReservados, marcador, estadisticas);

    int opcion = -1;

    while (opcion != 0)
    {
        mostrarTableroFichas(tablero, filas, columnas, bytesReservados);
        mostrarTableroBinario(tablero, filas, columnas, bytesReservados);
        mostrarEstadisticas(estadisticas, filas, columnas);
        mostrarMenu();
        opcion = leerEntero("Opcion: ", 0, 5);

        if (opcion == 1)
            jugadaEliminarFicha(tablero, filas, columnas, bytesReservados, marcador, estadisticas);
        else if (opcion >= 2)
            jugadaCambiarEstructura(tablero, filas, columnas, bytesReservados, marcador, estadisticas, opcion);
    }

    delete[] marcador;
    liberarTablero(tablero, bytesReservados);

    return 0;
}
