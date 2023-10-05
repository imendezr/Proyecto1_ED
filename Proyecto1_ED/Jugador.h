#pragma once

#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
private:
	int fila;
	int columna;

public:
	// Constructor
	Jugador(int filaInicial, int columnaInicial);

	// Métodos getter y setter
	int GetFila() const;
	int GetColumna() const;

	void SetPosicion(int nuevaFila, int nuevaColumna);
};

#endif
