// Definición de una lista "cuadruplemente" enlazada.

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <iostream>
#include <cstddef>
#include <vector>

template<class T> class ListaEnlazada {
private:
	// Declaración de cada nodo de la lista: contiene el valor y un apuntador a un nodo
	// Queda oculto para el usuario
	struct Nodo {
		T valor;
		Nodo* left;
		Nodo* right;
		Nodo* up;
		Nodo* down;
		// Constructor del Nodo - asigna NULL si se invoca sin el segundo parámetro
		Nodo(T valor, Nodo* izquierda = nullptr, Nodo* derecha = nullptr, Nodo* arriba = nullptr, Nodo* abajo = nullptr)
			: valor{ valor }, left{ izquierda }, right{ derecha }, up{ arriba }, down{ abajo } {}
	};

	// Apuntador al inicio de la lista
	Nodo* inicio;
	// Apuntador al final de la lista
	Nodo* final;

	void Inicializar() {
		inicio = nullptr;
		final = nullptr;
	}

public:

	// Declaración de definición de tipos
	typedef Nodo* listaptr;
	typedef const Nodo* const_listaptr;

	// Constructores
	// Default
	ListaEnlazada() { Inicializar(); }
	// Copia
	explicit ListaEnlazada(const ListaEnlazada& obj) {
		// Implementación para copiar la lista
	}

	// Destructor
	~ListaEnlazada() { BorrarLista(); }

	// Retorna un apuntador al primer nodo de la lista - modificable
	listaptr GetPrimerNodo() { return inicio; }

	// Retorna un apuntador al primer nodo de la lista - para un objeto const
	const_listaptr GetPrimerNodo() const { return inicio; }

	// Inserta una fila al final de la lista
	void InsertarFila(const std::vector<T>& valores) {
		if (valores.empty()) return;  // Si el vector está vacío, no hay nada que insertar

		listaptr finFilaAnterior = nullptr;
		listaptr inicioFilaNueva = nullptr;

		for (const T& val : valores) {
			listaptr nuevoNodo = new Nodo(val);

			if (!inicioFilaNueva) {
				inicioFilaNueva = nuevoNodo;
			}
			else {
				finFilaAnterior->right = nuevoNodo;
				nuevoNodo->left = finFilaAnterior;
			}

			// Si hay una fila anterior, conecta el nuevo nodo verticalmente
			if (finFilaAnterior && finFilaAnterior->up) {
				finFilaAnterior->up->right->down = nuevoNodo;
				nuevoNodo->up = finFilaAnterior->up->right;
			}

			finFilaAnterior = nuevoNodo;
		}

		if (!inicio) {
			inicio = inicioFilaNueva;
		}
	}

	// Inserta una columna al final de la lista
	void InsertarColumna(const std::vector<T>& valores) {
		if (valores.empty()) return;  // Si el vector está vacío, no hay nada que insertar

		listaptr finColumnaAnterior = nullptr;
		listaptr inicioColumnaNueva = nullptr;

		for (const T& val : valores) {
			listaptr nuevoNodo = new Nodo(val);

			if (!inicioColumnaNueva) {
				inicioColumnaNueva = nuevoNodo;
			}
			else {
				finColumnaAnterior->down = nuevoNodo;
				nuevoNodo->up = finColumnaAnterior;
			}

			// Si hay una columna anterior, conecta el nuevo nodo horizontalmente
			if (finColumnaAnterior && finColumnaAnterior->left) {
				finColumnaAnterior->left->down->right = nuevoNodo;
				nuevoNodo->left = finColumnaAnterior->left->down;
			}

			finColumnaAnterior = nuevoNodo;
		}

		if (!inicio) {
			inicio = inicioColumnaNueva;
		}
	}

	void EliminarFila(int posicion) {
		if (!inicio) return;  // Si la lista está vacía, no hay nada que eliminar

		listaptr filaActual = inicio;
		// Moverse a la fila correcta
		for (int i = 0; i < posicion && filaActual; i++) {
			filaActual = filaActual->down;
		}

		// Si el índice es inválido, simplemente retornar
		if (!filaActual) return;

		while (filaActual) {
			// Desconectar el nodo de la fila/columna anterior y siguiente
			if (filaActual->up) {
				filaActual->up->down = filaActual->down;
			}
			if (filaActual->down) {
				filaActual->down->up = filaActual->up;
			}

			listaptr nodoAEliminar = filaActual;
			filaActual = filaActual->right;

			delete nodoAEliminar;  // Liberar memoria
		}

		// Si estamos eliminando la primera fila, actualizar el puntero 'inicio'
		if (posicion == 0 && inicio->down) {
			inicio = inicio->down;
		}
		else if (posicion == 0) {
			inicio = nullptr;
		}
	}

	void EliminarColumna(int posicion) {
		if (!inicio) return;  // Si la lista está vacía, no hay nada que eliminar

		listaptr columnaActual = inicio;
		// Moverse a la columna correcta
		for (int i = 0; i < posicion && columnaActual; i++) {
			columnaActual = columnaActual->right;
		}

		// Si el índice es inválido, simplemente retornar
		if (!columnaActual) return;

		while (columnaActual) {
			// Desconectar el nodo de la fila/columna anterior y siguiente
			if (columnaActual->left) {
				columnaActual->left->right = columnaActual->right;
			}
			if (columnaActual->right) {
				columnaActual->right->left = columnaActual->left;
			}

			listaptr nodoAEliminar = columnaActual;
			columnaActual = columnaActual->down;

			delete nodoAEliminar;  // Liberar memoria
		}

		// Si estamos eliminando la primera columna, actualizar el puntero 'inicio'
		if (posicion == 0 && inicio->right) {
			inicio = inicio->right;
		}
		else if (posicion == 0) {
			inicio = nullptr;
		}
	}

	// Obtener nodo específico por posición
	listaptr ObtenerNodo(int fila, int columna) {
		if (!inicio) return nullptr;  // Si la lista está vacía

		listaptr nodoActual = inicio;

		// Moverse a la fila correcta
		for (int i = 0; i < fila && nodoActual; i++) {
			nodoActual = nodoActual->down;
		}

		// Si no se encontró la fila
		if (!nodoActual) return nullptr;

		// Moverse a la columna correcta
		for (int j = 0; j < columna && nodoActual; j++) {
			nodoActual = nodoActual->right;
		}

		// Devuelve el nodo en la posición especificada o nullptr si no se encontró
		return nodoActual;
	}

	// Borra completamente la lista
	void BorrarLista() {
		listaptr filaActual = inicio;

		while (filaActual) {
			listaptr nodoActual = filaActual;
			while (nodoActual) {
				listaptr nodoAEliminar = nodoActual;
				nodoActual = nodoActual->right;
				delete nodoAEliminar;
			}
			listaptr filaAEliminar = filaActual;
			filaActual = filaActual->down;
			delete filaAEliminar;
		}

		inicio = nullptr;  // Establecer inicio a nullptr
	}
};

#endif