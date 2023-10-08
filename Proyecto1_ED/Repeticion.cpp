#include "Repeticion.h"

void Repeticion::registrarMovimiento(char direccion) {
	movimientos.push_back(direccion);
}

const std::vector<char>& Repeticion::obtenerMovimientos() const {
	return movimientos;
}

void Repeticion::limpiarMovimientos() {
	movimientos.clear();
}
