#include "Tablero.h"
#include "Archivo.h"
#include <utility>
#include <sstream>

Tablero::Tablero() : jugador(0, 0), filas(0), columnas(0) {
	// Se podría cargar un nivel por defecto o dejar el tablero vacío
}

ListaEnlazada<char> Tablero::getTablero() const { return tablero; }

int Tablero::getFilas() const { return filas; }

int Tablero::getColumnas() const { return columnas; }

bool Tablero::esPosicionValida(int fila, int columna) {
	return fila >= 0 && fila < filas && columna >= 0 && columna < columnas;
}

bool Tablero::puedeMoverseA(int fila, int columna) {
	char celdaDestino = tablero.obtenerNodo(fila, columna)->valor;

	return (celdaDestino == ' ' || celdaDestino == '.');
}

bool Tablero::cargarDesdeArchivo(const std::string& nombreArchivo) {
	// Limpieza antes de cargar
	tablero.borrarLista();
	cajas.clear();
	jugador.setPosicion(0, 0);
	jugador.setCeldaPrevia(' ');

	auto contenido = Archivo::leerArchivo(nombreArchivo);

	if (contenido.empty()) {
		return false; // No se pudo leer el archivo correctamente
	}

	// Limpieza de datos residuales
	tablero.borrarLista(); // Limpia el tablero actual
	cajas.clear(); // Limpia las cajas actuales
	while (!cajasEnObjetivo.empty()) { // Limpia las cajas en objetivos
		cajasEnObjetivo.pop();
	}
	jugador.setPosicion(0, 0); // Restablece la posición del jugador
	jugador.setCeldaPrevia(' '); // Restablece la celda previa del jugador

	int longitudLinea = contenido[0].size();
	int contadorJugador = 0;

	for (int fila = 0; fila < contenido.size(); ++fila) {
		auto linea = contenido[fila];

		if (linea.size() != longitudLinea) {
			// Las líneas tienen diferentes longitudes, archivo no es válido
			return false;
		}

		std::vector<char> filaParaTablero;

		for (int columna = 0; columna < linea.size(); ++columna) {
			char celda = linea[columna];
			filaParaTablero.push_back(celda);

			if (celda == '@') {
				contadorJugador++;
				jugador.setPosicion(fila, columna);
			}
			else if (celda == '$') {
				Caja nuevaCaja(fila, columna);
				nuevaCaja.setCeldaPrevia(' ');  // Inicialmente las cajas no están en objetivos
				cajas.push_back(nuevaCaja);
			}
			else if (celda == '!') {
				Caja nuevaCaja(fila, columna);
				nuevaCaja.setCeldaPrevia('.');  // La caja está en una posición objetivo
				cajas.push_back(nuevaCaja);
				cajasEnObjetivo.push({ fila, columna });
			}
			else if (celda != ' ' && celda != '.' && celda != '#' && celda != '!') {
				// Char inesperado en el tablero
				return false;
			}
		}

		tablero.insertarFila(filaParaTablero);
	}

	if (contadorJugador != 1) {
		// Debe haber exactamente un jugador en el tablero
		return false;
	}

	filas = contenido.size();
	columnas = longitudLinea;

	return true;
}

bool Tablero::moverCaja(int filaActual, int columnaActual, int filaDeseada, int columnaDeseada) {
	char celdaDetrasCaja = tablero.obtenerNodo(filaDeseada, columnaDeseada)->valor;

	if (celdaDetrasCaja == ' ' || celdaDetrasCaja == '.') {
		char celdaActual = tablero.obtenerNodo(filaActual, columnaActual)->valor;

		// Si la caja está siendo movida a una posición objetivo
		if (celdaDetrasCaja == '.') {
			cajasEnObjetivo.push({ filaActual, columnaActual });
		}

		// Si la caja estaba previamente en una posición objetivo y se está moviendo fuera de ella
		if (celdaActual == '!') {
			if (!cajasEnObjetivo.empty() && cajasEnObjetivo.top() == std::make_pair(filaActual, columnaActual)) {
				cajasEnObjetivo.pop();
			}
			else {
				// Si la caja no está en la parte superior, buscaremos y eliminaremos manualmente
				std::stack<std::pair<int, int>> tempStack;
				while (!cajasEnObjetivo.empty() && cajasEnObjetivo.top() != std::make_pair(filaActual, columnaActual)) {
					tempStack.push(cajasEnObjetivo.top());
					cajasEnObjetivo.pop();
				}
				if (!cajasEnObjetivo.empty()) cajasEnObjetivo.pop(); // Eliminar la caja deseada
				// Reinsertar los elementos de la pila temporal
				while (!tempStack.empty()) {
					cajasEnObjetivo.push(tempStack.top());
					tempStack.pop();
				}
			}
		}

		tablero.obtenerNodo(filaDeseada, columnaDeseada)->valor = (celdaDetrasCaja == '.') ? '!' : '$';
		tablero.obtenerNodo(filaActual, columnaActual)->valor = ' ';

		// Actualizar la lista de cajas con la nueva posición
		for (auto& caja : cajas) {
			if (caja.getFila() == filaActual && caja.getColumna() == columnaActual) {
				caja.setPosicion(filaDeseada, columnaDeseada);
				break;
			}
		}

		return true;
	}
	return false;
}

bool Tablero::moverJugador(char direccion) {
	int nuevaFila = jugador.getFila();
	int nuevaColumna = jugador.getColumna();

	switch (direccion) {
	case 'U': nuevaFila--; break;
	case 'D': nuevaFila++; break;
	case 'L': nuevaColumna--; break;
	case 'R': nuevaColumna++; break;
	}

	if (!esPosicionValida(nuevaFila, nuevaColumna)) {
		return false;
	}

	char celdaDestino = tablero.obtenerNodo(nuevaFila, nuevaColumna)->valor;

	if (puedeMoverseA(nuevaFila, nuevaColumna)) {
		// Se restaura la celda previa del jugador
		tablero.obtenerNodo(jugador.getFila(), jugador.getColumna())->valor = jugador.getCeldaPrevia();

		// Se actualiza la celda previa del jugador antes de moverlo
		jugador.setCeldaPrevia(celdaDestino);

		jugador.setPosicion(nuevaFila, nuevaColumna);
		tablero.obtenerNodo(nuevaFila, nuevaColumna)->valor = '@';
	}
	else if (celdaDestino == '$' || celdaDestino == '!') {
		int filaDetrasCaja = nuevaFila + (nuevaFila - jugador.getFila());
		int columnaDetrasCaja = nuevaColumna + (nuevaColumna - jugador.getColumna());

		if (moverCaja(nuevaFila, nuevaColumna, filaDetrasCaja, columnaDetrasCaja)) {
			// Mueve al jugador
			tablero.obtenerNodo(jugador.getFila(), jugador.getColumna())->valor = jugador.getCeldaPrevia();
			jugador.setCeldaPrevia(celdaDestino == '!' ? '.' : ' ');
			jugador.setPosicion(nuevaFila, nuevaColumna);
			tablero.obtenerNodo(nuevaFila, nuevaColumna)->valor = '@';
		}
		else {
			return false;  // No puede mover la caja
		}
	}
	else {
		return false;  // Movimiento no válido
	}

	return true;
}

bool Tablero::verificarVictoria() {
	for (const Caja& caja : cajas) {
		char celda = tablero.obtenerNodo(caja.getFila(), caja.getColumna())->valor;
		if (celda != '!') {
			return false; // La caja no está en un objetivo
		}
	}
	return true; // Todas las cajas están en objetivos
}

std::string Tablero::serializar() const {
	std::string serializado = "TABLERO_START\n";  // Identificador de inicio
	serializado += std::to_string(filas) + "," + std::to_string(columnas) + "\n";
	for (int fila = 0; fila < filas; ++fila) {
		for (int columna = 0; columna < columnas; ++columna) {
			serializado += tablero.obtenerNodo(fila, columna)->valor;
		}
		serializado += "\n";
	}

	// Serializar posición y celda previa del jugador
	serializado += std::to_string(jugador.getFila()) + "," + std::to_string(jugador.getColumna()) + "," + jugador.getCeldaPrevia() + "\n";

	// Serializando las cajas:
	serializado += std::to_string(cajas.size()) + "\n";  // número de cajas
	for (const Caja& caja : cajas) {
		serializado += std::to_string(caja.getFila()) + "," + std::to_string(caja.getColumna()) + "\n";
	}

	serializado += "TABLERO_END\n";  // Identificador de finalización
	return serializado;
}

void Tablero::deserializar(const std::string& datos) {
	std::istringstream ss(datos);
	std::string linea;

	std::getline(ss, linea);
	if (linea != "TABLERO_START") {
		throw std::runtime_error("Archivo de guardado no válido.");
	}

	// Leer dimensiones
	std::getline(ss, linea);
	std::istringstream lineSS(linea);
	std::string token;
	std::getline(lineSS, token, ',');
	filas = std::stoi(token);
	std::getline(lineSS, token, ',');
	columnas = std::stoi(token);

	// Leer tablero
	for (int fila = 0; fila < filas; ++fila) {
		std::getline(ss, linea);
		if (linea.size() != columnas) {
			throw std::runtime_error("Formato de guardado no válido. Dimensiones incorrectas.");
		}
		std::vector<char> filaParaTablero(linea.begin(), linea.end());
		tablero.insertarFila(filaParaTablero);
	}

	// Leer posición del jugador y su celda previa
	std::getline(ss, linea);
	lineSS.str(linea);
	lineSS.clear();
	std::getline(lineSS, token, ',');
	int jugadorFila = std::stoi(token);
	std::getline(lineSS, token, ',');
	int jugadorColumna = std::stoi(token);
	std::getline(lineSS, token, ',');
	char jugadorCeldaPrevia = token[0];
	jugador.setPosicion(jugadorFila, jugadorColumna);
	jugador.setCeldaPrevia(jugadorCeldaPrevia);

	// Leer cajas
	cajas.clear();
	std::getline(ss, linea);
	int numCajas = std::stoi(linea);
	for (int i = 0; i < numCajas; ++i) {
		std::getline(ss, linea);
		lineSS.str(linea);
		lineSS.clear();
		std::getline(lineSS, token, ',');
		int cajaFila = std::stoi(token);
		std::getline(lineSS, token, ',');
		int cajaColumna = std::stoi(token);
		Caja caja(cajaFila, cajaColumna);
		cajas.push_back(caja);
	}

	std::getline(ss, linea);
	if (linea != "TABLERO_END") {
		throw std::runtime_error("Archivo de guardado no válido.");
	}
}
