#include "Tablero.h"
#include "Archivo.h"

Tablero::Tablero() : jugador(0, 0), filas(0), columnas(0) {
	// Aquí podrías cargar un nivel por defecto o dejar el tablero vacío
}

bool Tablero::EsPosicionValida(int fila, int columna) {
	return fila >= 0 && fila < filas && columna >= 0 && columna < columnas;
}

bool Tablero::PuedeMoverseA(int fila, int columna) {
	char celda = tablero.ObtenerNodo(fila, columna)->valor;
	return celda == ' ' || celda == '.';
}

bool Tablero::CargarDesdeArchivo(const std::string& nombreArchivo) {
	auto contenido = Archivo::LeerArchivo(nombreArchivo);

	tablero.BorrarLista(); // Limpia el tablero actual
	cajas.clear(); // Limpia las cajas actuales

	for (int fila = 0; fila < contenido.size(); ++fila) {
		auto linea = contenido[fila];
		std::vector<char> filaParaTablero;

		for (int columna = 0; columna < linea.size(); ++columna) {
			char celda = linea[columna];
			filaParaTablero.push_back(celda);

			if (celda == '@') {
				jugador.SetPosicion(fila, columna);
			}
			else if (celda == '$') {
				cajas.push_back(Caja(fila, columna));
			}
		}

		tablero.InsertarFila(filaParaTablero);
	}

	filas = contenido.size();
	columnas = (contenido.empty()) ? 0 : contenido[0].size();

	return true;
}

bool Tablero::MoverJugador(char direccion) {
	int nuevaFila = jugador.GetFila();
	int nuevaColumna = jugador.GetColumna();

	switch (direccion) {
	case 'U': nuevaFila--; break;
	case 'D': nuevaFila++; break;
	case 'L': nuevaColumna--; break;
	case 'R': nuevaColumna++; break;
	}

	if (!EsPosicionValida(nuevaFila, nuevaColumna)) {
		return false;
	}

	char celdaDestino = tablero.ObtenerNodo(nuevaFila, nuevaColumna)->valor;

	if (PuedeMoverseA(nuevaFila, nuevaColumna)) {
		// Obtener nodo antiguo y nuevo
		auto nodoAntiguo = tablero.ObtenerNodo(jugador.GetFila(), jugador.GetColumna());
		auto nodoNuevo = tablero.ObtenerNodo(nuevaFila, nuevaColumna);

		// Actualizar los nodos
		nodoAntiguo->valor = ' '; // espacio vacío o el valor que corresponda
		nodoNuevo->valor = '@'; // símbolo del jugador

		// Registrar el movimiento en el vector movimientos
		movimientos.push_back(direccion);

		// Actualizar la posición del jugador
		jugador.SetPosicion(nuevaFila, nuevaColumna);
		return true;
	}
	else if (celdaDestino == '$') {
		// Si el jugador está tratando de mover una caja, verifica si puede empujarla
		// Calcula la posición detrás de la caja basado en la dirección
		int filaDetrasCaja = nuevaFila + (nuevaFila - jugador.GetFila());
		int columnaDetrasCaja = nuevaColumna + (nuevaColumna - jugador.GetColumna());

		char celdaDetrasCaja = tablero.ObtenerNodo(filaDetrasCaja, columnaDetrasCaja)->valor;
		if (celdaDetrasCaja == ' ' || celdaDetrasCaja == '.') {
			// Empuja la caja y mueve al jugador
			jugador.SetPosicion(nuevaFila, nuevaColumna);

			// Actualizar posición de la caja en el tablero y en el vector de cajas
			for (Caja& caja : cajas) {
				if (caja.GetFila() == nuevaFila && caja.GetColumna() == nuevaColumna) {
					caja.SetPosicion(filaDetrasCaja, columnaDetrasCaja);
					break;
				}
			}
			// Actualizar los nodos del tablero
			tablero.ObtenerNodo(nuevaFila, nuevaColumna)->valor = '@';
			tablero.ObtenerNodo(filaDetrasCaja, columnaDetrasCaja)->valor = '$';

			// Registrar el movimiento en el vector movimientos
			movimientos.push_back(direccion);

			// Si movemos la caja a su objetivo
			if (celdaDetrasCaja == '.') {
				cajasEnObjetivo.push(Caja(filaDetrasCaja, columnaDetrasCaja));
			}

			// Si sacamos una caja de su objetivo
			if (tablero.ObtenerNodo(nuevaFila, nuevaColumna)->valor == '!') {
				cajasEnObjetivo.pop();
			}

			return true;
		}
	}

	return false; // Movimiento no válido
}

bool Tablero::VerificarVictoria() {
	return cajasEnObjetivo.size() == cajas.size();
}

void Tablero::MostrarTablero() {
	// Esta función mostraría el tablero, útil para la versión de consola
	// ...
}
