#include "ConsolaVista.h"

// Implementaci�n de los m�todos de la clase ConsolaVista
ConsolaVista::ConsolaVista() {
	// Constructor si es necesario
}

void ConsolaVista::MostrarTablero(const Tablero& tablero) {
	// Implementaci�n espec�fica de c�mo mostrar el tablero en la consola
}

void ConsolaVista::MostrarMensaje(const std::string& mensaje) {
	// Implementaci�n espec�fica de c�mo mostrar un mensaje en la consola
}

char ConsolaVista::SolicitarEntrada(const std::string& mensaje) {
	// Implementaci�n espec�fica de c�mo solicitar entrada al usuario en la consola
	char entrada = ' ';
	// C�digo para leer la entrada del usuario
	return entrada;
}

char ConsolaVista::MostrarMenu() {
	while (true) {
		MostrarMensaje("----- Men� de Sokoban -----");
		MostrarMensaje("1. Iniciar nuevo juego");
		MostrarMensaje("2. Cargar juego guardado");
		MostrarMensaje("3. Ver instrucciones");
		MostrarMensaje("4. Salir");
		char entrada = SolicitarEntrada("Ingrese su opci�n:");
		switch (entrada) {
		case '1':
			return 'N';
		case '2':
			return 'L';
		case '3':
			MostrarInstrucciones();
			return 'I';
		case '4':
			MostrarMensaje("Gracias por jugar Sokoban. �Hasta pronto!");
			return 'Q';
		default:
			MostrarMensaje("Opci�n no v�lida. Por favor, intente de nuevo.");
			break;
		}
	}
}

void ConsolaVista::MostrarInstrucciones() {
	MostrarMensaje("Instrucciones del juego ...");
}
