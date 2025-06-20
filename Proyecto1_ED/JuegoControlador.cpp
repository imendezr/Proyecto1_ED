#include "JuegoControlador.h"
#include "ConsolaVista.h"
#include <iostream>
#include <thread>
#include <conio.h>

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
			char entrada = vista->solicitarEntrada(R"(
Presiona:
Z para reiniciar el nivel
G para guardar la partida
Q para salir)");
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
		repeticion.limpiarMovimientos();  // Limpiamos la repetici�n
	}
	else {
		vista->mostrarMensaje("Error al cargar el nivel.");
	}
}

void JuegoControlador::guardarJuego() {
	// Si el jugador ha completado el nivel, limpiamos la repetici�n antes de guardar.
	if (tableroActual.verificarVictoria()) {
		repeticion.limpiarMovimientos();
	}

	if (Archivo::guardarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->mostrarMensaje("Juego guardado con exito.");
	}
	else {
		vista->mostrarMensaje("Error al guardar el juego.");
	}
}

bool JuegoControlador::cargarJuego() {
	// Limpiar o reinicializar cualquier estado anterior aqu�
	tableroActual = Tablero(); // Reiniciar el tablero a su estado inicial

	if (Archivo::cargarEstadoJuego("savegame.txt", tableroActual, nivelActual, repeticion)) {
		vista->mostrarMensaje("Juego cargado con exito.");
		juegoEnProgreso = true; // Reanudar juego
		return true;
	}
	else {
		vista->mostrarMensaje("Error al cargar el juego.");
		return false;
	}
}

void JuegoControlador::manejarEntrada(char entrada) {
	if (esperandoRespuesta) {
		return;  // No procesar la entrada si se est� esperando una respuesta
	}

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
		repeticion.registrarMovimiento(entrada);
		if (tableroActual.verificarVictoria()) {
			vista->mostrarTablero(tableroActual);
			nivelCompletado();
		}
	}
}

void JuegoControlador::nivelCompletado() {
	if (nivelActual == niveles.size()) {
		// Si el nivel actual es el �ltimo
		system("cls");
		vista->mostrarMensaje(R"(Felicidades! Has completado todos los niveles.

Presiona Enter para volver al menu principal...)");
		// Esperar hasta que el usuario presione Enter
		while (true) {
			char entrada = _getch();
			if (entrada == '\r') {
				system("cls");
				break;
			}
		}
		juegoEnProgreso = false;
	}
	else {
		esperandoRespuesta = true;
		vista->mostrarMensaje("\nNivel completado!");

		char entrada;
		do {
			entrada = vista->solicitarEntrada("Presiona V para ver la repetici�n o C para continuar al siguiente nivel: ");
		} while (entrada != 'V' && entrada != 'v' && entrada != 'C' && entrada != 'c');

		switch (entrada) {
		case 'V':
		case 'v':
			mostrarRepeticion();
			// Luego de ver la repetici�n, limpiamos los movimientos
			repeticion.limpiarMovimientos();
			// Luego de ver la repetici�n, se le da la opci�n de continuar al siguiente nivel.
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
}

void JuegoControlador::reiniciarNivel() {
	cargarNivel(nivelActual);
	repeticion.limpiarMovimientos();  // Limpiamos la repetici�n
}

void JuegoControlador::mostrarRepeticion() {
	const auto& movimientos = repeticion.obtenerMovimientos();

	// Se resetea el tablero al estado inicial del nivel actual
	Tablero tableroTemporal;
	tableroTemporal.cargarDesdeArchivo(niveles[nivelActual - 1]);

	for (char movimiento : movimientos) {
		tableroTemporal.moverJugador(movimiento);
		vista->mostrarTablero(tableroTemporal);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay de medio segundo entre movimientos
	}
}

void JuegoControlador::avanzarAlSiguienteNivel() {
	if (nivelActual < niveles.size()) {
		cargarNivel(nivelActual + 1);
		repeticion.limpiarMovimientos();  // Limpiamos la repetici�n despu�s de cargar el nivel
	}
	else {
		system("cls");
		vista->mostrarMensaje(R"(Felicidades! Has completado todos los niveles.

Presiona Enter para volver al menu principal...)");
		// Esperar hasta que el usuario presione Enter
		while (true) {
			char entrada = _getch();
			if (entrada == '\r') {
				system("cls");
				break;
			}
		}
		juegoEnProgreso = false;
	}
}
