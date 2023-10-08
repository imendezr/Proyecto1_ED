#include "Jugador.h"

Jugador::Jugador(int filaInicial, int columnaInicial)
	: fila(filaInicial), columna(columnaInicial), celdaPrevia(' ') {}

int Jugador::getFila() const {
	return fila;
}

int Jugador::getColumna() const {
	return columna;
}

char Jugador::getCeldaPrevia() const {
	return celdaPrevia;
}

void Jugador::setCeldaPrevia(char celda) {
	celdaPrevia = celda;
}

void Jugador::setPosicion(int nuevaFila, int nuevaColumna) {
	fila = nuevaFila;
	columna = nuevaColumna;
}
