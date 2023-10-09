#include "Archivo.h"
#include <fstream>

std::vector<std::string> Archivo::leerArchivo(const std::string& nombreArchivo) {
	std::vector<std::string> contenido;
	std::ifstream archivo(nombreArchivo); // Abre el archivo en modo lectura

	if (!archivo.is_open()) {
		// Si el archivo no se pudo abrir, retorna un vector vacío
		return contenido;
	}

	std::string linea;
	while (getline(archivo, linea)) {
		// Lee cada línea y la agrega al vector
		contenido.push_back(linea);
	}

	archivo.close();
	return contenido;
}

bool Archivo::guardarArchivo(const std::string& nombreArchivo, const std::vector<std::string>& contenido) {
	std::ofstream archivo(nombreArchivo); // Abre el archivo en modo escritura

	if (!archivo.is_open()) {
		// Si el archivo no se pudo abrir
		return false;
	}

	for (const std::string& linea : contenido) {
		// Escribe cada línea en el archivo
		archivo << linea << "\n";
	}

	archivo.close();
	return true;
}

bool Archivo::guardarEstadoJuego(const std::string& nombreArchivo, const Tablero& tablero, int nivelActual, const Repeticion& repeticion) {
	std::ofstream archivo(nombreArchivo);
	if (!archivo.is_open()) {
		return false;
	}

	archivo << nivelActual << "\n";
	archivo << tablero.serializar();
	archivo << repeticion.serializar();

	archivo.close();
	return true;
}

bool Archivo::cargarEstadoJuego(const std::string& nombreArchivo, Tablero& tablero, int& nivelActual, Repeticion& repeticion) {
	std::ifstream archivo(nombreArchivo);
	if (!archivo.is_open()) {
		return false;
	}

	// Leer nivel
	archivo >> nivelActual;
	archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar el resto de la línea

	// Leer contenido del archivo
	std::string contenido((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());

	// Dividir el contenido en partes del tablero y de la repetición
	auto tableroStart = contenido.find("TABLERO_START");
	auto tableroEnd = contenido.find("TABLERO_END");

	if (tableroStart == std::string::npos || tableroEnd == std::string::npos) {
		throw std::runtime_error("Archivo de guardado no válido.");
	}

	// +12 para incluir "TABLERO_END\n"
	std::string datosTablero = contenido.substr(tableroStart, tableroEnd + 12 - tableroStart);
	std::string datosRepeticion = contenido.substr(tableroEnd + 12);  // El resto después del tablero

	tablero.deserializar(datosTablero);
	repeticion.deserializar(datosRepeticion);

	archivo.close();
	return true;
}
