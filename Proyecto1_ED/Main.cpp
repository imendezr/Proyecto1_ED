#include "ListaEnlazada.h"
#include <iostream>

template <typename T>
void Mostrar(const T&);

int main() {
    // Crear una instancia de la lista enlazada
    ListaEnlazada<int> lista;

    // Insertar elementos
    lista.Insertar(1);
    lista.Insertar(2);
    lista.Insertar(3);

    // Mostrar la lista
    Mostrar(lista);

    // Insertar más elementos
    lista.Insertar(4);
    lista.Insertar(5);

    // Mostrar la lista nuevamente
    Mostrar(lista);

    // Buscar y eliminar un elemento
    ListaEnlazada<int>::listaptr nodoBuscado = lista.Buscar(2);
    if (nodoBuscado != nullptr) {
        lista.Eliminar(nodoBuscado);
    }

    // Mostrar la lista después de la eliminación
    Mostrar(lista);

    // Eliminar un nodo en una posición específica
    lista.EliminarEnPos(2);

    // Mostrar la lista después de la eliminación por posición
    Mostrar(lista);

    // Borrar completamente la lista
    lista.BorrarLista();

    return 0;
}

template <typename T>
void Mostrar(const T& l) {
	typename T::const_listaptr tmp = l.GetPrimerNodo();

	while (tmp != nullptr) {
		std::cout << tmp->valor << " ";
		tmp = tmp->right;
	}
	std::cout << "\n\n";
}
