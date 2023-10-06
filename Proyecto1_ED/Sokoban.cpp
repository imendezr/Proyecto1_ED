#include "ListaEnlazada.h"
#include "JuegoControlador.h"
#include <iostream>
#include <vector>

template <typename T>
void Mostrar(const T&);

int main() {
	// JuegoControlador controlador;
	// controlador.IniciarJuego();


	// Crear una instancia de la ListaEnlazada
	ListaEnlazada<int> lista;

	// Insertar una fila en la lista
	std::vector<int> fila1 = { 1, 2, 3 };
	std::vector<int> fila2 = { 4, 5, 6 };
	lista.InsertarFila(fila1);
	lista.InsertarFila(fila2);

	// Insertar una columna en la lista
	std::vector<int> columna1 = { 7, 8 };
	std::vector<int> columna2 = { 9, 10 };
	lista.InsertarColumna(columna1);
	lista.InsertarColumna(columna2);

	// Mostrar la lista
	Mostrar(lista);

	std::vector<int> fila3 = { 7, 7, 7 , 7};
	lista.InsertarFila(fila3);

	// Mostrar la lista
	Mostrar(lista);

	// Eliminar una fila y una columna
	lista.EliminarFila(1); // Eliminar la segunda fila

	// Mostrar la lista
	Mostrar(lista);

	lista.EliminarColumna(0); // Eliminar la primera columna

	// Mostrar la lista
	Mostrar(lista);

	// Obtener un nodo específico
	ListaEnlazada<int>::listaptr nodo = lista.ObtenerNodo(0, 1);
	if (nodo) {
		std::cout << "Valor en la fila " << 0 + 1 << ", columna " << 1 + 1 << ": " << nodo->valor << std::endl;
	}

	return 0;
}

template <typename T>
void Mostrar(const T& lista) {
	typename T::const_listaptr filaActual = lista.GetPrimerNodo();

	while (filaActual) {
		typename T::const_listaptr columnaActual = filaActual;
		while (columnaActual) {
			std::cout << columnaActual->valor << " ";
			columnaActual = columnaActual->right;
		}
		std::cout << std::endl;
		filaActual = filaActual->down;
	}
	std::cout << "\n\n";
}
