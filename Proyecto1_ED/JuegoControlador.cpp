#include "JuegoControlador.h"
#include "ConsolaVista.h"
#include <iostream>
#include <thread>

JuegoControlador::JuegoControlador() : nivelActual(1), juegoEnProgreso(false), esperandoRespuesta(false), vista(new ConsolaVista()) {
	// Inicializar la lista de niveles
	niveles.push_back("nivel1.txt");
	niveles.push_back("nivel2.txt");
	niveles.push_back("nivel3.txt");
}

JuegoControlador::~JuegoControlador() {
	delete vista;
}

void JuegoControlador::iniciarJuego() {
	while (true) {
		char opcion = vista->mostrarMenu();

		switch (opcion) {
		case 'N':
			cargarNivel(1);
			break;
		case 'L':
			cargarJuego();
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
			if (esperandoRespuesta) {
				continue; // Si estamos esperando una respuesta, no procesamos la entrada y volvemos al inicio del loop
			}
			switch (entrada) {
			case 'G':
			case 'g':
				guardarJuego();
				break;
			case 'Z':
			case 'z':
				reiniciarNivel();
				break;
			case 'Q':
			case 'q':
				juegoEnProgreso = false;
				break;
			default:
				manejarEntrada(entrada);
				break;
			}
		}
	}
}

void JuegoControlador::cargarNivel(int nivel) {
	if (nivel <= niveles.size() && tableroActual.cargarDesdeArchivo(niveles[nivel - 1])) {
		nivelActual = nivel;
		juegoEnProgreso = true;
	}
	else {
		vista->mostrarMensaje("Error al cargar el nivel.");
	}
}

void JuegoControlador::guardarJuego() {
	if (Archivo::guardarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->mostrarMensaje("Juego guardado con éxito.");
	}
	else {
		vista->mostrarMensaje("Error al guardar el juego.");
	}
}

bool JuegoControlador::cargarJuego() {
	// Limpiar o reinicializar cualquier estado anterior aquí
	tableroActual = Tablero(); // Reiniciar el tablero a su estado inicial

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

void JuegoControlador::manejarEntrada(char entrada) {
	if (esperandoRespuesta) {
		return;  // No procesar la entrada si se está esperando una respuesta
	}

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
		repeticion.registrarMovimiento(entrada);
		if (tableroActual.verificarVictoria()) {
			vista->mostrarTablero(tableroActual);
			nivelCompletado();
		}
	}
}

void JuegoControlador::nivelCompletado() {
	esperandoRespuesta = true;
	vista->mostrarMensaje("¡Nivel completado!");

	char entrada;
	do {
		entrada = vista->solicitarEntrada("Presiona V para ver la repetición o C para continuar al siguiente nivel: ");
	} while (entrada != 'V' && entrada != 'v' && entrada != 'C' && entrada != 'c');

	switch (entrada) {
	case 'V':
	case 'v':
		mostrarRepeticion();
		// Luego de ver la repetición, se le da la opción de continuar al siguiente nivel.
		vista->solicitarEntrada("Presiona C para continuar al siguiente nivel: ");
		avanzarAlSiguienteNivel();
		break;
	case 'C':
	case 'c':
		avanzarAlSiguienteNivel();
		break;
	}

	esperandoRespuesta = false;
}

void JuegoControlador::reiniciarNivel() {
	cargarNivel(nivelActual);
}

void JuegoControlador::mostrarRepeticion() {
	const auto& movimientos = repeticion.obtenerMovimientos();

	// Se carga el nivel de nuevo para comenzar la repetición desde el inicio
	cargarNivel(nivelActual);

	for (char movimiento : movimientos) {
		tableroActual.moverJugador(movimiento);
		vista->mostrarTablero(tableroActual);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay de medio segundo entre movimientos
	}
}

void JuegoControlador::avanzarAlSiguienteNivel() {
	if (nivelActual < niveles.size()) {
		cargarNivel(nivelActual + 1);
	}
	else {
		vista->mostrarMensaje("¡Felicidades! Has completado todos los niveles.");
		juegoEnProgreso = false;
	}
}
