// Descripción: Definición de una lista "cuadruplemente" enlazada.

#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <iostream>
#include <cstddef>

template<class T> class ListaEnlazada {
private:
	// Declaración de cada nodo de la lista: contiene el valor y un apuntador a un nodo
	// Queda oculto para el usuario
	struct Nodo {
		T valor;
		Nodo* left;
		Nodo* right;
		// Constructor del Nodo - asigna NULL si se invoca sin el segundo parámetro
		Nodo(T val, Nodo* izq = nullptr, Nodo* der = nullptr) : valor{ val }, left{ izq }, right { der } {}
	};

	// Apuntador al inicio de la lista
	Nodo* inicio;

	void Inicializar() { inicio = nullptr; }

public:

	// Declaración de definición de tipos
	typedef Nodo* listaptr;
	typedef const Nodo* const_listaptr;

	// Constructores
	// Default
	ListaEnlazada() { Inicializar(); }
	// Copia
	explicit ListaEnlazada(const ListaEnlazada& obj) {
		if (obj.inicio == nullptr)
			inicio = nullptr;
		else {
			inicio = new Nodo(obj.inicio->valor);
			listaptr actual = inicio;
			listaptr actualObj = obj.inicio->right;
			while (actualObj != nullptr) {
				actual->right = new Nodo(actualObj->valor); // nodo copiado
				actual->right->left = actual; // anterior del nodo copiado
				actual = actual->right;
				actualObj = actualObj->right;
			}
		}
	}

	// Destructor
	~ListaEnlazada() { BorrarLista(); }

	// Retorna un apuntador al primer nodo de la lista - modificable
	listaptr GetPrimerNodo() { return inicio; }

	// Retorna un apuntador al primer nodo de la lista - para un objeto const
	const_listaptr GetPrimerNodo() const { return inicio; }

	// Inserta un elemento al final de la lista enlazada
	void Insertar(const T& val) {
		listaptr nuevo;

		try {
			nuevo = new Nodo(val);
		}
		catch (std::bad_alloc exception) {
			return;
		}

		if (inicio == nullptr)
			inicio = nuevo;
		else {
			listaptr tmp = inicio;
			while (tmp->right != nullptr) {
				tmp = tmp->right;
			}
			tmp->right = nuevo;
			nuevo->left = tmp; // asigno prev del nuevo nodo
		}
	}

	// Inserta un elemento al inicio de la lista enlazada
	void InsertarInicio(const T& val) {
		listaptr nuevo;

		try {
			nuevo = new Nodo(val);
		}
		catch (std::bad_alloc exception) {
			return;
		}

		if (inicio == nullptr)
			inicio = nuevo;
		else {
			nuevo->right = inicio;
			inicio->left = nuevo; // asigno prev del nodo inicio anterior
			inicio = nuevo;
		}
	}

	// Elimina el nodo especificado de la lista enlazada
	void Eliminar(listaptr puntero) {
		// No hay nada que borrar si la lista enlazada está vacía
		// o el puntero es NULL
		if (puntero == nullptr || inicio == nullptr)
			return;

		// Caso #1: El elemento a borrar es el primero de la lista enlazada
		if (inicio == puntero) {
			inicio = inicio->right;
			if (inicio) inicio->left = nullptr; // = if (inicio != nullptr). Evita desreferenciar un puntero nulo (si inicio->next es nullptr, entonces nullptr->prev daría error)
			delete puntero;
		}
		// Caso #2: El elemento se encuentra en alguna otra posición de la lista
		else {
			listaptr tmp = inicio;
			listaptr tmp2 = tmp->right;
			while (tmp2 != nullptr) {
				if (tmp2 == puntero) {
					tmp->right = tmp2->right;

					if (tmp2->right) { // = if (tmp2->next != nullptr). Si el nodo que se elimina no es el último, se ajusta prev del siguiente.
						tmp2->right->left = tmp;
					}

					delete tmp2;
					return;
				}
				tmp = tmp2;
				tmp2 = tmp2->right;
			}
		}
	}

	// Elimina un nodo de la lista en la posición especificada
	void EliminarEnPos(std::size_t pos) {
		if (pos <= 0)
			return;

		listaptr tmp = inicio;
		for (std::size_t i = 1; i < pos; ++i) {
			tmp = tmp->right;
			if (tmp == nullptr)
				return;
		}
		Eliminar(tmp);
	}

	// Busca un elemento en la lista y retorna el nodo
	listaptr Buscar(const T& val) {
		listaptr tmp = inicio;
		while (tmp != nullptr) {
			if (tmp->valor == val)
				return tmp;
			tmp = tmp->right;
		}
		return nullptr;  // Si no lo encuentra retorna nullptr
	}

	// Borra completamente la lista
	void BorrarLista() {
		listaptr tmp;
		while (inicio != nullptr) {
			tmp = inicio;
			inicio = inicio->right;
			delete tmp;
		}
	}
};

#endif