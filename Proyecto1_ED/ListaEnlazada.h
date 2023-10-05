// Definición de una lista "cuadruplemente" enlazada. ------------------------ RECORDATORIO: SEPARAR LA CLASE EN .H Y .CPP AL FINAL
#pragma once

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
	/*// Apuntador al final de la lista
	Nodo* final;*/

	void Inicializar() {
		inicio = nullptr;
		//final = nullptr;
	}

	// Tamaño de la lista
	int filas = 0;
	int columnas = 0;

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
	~ListaEnlazada() {
		BorrarLista();
		filas = 0;
		columnas = 0;
	}

	// Retorna un apuntador al primer nodo de la lista - modificable
	listaptr GetPrimerNodo() { return inicio; }

	// Retorna un apuntador al primer nodo de la lista - para un objeto const
	const_listaptr GetPrimerNodo() const { return inicio; }

	/*// Verifica si un nodo es contiguo a otro en la lista en cualquier dirección
	bool EsAdyacente(listaptr nodo1, listaptr nodo2) {
		if (!nodo1 || !nodo2) return false;

		return (nodo1->right == nodo2 || nodo1->left == nodo2 ||
			nodo1->up == nodo2 || nodo1->down == nodo2);
	}

	// Encuentra todos los nodos con un mismo valor
	std::vector<listaptr> BuscarCeldasConValor(const T& valorBuscado) {
		std::vector<listaptr> nodosEncontrados;
		listaptr filaActual = inicio;
		while (filaActual) {
			listaptr nodoActual = filaActual;
			while (nodoActual) {
				if (nodoActual->valor == valorBuscado) {
					nodosEncontrados.push_back(nodoActual);
				}
				nodoActual = nodoActual->right;
			}
			filaActual = filaActual->down;
		}
		return nodosEncontrados;
	}*/

	// Retorna el número de filas en la lista
	int NumeroDeFilas() const { return filas; }

	// Retorna el número de columnas en la lista
	int NumeroDeColumnas() const { return columnas; }

	// Inserta una fila al final de la lista
	void InsertarFila(const std::vector<T>& valores) {
		if (valores.empty()) return;  // Si el vector de valores está vacío

		listaptr primerDeFilaAnterior = nullptr;
		if (filas > 0) {
			primerDeFilaAnterior = ObtenerNodo(filas - 1, 0);
		}

		listaptr finFilaAnterior = nullptr;
		listaptr inicioFilaNueva = nullptr;

		for (const T& val : valores) {
			listaptr nuevoNodo = new Nodo(val);

			if (!inicioFilaNueva) {
				inicioFilaNueva = nuevoNodo;
			}
			else {
				finFilaAnterior->right = nuevoNodo;  // Conecta el nodo derecho del nodo anterior al nuevo nodo
				nuevoNodo->left = finFilaAnterior;   // Conecta el nodo izquierdo del nuevo nodo al nodo anterior
			}

			if (primerDeFilaAnterior) {
				primerDeFilaAnterior->down = nuevoNodo;  // Conecta el nodo de abajo del nodo anterior al nuevo nodo
				nuevoNodo->up = primerDeFilaAnterior;   // Conecta el nodo de arriba del nuevo nodo al nodo anterior

				primerDeFilaAnterior = primerDeFilaAnterior->right;  // Avanza al siguiente nodo de la fila anterior
			}

			finFilaAnterior = nuevoNodo;
		}

		if (!inicio) {
			inicio = inicioFilaNueva;  // Si la lista estaba vacía, establece el inicio de la lista en el primer nodo de la fila nueva
		}

		filas++;
		if (valores.size() > columnas) {
			columnas = valores.size();  // Actualiza el número de columnas si es necesario
		}
	}

	// Inserta una columna al final de la lista
	void InsertarColumna(const std::vector<T>& valores) {
		if (valores.empty()) return;  // Si el vector de valores está vacío

		listaptr primerDeColumnaAnterior = nullptr;
		if (columnas > 0) {
			primerDeColumnaAnterior = ObtenerNodo(0, columnas - 1);
		}

		listaptr finColumnaAnterior = nullptr;
		listaptr inicioColumnaNueva = nullptr;

		for (const T& val : valores) {
			listaptr nuevoNodo = new Nodo(val);

			if (!inicioColumnaNueva) {
				inicioColumnaNueva = nuevoNodo;
			}
			else {
				finColumnaAnterior->down = nuevoNodo;  // Conecta el nodo de abajo del nodo anterior al nuevo nodo
				nuevoNodo->up = finColumnaAnterior;   // Conecta el nodo de arriba del nuevo nodo al nodo anterior
			}

			if (primerDeColumnaAnterior) {
				primerDeColumnaAnterior->right = nuevoNodo;  // Conecta el nodo derecho del nodo anterior al nuevo nodo
				nuevoNodo->left = primerDeColumnaAnterior;   // Conecta el nodo izquierdo del nuevo nodo al nodo anterior

				primerDeColumnaAnterior = primerDeColumnaAnterior->down;  // Avanza al siguiente nodo de la columna anterior
			}

			finColumnaAnterior = nuevoNodo;
		}

		if (!inicio) {
			inicio = inicioColumnaNueva;  // Si la lista estaba vacía, establece el inicio de la lista en el primer nodo de la columna nueva
		}

		columnas++;
		if (valores.size() > filas) {
			filas = valores.size();  // Actualiza el número de filas si es necesario
		}
	}

	// Elimina una fila en la posición dada
	void EliminarFila(int posicion) {
		// Si la lista está vacía o si la posición es inválida
		if (!inicio || posicion < 0 || posicion >= filas) return;

		// Moverse a la fila especificada
		listaptr filaActual = inicio;
		for (int i = 0; i < posicion && filaActual; i++) {
			filaActual = filaActual->down;
		}

		// Si no se encuentra la fila
		if (!filaActual) return;

		// Obtener referencias a las filas adyacentes
		listaptr filaAnterior = filaActual->up;
		listaptr filaSiguiente = filaActual->down;

		// Iterar a través de todos los nodos en la fila y eliminarlos
		listaptr nodoActual = filaActual;
		while (nodoActual) {
			listaptr siguienteNodo = nodoActual->right;

			// Desconectar el nodo actual de sus vecinos
			if (nodoActual->left) nodoActual->left->right = nodoActual->right;
			if (nodoActual->right) nodoActual->right->left = nodoActual->left;
			if (nodoActual->up) nodoActual->up->down = nodoActual->down;
			if (nodoActual->down) nodoActual->down->up = nodoActual->up;

			// Liberar memoria
			delete nodoActual;
			nodoActual = siguienteNodo;
		}

		// Reconectar las filas adyacentes
		if (filaAnterior) filaAnterior->down = filaSiguiente;
		if (filaSiguiente) filaSiguiente->up = filaAnterior;

		// Si se elimina la primera fila, actualizar el inicio
		if (posicion == 0) inicio = filaSiguiente;

		// Actualizar el conteo de filas
		filas--;
	}

	// // Elimina una columna en la posición dada
	void EliminarColumna(int posicion) {
		// Si la lista está vacía o si la posición es inválida
		if (!inicio || posicion < 0 || posicion >= columnas) return;

		// Moverse a la columna especificada
		listaptr columnaActual = inicio;
		for (int i = 0; i < posicion && columnaActual; i++) {
			columnaActual = columnaActual->right;
		}

		// Si no se encuentra la columna
		if (!columnaActual) return;

		// Obtener referencias a las columnas adyacentes
		listaptr columnaAnterior = columnaActual->left;
		listaptr columnaSiguiente = columnaActual->right;

		// Iterar a través de todos los nodos en la columna y eliminarlos
		listaptr nodoActual = columnaActual;
		while (nodoActual) {
			listaptr siguienteNodo = nodoActual->down;

			// Desconectar el nodo actual de sus vecinos
			if (nodoActual->left) nodoActual->left->right = nodoActual->right;
			if (nodoActual->right) nodoActual->right->left = nodoActual->left;
			if (nodoActual->up) nodoActual->up->down = nodoActual->down;
			if (nodoActual->down) nodoActual->down->up = nodoActual->up;

			// Liberar memoria
			delete nodoActual;
			nodoActual = siguienteNodo;
		}

		// Reconectar las columnas adyacentes
		if (columnaAnterior) columnaAnterior->right = columnaSiguiente;
		if (columnaSiguiente) columnaSiguiente->left = columnaAnterior;

		// Si se elimina la primera columna, actualizar el inicio
		if (posicion == 0) inicio = columnaSiguiente;

		// Actualizar el conteo de columnas
		columnas--;
	}

	// Retorna un nodo por posición
	listaptr ObtenerNodo(int fila, int columna) {
		if (fila < 0 || columna < 0 || fila >= filas || columna >= columnas) return nullptr;  // Si la lista está vacía

		listaptr nodoActual = inicio;

		// Moverse a la fila correcta
		for (int i = 0; i < fila; i++) {
			nodoActual = nodoActual->down;
			if (!nodoActual) return nullptr;  // Verifica que el nodo actual no sea nullptr
		}

		// Moverse a la columna correcta
		for (int j = 0; j < columna; j++) {
			nodoActual = nodoActual->right;
			if (!nodoActual) return nullptr;  // Verifica que el nodo actual no sea nullptr
		}

		return nodoActual;
	}

	// Borra completamente la lista
	void BorrarLista() {
		listaptr filaActual = inicio;

		while (filaActual) {
			listaptr nodoActual = filaActual;
			filaActual = filaActual->down;  // Moverse a la siguiente fila antes de borrar nodos

			while (nodoActual) {
				listaptr nodoAEliminar = nodoActual;
				nodoActual = nodoActual->right;  // Moverse al siguiente nodo antes de borrar
				delete nodoAEliminar;
			}
		}

		inicio = nullptr;
	}

	/*void Imprimir() {
		listaptr filaActual = inicio;
		while (filaActual) {
			listaptr nodoActual = filaActual;
			while (nodoActual) {
				std::cout << nodoActual->valor << "\t"; // Tabulación entre columnas
				nodoActual = nodoActual->right;
			}
			std::cout << std::endl; // Al final de cada fila
			filaActual = filaActual->down;
		}
	}*/
};

#endif
