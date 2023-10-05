#pragma once

#ifndef CONSOLAVISTA_H
#define CONSOLAVISTA_H

#include "IVista.h"

class ConsolaVista : public IVista {
public:
	ConsolaVista(); // Constructor si es necesario

	// Implementa los métodos virtuales puros de IVista
	void MostrarTablero(const Tablero& tablero) override;
	void MostrarMensaje(const std::string& mensaje) override;
	char SolicitarEntrada(const std::string& mensaje) override;

	// Otros miembros y funciones si es necesario
};

#endif
