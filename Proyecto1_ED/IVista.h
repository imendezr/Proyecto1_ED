#pragma once

#ifndef IVISTA_H
#define IVISTA_H

#include "Tablero.h"

class IVista {
public:
	virtual ~IVista() = default;

	virtual void mostrarTablero(const Tablero&) = 0;
	virtual void mostrarMensaje(const std::string&) = 0;
	virtual char solicitarEntrada(const std::string&) = 0;
	virtual char mostrarMenu() = 0;
};

#endif
