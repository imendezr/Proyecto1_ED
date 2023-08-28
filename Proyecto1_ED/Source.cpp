#include "ListaDoble.h"
#include <iostream>

//void Mostrar(const ListaSimple<int>&);
template <typename T>
void Mostrar(const T&);

int main() {
	ListaDoble<int> listaD;

	// Doblemente enlazada

	listaD.Insertar(24);
	listaD.Insertar(15);
	listaD.Insertar(3);
	listaD.Insertar(43);
	listaD.Insertar(30);
	listaD.Insertar(62);

	Mostrar(listaD);

	listaD.InsertarInicio(77);

	Mostrar(listaD);

	listaD.EliminarEnPos(3);

	Mostrar(listaD);

	int num1 = 43;
	auto nodo1 = listaD.Buscar(num1);
	if (nodo1 != nullptr) {
		std::cout << "Se encontro el valor " << num1 << " en la lista" << std::endl;
	}
	else {
		std::cout << "No se encontro el valor " << num1 << " en la lista" << std::endl;
	}

	int num2 = 81;
	auto nodo2 = listaD.Buscar(num2);
	if (nodo2 != nullptr) {
		std::cout << "Se encontro el valor " << num2 << " en la lista" << std::endl;
	}
	else {
		std::cout << "No se encontro el valor " << num2 << " en la lista" << std::endl;
	}

	listaD.BorrarLista();



	return 0;
}

/*void Mostrar(const ListaSimple<int>& l) {
	ListaSimple<int>::listaptr tmp;
	tmp = l.GetPrimerNodo();

	while (tmp != nullptr) {
		std::cout << tmp->valor << " ";
		tmp = tmp->next;
	}
	std::cout << "\n\n";
}*/

template <typename T>
void Mostrar(const T& l) {
	typename T::const_listaptr tmp = l.GetPrimerNodo();

	while (tmp != nullptr) {
		std::cout << tmp->valor << " ";
		tmp = tmp->next;
	}
	std::cout << "\n\n";
}
