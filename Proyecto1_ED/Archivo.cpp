#include "Archivo.h"
#include <fstream>

std::vector<std::string> Archivo::LeerArchivo(const std::string& nombreArchivo) {
	std::vector<std::string> contenido;
	std::ifstream archivo(nombreArchivo); // Abre el archivo en modo lectura

	if (!archivo.is_open()) {
		// Si el archivo no se pudo abrir, retorna un vector vacío
		return contenido;
	}

	std::string linea;
	while (getline(archivo, linea)) {
		// Lee cada línea y la agrega al vector contenido
		contenido.push_back(linea);
	}

	archivo.close();
	return contenido;
}

bool Archivo::GuardarArchivo(const std::string& nombreArchivo, const std::vector<std::string>& contenido) {
	std::ofstream archivo(nombreArchivo); // Abre el archivo en modo escritura

	if (!archivo.is_open()) {
		// Si el archivo no se pudo abrir, retorna false
		return false;
	}

	for (const std::string& linea : contenido) {
		// Escribe cada línea en el archivo
		archivo << linea << "\n";
	}

	archivo.close();
	return true;
}

/* Expandir esta clase con funciones adicionales como por ejemplo:
guardar y cargar el estado del juego(posición del jugador, estado de las cajas, nivel actual, etc.) */