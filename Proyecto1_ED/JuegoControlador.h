#pragma once

#ifndef JUEGOCONTROLADOR_H
#define JUEGOCONTROLADOR_H

#include "Tablero.h"
#include <string>

class JuegoControlador {
private:
	Tablero tableroActual;
	int nivelActual;
	bool juegoEnProgreso;

	void CargarNivel(int nivel);
	void MostrarMenu();
	void MostrarInstrucciones();
	void ManejarEntrada(char entrada);
	void ReiniciarNivel();
	void MostrarRepeticion();

public:
	JuegoControlador();
	void IniciarJuego();
};

#endif
