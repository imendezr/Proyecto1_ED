#pragma once

#ifndef CAJA_H
#define CAJA_H

class Caja {
private:
	int fila;
	int columna;

public:
	// Constructor
	Caja(int filaInicial, int columnaInicial);

	// Métodos getter y setter
	int GetFila() const;
	int GetColumna() const;

	void SetPosicion(int nuevaFila, int nuevaColumna);
};

#endif
