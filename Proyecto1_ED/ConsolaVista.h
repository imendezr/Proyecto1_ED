#pragma once

#ifndef CONSOLAVISTA_H
#define CONSOLAVISTA_H

#include "IVista.h"

class ConsolaVista : public IVista {
public:
	ConsolaVista();

	void MostrarTablero(const Tablero& tablero) override;
	void MostrarMensaje(const std::string& mensaje) override;
	char SolicitarEntrada(const std::string& mensaje) override;
	char MostrarMenu() override;
	void MostrarInstrucciones();
};

#endif
