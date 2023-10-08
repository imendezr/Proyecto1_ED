#pragma once

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "Tablero.h"
#include "Repeticion.h"
#include <string>
#include <vector>

class Archivo {
public:
	static std::vector<std::string> leerArchivo(const std::string&);
	static bool guardarArchivo(const std::string&, const std::vector<std::string>&);
	static bool guardarEstadoJuego(const std::string&, const Tablero&, int, const Repeticion&);
	static bool cargarEstadoJuego(const std::string&, Tablero&, int&, Repeticion&);
};

#endif
