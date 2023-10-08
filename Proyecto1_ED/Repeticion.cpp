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
    std::string serializado = "REPETICION_START\n";  // Identificador de inicio
    for (char movimiento : movimientos) {
        serializado += movimiento;
    }
    serializado += "\nREPETICION_END\n";  // Identificador de finalización
    return serializado;
}

void Repeticion::deserializar(const std::string& datos) {
    std::istringstream ss(datos);
    std::string linea;

    if (!std::getline(ss, linea) || linea != "REPETICION_START") {
        throw std::runtime_error("Datos de repetición no válidos: falta REPETICION_START.");
    }

    if (!std::getline(ss, linea)) {
        throw std::runtime_error("Datos de repetición no válidos: falta la secuencia de movimientos.");
    }

    movimientos.clear();
    for (char movimiento : linea) {
        if (movimiento == 'U' || movimiento == 'D' || movimiento == 'L' || movimiento == 'R') {
            movimientos.push_back(movimiento);
        }
        else {
            throw std::runtime_error("Movimiento no válido en la secuencia de repetición.");
        }
    }

    if (!std::getline(ss, linea) || linea != "REPETICION_END") {
        throw std::runtime_error("Datos de repetición no válidos: falta REPETICION_END.");
    }
}
