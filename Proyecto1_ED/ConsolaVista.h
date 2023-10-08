#pragma once

#ifndef CONSOLAVISTA_H
#define CONSOLAVISTA_H

#include "IVista.h"

class ConsolaVista : public IVista {
public:
	ConsolaVista();

	void mostrarTablero(const Tablero&) override;
	void mostrarMensaje(const std::string&) override;
	char solicitarEntrada(const std::string&) override;
	char mostrarMenu() override;
	void mostrarInstrucciones();
};

#endif
