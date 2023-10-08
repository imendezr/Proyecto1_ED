#include "ListaEnlazada.h"
#include "JuegoControlador.h"
#include <iostream>
#include <vector>

template <typename T>
void Mostrar(const T&);

int main() {
	JuegoControlador controlador;
	controlador.IniciarJuego();

    /*//  -------------------------------------------------------------- PRUEBAS LISTA ENLAZADA --------------------------------------------------------------
    // Crear una instancia original de ListaEnlazada
    ListaEnlazada<int> listaOriginal;

    // Insertar una fila en la lista original
    std::vector<int> fila1 = { 1, 2, 3 };
    std::vector<int> fila2 = { 4, 5, 6 };
    listaOriginal.InsertarFila(fila1);
    listaOriginal.InsertarFila(fila2);

    // Insertar una columna en la lista original
    std::vector<int> columna1 = { 7, 8 };
    std::vector<int> columna2 = { 9, 10 };
    listaOriginal.InsertarColumna(columna1);
    listaOriginal.InsertarColumna(columna2);

    // Mostrar la lista original
    std::cout << "Lista Original:" << std::endl;
    Mostrar(listaOriginal);

    // Crear una nueva instancia utilizando el constructor de copia
    ListaEnlazada<int> listaCopia(listaOriginal);

    // Mostrar la lista copiada
    std::cout << "Lista Copiada:" << std::endl;
    Mostrar(listaCopia);

    // Realizar algunas operaciones en la lista copiada
    std::vector<int> fila3 = { 7, 7, 7, 7 };
    listaCopia.InsertarFila(fila3);

    // Mostrar la lista copiada después de la operación
    std::cout << "Lista Copiada despues de Insertar Fila:" << std::endl;
    Mostrar(listaCopia);

    // Eliminar una fila en la lista copiada
    listaCopia.EliminarFila(1);

    // Mostrar la lista copiada después de eliminar una fila
    std::cout << "Lista Copiada despues de Eliminar Fila:" << std::endl;
    Mostrar(listaCopia);

    // Verificar que la lista original no se haya modificado
    std::cout << "Lista Original despues de operaciones en la copia:" << std::endl;
    Mostrar(listaOriginal);

    //  -------------------------------------------------------------- PRUEBAS LISTA ENLAZADA --------------------------------------------------------------
    */
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
