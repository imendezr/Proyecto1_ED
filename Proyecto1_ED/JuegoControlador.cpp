#include "JuegoControlador.h"
#include "ConsolaVista.h"
#include <iostream>

JuegoControlador::JuegoControlador() : nivelActual(1), juegoEnProgreso(false), vista(new ConsolaVista()) {
	// Inicializar la lista de niveles
	niveles.push_back("nivel1.txt");
	niveles.push_back("nivel2.txt");
	niveles.push_back("nivel3.txt");
}

JuegoControlador::~JuegoControlador() {
	delete vista;
}

void JuegoControlador::IniciarJuego() {
	while (true) {  // Bucle principal del juego
		char opcion = vista->mostrarMenu();

		switch (opcion) {
		case 'N':
			CargarNivel(1);
			break;
		case 'L':
			CargarJuego();
			break;
		case 'I':
			// Las instrucciones ya fueron mostradas en la vista
			continue;  // Contin�a con la siguiente iteraci�n del bucle para volver al men�
		case 'Q':
			exit(0);
			break;
		}

		while (juegoEnProgreso) {
			vista->mostrarTablero(tableroActual);
			char entrada = vista->solicitarEntrada("Mueve con las flechas o Q para salir: ");
			switch (entrada) {
			case 'Q':
			case 'q':
				juegoEnProgreso = false;
				break;
			default:
				ManejarEntrada(entrada);
				break;
			}
		}
	}
}

void JuegoControlador::CargarNivel(int nivel) {
	if (nivel <= niveles.size() && tableroActual.cargarDesdeArchivo(niveles[nivel - 1])) {
		nivelActual = nivel;
		juegoEnProgreso = true;
	}
	else {
		vista->mostrarMensaje("Error al cargar el nivel.");
	}
}

void JuegoControlador::GuardarJuego() {
	if (Archivo::guardarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->mostrarMensaje("Juego guardado con �xito.");
	}
	else {
		vista->mostrarMensaje("Error al guardar el juego.");
	}
}

bool JuegoControlador::CargarJuego() {
	if (Archivo::cargarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->mostrarMensaje("Juego cargado con �xito.");
		return true;
	}
	else {
		vista->mostrarMensaje("Error al cargar el juego.");
		return false;
	}
}

void JuegoControlador::mostrarInstrucciones() {
	vista->mostrarMensaje("Instrucciones del juego ...");
}

void JuegoControlador::ManejarEntrada(char entrada) {
	// L�gica de manejo de entrada...

	bool movimientoValido = false;

	switch (entrada) {
	case 'U':
	case 'D':
	case 'L':
	case 'R':
		movimientoValido = tableroActual.moverJugador(entrada);
		break;
		// Puedes agregar otros casos para otras entradas, como seleccionar opciones en el men�, etc.
	default:
		break;
	}

	if (movimientoValido) {
		repeticion.registrarMovimiento(entrada); // Registrar el movimiento en Repeticion
	}
}

void JuegoControlador::ReiniciarNivel() {
	CargarNivel(nivelActual);
}

void JuegoControlador::MostrarRepeticion() {
	const auto& movimientos = repeticion.obtenerMovimientos();

	// Cargamos el nivel inicial para comenzar la repetici�n desde el inicio
	CargarNivel(nivelActual);

	for (char movimiento : movimientos) {
		tableroActual.moverJugador(movimiento);
		vista->mostrarTablero(tableroActual); // Mostrar el tablero despu�s de cada movimiento
	}
}

void JuegoControlador::AvanzarAlSiguienteNivel() {
	if (nivelActual < niveles.size()) {
		CargarNivel(nivelActual + 1);
	}
	else {
		vista->mostrarMensaje("�Felicidades! Has completado todos los niveles.");
		juegoEnProgreso = false;
	}
}
