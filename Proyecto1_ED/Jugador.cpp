#include "Jugador.h"

Jugador::Jugador(int filaInicial, int columnaInicial)
	: fila(filaInicial), columna(columnaInicial) {}

int Jugador::GetFila() const {
	return fila;
}

int Jugador::GetColumna() const {
	return columna;
}

void Jugador::SetPosicion(int nuevaFila, int nuevaColumna) {
	fila = nuevaFila;
	columna = nuevaColumna;
}
