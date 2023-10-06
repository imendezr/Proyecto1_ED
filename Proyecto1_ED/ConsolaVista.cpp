#include "ConsolaVista.h"

// Implementación de los métodos de la clase ConsolaVista
ConsolaVista::ConsolaVista() {
	// Constructor si es necesario
}

void ConsolaVista::MostrarTablero(const Tablero& tablero) {
	// Implementación específica de cómo mostrar el tablero en la consola
}

void ConsolaVista::MostrarMensaje(const std::string& mensaje) {
	// Implementación específica de cómo mostrar un mensaje en la consola
}

char ConsolaVista::SolicitarEntrada(const std::string& mensaje) {
	// Implementación específica de cómo solicitar entrada al usuario en la consola
	char entrada = ' ';
	// Código para leer la entrada del usuario
	return entrada;
}

char ConsolaVista::MostrarMenu() {
	while (true) {
		MostrarMensaje("----- Menú de Sokoban -----");
		MostrarMensaje("1. Iniciar nuevo juego");
		MostrarMensaje("2. Cargar juego guardado");
		MostrarMensaje("3. Ver instrucciones");
		MostrarMensaje("4. Salir");
		char entrada = SolicitarEntrada("Ingrese su opción:");
		switch (entrada) {
		case '1':
			return 'N';
		case '2':
			return 'L';
		case '3':
			MostrarInstrucciones();
			return 'I';
		case '4':
			MostrarMensaje("Gracias por jugar Sokoban. ¡Hasta pronto!");
			return 'Q';
		default:
			MostrarMensaje("Opción no válida. Por favor, intente de nuevo.");
			break;
		}
	}
}

void ConsolaVista::MostrarInstrucciones() {
	MostrarMensaje("Instrucciones del juego ...");
}
