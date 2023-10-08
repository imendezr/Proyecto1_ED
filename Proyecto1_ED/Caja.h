#pragma once

#ifndef CAJA_H
#define CAJA_H

class Caja {
private:
	int fila;
	int columna;
	char celdaPrevia;

public:
	Caja(int, int);

	int getFila() const;
	int getColumna() const;

	char getCeldaPrevia() const;
	void setCeldaPrevia(char);

	void setPosicion(int, int);
};

#endif
