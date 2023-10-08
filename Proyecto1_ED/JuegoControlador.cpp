#include "JuegoControlador.h"
#include "ConsolaVista.h"
#include <iostream>
#include <thread>

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
	while (true) {
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
			continue;
		case 'Q':
			exit(0);
			break;
		}

		while (juegoEnProgreso) {
			vista->mostrarTablero(tableroActual);
			char entrada = vista->solicitarEntrada("Presiona Z para reiniciar el nivel, G para guardar la partida o Q para salir: ");
			switch (entrada) {
			case 'G':
			case 'g':
				GuardarJuego();
				break;
			case 'Z':
			case 'z':
				ReiniciarNivel();
				break;
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
		vista->mostrarMensaje("Juego guardado con éxito.");
	}
	else {
		vista->mostrarMensaje("Error al guardar el juego.");
	}
}

bool JuegoControlador::CargarJuego() {
	if (Archivo::cargarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->mostrarMensaje("Juego cargado con éxito.");
		juegoEnProgreso = true; // Reanudar juego
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
	// Lógica de manejo de entrada...

	bool movimientoValido = false;

	switch (entrada) {
	case 'U':
	case 'D':
	case 'L':
	case 'R':
		movimientoValido = tableroActual.moverJugador(entrada);
		break;
		// Puedes agregar otros casos para otras entradas, como seleccionar opciones en el menú, etc.
	default:
		break;
	}

	if (movimientoValido) {
		repeticion.registrarMovimiento(entrada); // Registrar el movimiento en Repeticion
		if (tableroActual.verificarVictoria()) {
			nivelCompletado();
		}
	}
}

void JuegoControlador::nivelCompletado() {
	vista->mostrarMensaje("¡Nivel completado!");
	// Puedes agregar un pequeño delay aquí para que el jugador pueda ver el mensaje
	std::this_thread::sleep_for(std::chrono::seconds(2));
	AvanzarAlSiguienteNivel();
}

void JuegoControlador::ReiniciarNivel() {
	CargarNivel(nivelActual);
}

void JuegoControlador::MostrarRepeticion() {
	const auto& movimientos = repeticion.obtenerMovimientos();

	// Se carga el nivel de nuevo para comenzar la repetición desde el inicio
	CargarNivel(nivelActual);

	for (char movimiento : movimientos) {
		tableroActual.moverJugador(movimiento);
		vista->mostrarTablero(tableroActual);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay de medio segundo entre movimientos
	}
}

void JuegoControlador::AvanzarAlSiguienteNivel() {
	if (nivelActual < niveles.size()) {
		CargarNivel(nivelActual + 1);
	}
	else {
		vista->mostrarMensaje("¡Felicidades! Has completado todos los niveles.");
		juegoEnProgreso = false;
	}
}
