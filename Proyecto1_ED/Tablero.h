#pragma once

#ifndef TABLERO_H
#define TABLERO_H

#include "ListaEnlazada.h"
#include "Caja.h"
#include "Jugador.h"
#include <vector>
#include <stack>
#include <string>

class Tablero {
private:
	ListaEnlazada<char> tablero;
	Jugador jugador;
	std::vector<Caja> cajas;
	std::stack<Caja> cajasEnObjetivo;
	std::vector<char> movimientos; // Guarda los movimientos para la repetición
	int filas, columnas;

	// Funciones auxiliares
	bool EsPosicionValida(int fila, int columna);
	bool PuedeMoverseA(int fila, int columna);

public:
	Tablero();

	bool CargarDesdeArchivo(const std::string& nombreArchivo);
	bool MoverJugador(char direccion); // 'U' para arriba, 'D' para abajo, 'L' para izquierda, 'R' para derecha
	bool VerificarVictoria();
	void MostrarTablero();
};

#endif
