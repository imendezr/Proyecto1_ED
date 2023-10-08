#pragma once

#ifndef REPETICION_H
#define REPETICION_H

#include <vector>
#include <string>

class Repeticion {
private:
	std::vector<char> movimientos;

public:
	void registrarMovimiento(char);
	const std::vector<char>& obtenerMovimientos() const;
	void limpiarMovimientos();

	std::string serializar() const;
	void deserializar(const std::string&);
};

#endif
