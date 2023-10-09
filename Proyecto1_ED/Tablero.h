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
	std::stack<std::pair<int, int>> cajasEnObjetivo;
	int filas, columnas;

	bool esPosicionValida(int, int);
	bool puedeMoverseA(int, int);

public:
	Tablero();

	ListaEnlazada<char> getTablero() const;
	int getFilas() const;
	int getColumnas() const;

	bool cargarDesdeArchivo(const std::string&);
	bool moverCaja(int, int, int, int);
	bool moverJugador(char); // 'U' para arriba (up), 'D' para abajo (down), 'L' para la izquierda (left), 'R' para la derecha (right)
	bool verificarVictoria();

	std::string serializar() const;
	void deserializar(const std::string&);

};

#endif
