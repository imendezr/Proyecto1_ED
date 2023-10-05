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
		vista->MostrarMensaje("Juego guardado con éxito.");
	}
	else {
		vista->MostrarMensaje("Error al guardar el juego.");
	}
}

bool JuegoControlador::CargarJuego() {
	if (Archivo::CargarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->MostrarMensaje("Juego cargado con éxito.");
		return true;
	}
	else {
		vista->MostrarMensaje("Error al cargar el juego.");
		return false;
	}
}

void JuegoControlador::MostrarMenu() {
	while (true) { // Este bucle permite que el menú se muestre hasta que el jugador elija una opción válida
		vista->MostrarMensaje("----- Menú de Sokoban -----");
		vista->MostrarMensaje("1. Iniciar nuevo juego");
		vista->MostrarMensaje("2. Cargar juego guardado");
		vista->MostrarMensaje("3. Ver instrucciones");
		vista->MostrarMensaje("4. Salir");
		char entrada = vista->SolicitarEntrada("Ingrese su opción:");
		if (ManejarEntradaMenu(entrada)) {
			break;
		}
	}
}

bool JuegoControlador::ManejarEntradaMenu(char entrada) {
	switch (entrada) {
	case '1':
		CargarNivel(1); // Inicia el primer nivel
		return true;
	case '2':
		if (!CargarJuego()) {
			vista->MostrarMensaje("No se pudo cargar el juego.");
		}
		return true;
	case '3':
		MostrarInstrucciones();
		return true;
	case '4':
		juegoEnProgreso = false; // Termina el juego
		vista->MostrarMensaje("Gracias por jugar Sokoban. ¡Hasta pronto!");
		exit(0); // Salir del programa
	default:
		vista->MostrarMensaje("Opción no válida. Por favor, intente de nuevo.");
		return false;
	}
}

void JuegoControlador::MostrarInstrucciones() {
	vista->MostrarMensaje("Instrucciones del juego ...");
}

void JuegoControlador::ManejarEntrada(char entrada) {
	// Lógica de manejo de entrada...

	bool movimientoValido = false;

	switch (entrada) {
	case 'U':
	case 'D':
	case 'L':
	case 'R':
		movimientoValido = tableroActual.MoverJugador(entrada);
		break;
		// Puedes agregar otros casos para otras entradas, como seleccionar opciones en el menú, etc.
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

	// Cargamos el nivel inicial para comenzar la repetición desde el inicio
	CargarNivel(nivelActual);

	for (char movimiento : movimientos) {
		tableroActual.MoverJugador(movimiento);
		vista->MostrarTablero(tableroActual); // Mostrar el tablero después de cada movimiento
	}
}

void JuegoControlador::AvanzarAlSiguienteNivel() {
	if (nivelActual < niveles.size()) {
		CargarNivel(nivelActual + 1);
	}
	else {
		vista->MostrarMensaje("¡Felicidades! Has completado todos los niveles.");
		juegoEnProgreso = false;
	}
}
