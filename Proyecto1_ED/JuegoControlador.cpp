#include "JuegoControlador.h"
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
	MostrarMenu();
}

void JuegoControlador::CargarNivel(int nivel) {
	if (nivel <= niveles.size() && tableroActual.CargarDesdeArchivo(niveles[nivel - 1])) {
		nivelActual = nivel;
		juegoEnProgreso = true;
	}
	else {
		vista->MostrarMensaje("Error al cargar el nivel.");
	}
}

void JuegoControlador::GuardarJuego() {
	if (Archivo::GuardarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->MostrarMensaje("Juego guardado con �xito.");
	}
	else {
		vista->MostrarMensaje("Error al guardar el juego.");
	}
}

bool JuegoControlador::CargarJuego() {
	if (Archivo::CargarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->MostrarMensaje("Juego cargado con �xito.");
		return true;
	}
	else {
		vista->MostrarMensaje("Error al cargar el juego.");
		return false;
	}
}

void JuegoControlador::MostrarMenu() {
	// Mostrar opciones al usuario y manejar su elecci�n
	vista->MostrarMensaje("Mensaje del men� ...");
	char entrada = vista->SolicitarEntrada("Ingrese su opci�n:");
	ManejarEntrada(entrada);
}

void JuegoControlador::MostrarInstrucciones() {
	vista->MostrarMensaje("Instrucciones del juego ...");
}

void JuegoControlador::ManejarEntrada(char entrada) {
	// L�gica de manejo de entrada...

	bool movimientoValido = false;

	switch (entrada) {
	case 'U':
	case 'D':
	case 'L':
	case 'R':
		movimientoValido = tableroActual.MoverJugador(entrada);
		break;
		// Puedes agregar otros casos para otras entradas, como seleccionar opciones en el men�, etc.
	default:
		break;
	}

	if (movimientoValido) {
		repeticion.RegistrarMovimiento(entrada); // Registrar el movimiento en Repeticion
	}
}

void JuegoControlador::ReiniciarNivel() {
	CargarNivel(nivelActual);
}

void JuegoControlador::MostrarRepeticion() {
	const auto& movimientos = repeticion.ObtenerMovimientos();

	// Cargamos el nivel inicial para comenzar la repetici�n desde el inicio
	CargarNivel(nivelActual);

	for (char movimiento : movimientos) {
		tableroActual.MoverJugador(movimiento);
		vista->MostrarTablero(tableroActual); // Mostrar el tablero despu�s de cada movimiento
	}
}

void JuegoControlador::AvanzarAlSiguienteNivel() {
	if (nivelActual < niveles.size()) {
		CargarNivel(nivelActual + 1);
	}
	else {
		vista->MostrarMensaje("�Felicidades! Has completado todos los niveles.");
		juegoEnProgreso = false;
	}
}
