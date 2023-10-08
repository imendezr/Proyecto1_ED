#pragma once

#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
private:
	int fila;
	int columna;
	char celdaPrevia;

public:
	Jugador(int, int);

	int getFila() const;
	int getColumna() const;

	char getCeldaPrevia() const;
	void setCeldaPrevia(char);

	void setPosicion(int, int);
};

#endif
