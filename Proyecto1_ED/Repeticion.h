#pragma once

#ifndef REPETICION_H
#define REPETICION_H

#include <vector>

class Repeticion {
private:
	std::vector<char> movimientos; // Guarda los movimientos para la repetición

public:
	void RegistrarMovimiento(char direccion);
	const std::vector<char>& ObtenerMovimientos() const;
	void LimpiarMovimientos();
};

#endif
