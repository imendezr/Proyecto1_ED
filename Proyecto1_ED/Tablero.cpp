#include "Tablero.h"
#include "Archivo.h"

Tablero::Tablero() : jugador(0, 0), filas(0), columnas(0) {
	// Aquí podrías cargar un nivel por defecto o dejar el tablero vacío
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
	auto contenido = Archivo::leerArchivo(nombreArchivo);

	if (contenido.empty()) {
		return false; // No se pudo leer el archivo correctamente
	}

	tablero.borrarLista(); // Limpia el tablero actual
	cajas.clear(); // Limpia las cajas actuales

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
		char celdaDetrasCaja = tablero.obtenerNodo(filaDetrasCaja, columnaDetrasCaja)->valor;

		if (celdaDetrasCaja == ' ' || celdaDetrasCaja == '.') {
			// Mueve la caja
			tablero.obtenerNodo(filaDetrasCaja, columnaDetrasCaja)->valor = (celdaDetrasCaja == '.') ? '!' : '$';

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
	return cajasEnObjetivo.size() == cajas.size();
}
