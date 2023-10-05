#pragma once

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "Tablero.h"
#include "Repeticion.h"
#include <string>
#include <vector>

class Archivo {
public:
	static std::vector<std::string> LeerArchivo(const std::string& nombreArchivo);
	static bool GuardarArchivo(const std::string& nombreArchivo, const std::vector<std::string>& contenido);
	static bool GuardarEstadoJuego(const std::string& nombreArchivo, const Tablero& tablero, int nivelActual, const Repeticion& repeticion);
	static bool CargarEstadoJuego(const std::string& nombreArchivo, Tablero& tablero, int& nivelActual, Repeticion& repeticion);
};

#endif
