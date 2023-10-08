#include "Repeticion.h"
#include <sstream>

void Repeticion::registrarMovimiento(char direccion) {
	movimientos.push_back(direccion);
}

const std::vector<char>& Repeticion::obtenerMovimientos() const {
	return movimientos;
}

void Repeticion::limpiarMovimientos() {
	movimientos.clear();
}

std::string Repeticion::serializar() const {
    std::string serialized = "REPETICION_START\n";  // Identificador de inicio
    for (char movimiento : movimientos) {
        serialized += movimiento;
    }
    serialized += "\nREPETICION_END\n";  // Identificador de finalizaci�n
    return serialized;
}

void Repeticion::deserializar(const std::string& datos) {
    std::istringstream ss(datos);
    std::string line;

    if (!std::getline(ss, line) || line != "REPETICION_START") {
        throw std::runtime_error("Datos de repetici�n no v�lidos: falta REPETICION_START.");
    }

    if (!std::getline(ss, line)) {
        throw std::runtime_error("Datos de repetici�n no v�lidos: falta la secuencia de movimientos.");
    }

    movimientos.clear();
    for (char movimiento : line) {
        if (movimiento == 'U' || movimiento == 'D' || movimiento == 'L' || movimiento == 'R') {
            movimientos.push_back(movimiento);
        }
        else {
            throw std::runtime_error("Movimiento no v�lido en la secuencia de repetici�n.");
        }
    }

    if (!std::getline(ss, line) || line != "REPETICION_END") {
        throw std::runtime_error("Datos de repetici�n no v�lidos: falta REPETICION_END.");
    }
}
