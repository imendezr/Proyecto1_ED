#include "Caja.h"

Caja::Caja(int filaInicial, int columnaInicial)
	: fila(filaInicial), columna(columnaInicial) {}

int Caja::GetFila() const {
	return fila;
}

int Caja::GetColumna() const {
	return columna;
}

void Caja::SetPosicion(int nuevaFila, int nuevaColumna) {
	fila = nuevaFila;
	columna = nuevaColumna;
}
