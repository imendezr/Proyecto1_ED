#include "JuegoControlador.h"
#include <iostream>

JuegoControlador::JuegoControlador() : nivelActual(1), juegoEnProgreso(false) {}

void JuegoControlador::IniciarJuego() {
	MostrarMenu();
}

void JuegoControlador::CargarNivel(int nivel) {
	std::string nombreArchivo = "nivel" + std::to_string(nivel) + ".txt";
	if (tableroActual.CargarDesdeArchivo(nombreArchivo)) {
		juegoEnProgreso = true;
	}
	else {
		std::cout << "Error al cargar el nivel." << std::endl;
	}
}

void JuegoControlador::MostrarMenu() {
	// Mostrar opciones al usuario y manejar su elección
}

void JuegoControlador::MostrarInstrucciones() {
	// Mostrar instrucciones del juego
}

void JuegoControlador::ManejarEntrada(char entrada) {
	// Manejar la entrada del usuario y actualizar el tablero
}

void JuegoControlador::ReiniciarNivel() {
	CargarNivel(nivelActual);
}

void JuegoControlador::MostrarRepeticion() {
	// Mostrar la repetición del nivel actual basado en los movimientos registrados
}
