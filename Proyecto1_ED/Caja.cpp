#include "Caja.h"

Caja::Caja(int filaInicial, int columnaInicial)
	: fila(filaInicial), columna(columnaInicial), celdaPrevia(' ') {}

int Caja::getFila() const {
	return fila;
}

int Caja::getColumna() const {
	return columna;
}

char Caja::getCeldaPrevia() const {
	return celdaPrevia;
}

void Caja::setCeldaPrevia(char celda) {
	celdaPrevia = celda;
}

void Caja::setPosicion(int nuevaFila, int nuevaColumna) {
	fila = nuevaFila;
	columna = nuevaColumna;
}
