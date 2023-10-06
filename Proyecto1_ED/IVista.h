#pragma once

#ifndef IVISTA_H
#define IVISTA_H

#include "Tablero.h"

class IVista {
public:
	virtual ~IVista() = default;

	virtual void MostrarTablero(const Tablero& tablero) = 0;
	virtual void MostrarMensaje(const std::string& mensaje) = 0;
	virtual char SolicitarEntrada(const std::string& mensaje) = 0;
	virtual char MostrarMenu() = 0;
};

#endif
