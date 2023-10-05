#include "Repeticion.h"

void Repeticion::RegistrarMovimiento(char direccion) {
	movimientos.push_back(direccion);
}

const std::vector<char>& Repeticion::ObtenerMovimientos() const {
	return movimientos;
}

void Repeticion::LimpiarMovimientos() {
	movimientos.clear();
}
