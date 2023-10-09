#include "ConsolaVista.h"
#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include <conio.h>

ConsolaVista::ConsolaVista() {}

void ConsolaVista::mostrarTablero(const Tablero& tablero) {
	system("cls");  // Limpia la consola

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	SetConsoleCursorPosition(hConsole, coord); // Se establece el cursor en la esquina superior izquierda para mejor visualización

	for (int fila = 0; fila < tablero.getFilas(); ++fila) {
		for (int columna = 0; columna < tablero.getColumnas(); ++columna) {
			char celda = tablero.getTablero().obtenerNodo(fila, columna)->valor;
			switch (celda) {
			case '@': // Jugador
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << celda;
				break;
			case '#': // Pared
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << celda;
				break;
			case '$': // Caja
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << celda;
				break;
			case '.': // Objetivo
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << celda;
				break;
			case '!': // Caja en objetivo
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << celda;
				break;
			default:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				std::cout << celda;
				break;
			}
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Restablece el color normal
}

void ConsolaVista::mostrarMensaje(const std::string& mensaje) {
	std::cout << mensaje << "\n";
}

char ConsolaVista::solicitarEntrada(const std::string& mensaje) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << mensaje;

	int entrada = _getch();

	// Si la entrada es una tecla de flecha o tecla especial
	if (entrada == 224 || entrada == 0xE0) {
		entrada = _getch();
		switch (entrada) {
		case 72: return 'U';  // Flecha arriba
		case 80: return 'D';  // Flecha abajo
		case 75: return 'L';  // Flecha izquierda
		case 77: return 'R';  // Flecha derecha
		}
	}
	else {
		switch (toupper(entrada)) {
		case 'W': return 'U';
		case 'A': return 'L';
		case 'S': return 'D';
		case 'D': return 'R';
		default: return char(entrada);
		}
	}
	return char(entrada);
}

char ConsolaVista::mostrarMenu() {
	while (true) {
		system("cls");
		mostrarMensaje("----- Menu de Sokoban -----\n");
		mostrarMensaje("1. Iniciar nuevo juego");
		mostrarMensaje("2. Cargar juego guardado");
		mostrarMensaje("3. Ver instrucciones");
		mostrarMensaje("4. Salir");
		char entrada = solicitarEntrada("\nIngrese su opcion: ");
		switch (entrada) {
		case '1':
			return 'N';
		case '2':
			return 'L';
		case '3':
			mostrarInstrucciones();
			break;
			//return 'I';
		case '4':
			system("cls");
			mostrarMensaje("Gracias por jugar Sokoban. Hasta pronto!");
			return 'Q';
		default:
			mostrarMensaje("Opcion no valida. Por favor, intente de nuevo.");
			break;
		}
	}
}

void ConsolaVista::mostrarInstrucciones() {
	system("cls");
	mostrarMensaje(R"(
Instrucciones del juego:

1. Mueve al jugador con las flechas de direccion o las teclas W A S D.
2. Posiciona las cajas en los espacios respectivos.
3. Si completas los 3 niveles se gana una birra.

Buena suerte para completar los niveles sin un tutorial!

Presiona Enter para volver al menu principal...
)");

	// Esperar hasta que el usuario presione Enter
	while (true) {
		char entrada = _getch();
		if (entrada == '\r') {
			system("cls");
			break;
		}
	}
}
